# hook_filter.py
# Authors: MCMi460

import sys
import re

def strip_comments(string):
    line = False
    block = False
    ret = ""
    for idx, char in enumerate(string):
        if len(string) > idx + 1:
            match string[idx:idx+2]:
                case "//":
                    line = True
                case "/*":
                    block = True
                case "*/":
                    block = False
        if char == "\n":
            line = False
        if not line and not block:
            ret += char
    return ret.replace("*/", "")

def fetch_prefixed(string:str) -> list[str]:
    pattern = r"FULL_COPY_[A-Za-z0-9_]+(_0x[0-9a-fA-F]+)?"
    regex = re.compile(pattern)
    return [ match.group(0) for match in regex.finditer(string) ]

if __name__ == "__main__":
    for arg in sys.argv[1:]:
        with open(arg, "r") as file:
            contents = file.read()
        print(" ".join(fetch_prefixed(strip_comments(contents))))
