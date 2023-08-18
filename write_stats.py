#!/usr/bin/env python3
"""
SCRIPT TAKES THE FILEPATH TO 'SAVE.DAT' FILE AS AN ARGUMENT
AND PRINTS THE SEVEN 'SPECIAL' STATS TO STANDARD OUTPUT
"""
from pathlib import Path

STAT_MEM_ADDRESS = 0x8c2c
STAT_FIELD_SIZE = 4

def write_stats(filepath, stats=[6,6,5,5,5,6,6]):
    save_file_obj = Path(filepath)
    if (save_file_obj.name != "SAVE.DAT"):
        raise Exception()
    
    if (
        not all([isinstance(x, int) for x in stats]) and
        len(stats) == 7
    ):
        raise Exception()
    
    stats = [x.to_bytes(4, byteorder='big') for x in stats]

    with open(save_file_obj, "rb+") as file:
        current_address = STAT_MEM_ADDRESS
        for num in stats:
            current_address += 4
            file.seek(current_address)
            file.write(num)


if __name__ == "__main__":
    import sys

    if (len(sys.argv) > 1):
        save_path = sys.argv[1]
        save_file_obj = Path(save_path)
        if save_file_obj.exists():
            write_stats(save_file_obj)
    else:
        print("INVALID FILE")
