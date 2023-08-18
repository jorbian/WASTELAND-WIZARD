#!/usr/bin/env python3
"""
SCRIPT TAKES THE FILEPATH TO 'SAVE.DAT' FILE AS AN ARGUMENT
AND PRINTS THE SEVEN 'SPECIAL' STATS TO STANDARD OUTPUT
"""
from pathlib import Path

STAT_MEM_ADDRESS = 0x8c2c
STAT_BLOCK_SIZE = 28

def get_stats(filepath):
    """GETS THE STATS FROM A 'SAVE.DAT' FILE FROM A CHARACTER WITH ONE ITEM"""
    save_file_obj = Path(filepath)
    if (save_file_obj.name != "SAVE.DAT"):
        raise Exception()

    with open(save_file_obj, "ab") as file:
        file.seek(STAT_MEM_ADDRESS)
        stat_data = [
            str(x) for x in file.read(STAT_BLOCK_SIZE) if x
        ]
    stats = ",".join(stat_data)

    print(stats)


if __name__ == "__main__":
    import sys

    if (len(sys.argv) > 1):
        save_path = sys.argv[1]
        save_file_obj = Path(save_path)
        if save_file_obj.exists():
            get_stats(save_file_obj)
    else:
        print("INVALID FILE")
