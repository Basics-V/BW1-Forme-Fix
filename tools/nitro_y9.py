import json
import sys

if __name__ == "__main__":
    assert len(sys.argv) == 3

    project_json = sys.argv[1]
    y9_donor     = sys.argv[2]

    with open(project_json, "r") as file:
        project_table = json.loads(file.read())
    with open(y9_donor, "r") as file:
        donor_table = json.loads(file.read())

    table = project_table["RomInfo"]["ARM9Ovt"]
    if donor_table not in table:
        table += donor_table

    with open(project_json, "w") as file:
        file.write(json.dumps(project_table, indent = 4))
