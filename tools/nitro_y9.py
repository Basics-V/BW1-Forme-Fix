# nitro_y9.py
# Authors: MCMi460

import json
import sys
import os

if __name__ == "__main__":
    assert len(sys.argv) == 4

    fpm_bin      = sys.argv[1]
    project_json = sys.argv[2]
    y9_donor     = sys.argv[3]

    fpm_size = os.path.getsize(fpm_bin)
    with open(project_json, "r") as file:
        project_table = json.loads(file.read())
    with open(y9_donor, "r") as file:
        donor_table = json.loads(file.read() % fpm_size)

    table = project_table["RomInfo"]["ARM9Ovt"]
    if donor_table not in table:
        table += donor_table

    with open(project_json, "w") as file:
        file.write(json.dumps(project_table, indent = 4))

    # Return the size of the overlay
    print(fpm_size)
