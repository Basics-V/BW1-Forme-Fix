import sys
import yaml
import json

def trim_prefix(symbol:str):
    prefixes = [
        "FULL_COPY_",
        #"THUMB_BRANCH_",
        #"THUMB_BRANCH_LINK_",
        #"THUMB_BRANCH_SAFESTACK_",
        #"ARM_BRANCH_",
        #"ARM_BRANCH_LINK"
    ]

    for prefix in prefixes:
        if symbol.startswith(prefix):
            return symbol[len(prefix):]
    return symbol

def normalize_segment(segment:str):
    segment = segment.replace(".c", "")
    if segment.startswith("main_"):
        segment = "OVL_%d" % int(segment.split("_")[-1], 16)
    if segment.startswith("overlay_"):
        segment = "OVL_%d" % int(segment.split("_")[-1])
    return segment.lower()

def match_segment(a:str, b:str):
    return normalize_segment(a) == normalize_segment(b)

if __name__ == "__main__":
    if len(sys.argv) == 2:
        with open(sys.argv[1], "r") as file:
            data = yaml.safe_load(file)
        for symbol in data["Symbols"]:
            print(".global %s" % symbol["Name"])
            if symbol["Address"] & 1:
                print(".type {}, %function".format(symbol["Name"]))
                print(".thumb_func")
            print("%s = 0x%X" % (symbol["Name"], symbol["Address"]))
            print()
        quit()

    assert len(sys.argv) == 4

    # Fetch arguments from command line
    *_, esdb, func, proj = sys.argv

    # Splice function into useful parts
    func = func.split("/")[-1].split(":")
    #seg  = func[0] # Unused
    sym  = trim_prefix(func[-1])

    # Nab offset if there is one
    offset = 0
    try:
        offs_str = sym.split("_")[-1]
        if offs_str.startswith("0x"):
            offset = int(offs_str[2:], 16)
            sym = "_".join(sym.split("_")[:-1])
    except ValueError:
        pass

    with open(proj, "r") as file:
        projson = json.loads(file.read())

    # Read ESDB file and parse it
    with open(esdb, "r") as file:
        data = yaml.safe_load(file)

    address = 0
    seg_id = -1
    for symbol in data["Symbols"]:
        if symbol["Name"] == sym:
            address = symbol["Address"]
            seg_id = symbol["Segment"]
            break

    if address == 0:
        raise ValueError("missing symbol for %s -- perhaps it is missing from %s?" % (sym, esdb))

    for segment in data["Segments"]:
        if seg_id == segment["ID"]:
            normal = normalize_segment(segment["Name"])
            if normal == "arm9":
                file_offset = 0x2004000
            else:
                file_offset = projson["RomInfo"]["ARM9Ovt"][int(normal.split("_")[-1])]["RamAddress"]

            address += offset
            print("%s 0x%X 0x%X" % (func[-1], address, address - file_offset))
            quit()
