#!/usr/bin/env python3

from pathlib import Path

filepath = "/home/boller/Desktop/test/data/SLOT10/SAVE.DAT"

class Structure:
    """A UTUILITY CLASS FOR DEALING WITH 'SAVE.DAT' FILES MORE ABSTRACTLY"""
    player_stats = {
        "strength": 0x08,
        "perception": 0x0c,
        "endurance": 0x10,
        "charisma": 0x14,
        "intelligence": 0x18,
        "agility": 0x1c,
        "luck": 0x20
    }
    stat_block_at_start = 0x8c2c
    stat_field_size = 0x04
    stat_block_size = len(player_stats) * stat_field_size

class File:

    def __init__(self, filepath):

        self.file_obj = Path(filepath)
        self.stat_location = -1
        self.stat_values = {}

        self.find_stat_location()
        self.get_stat_values()


    def find_stat_location(self):
        """DETERMIN POSITION OF STAT BLOCK WITHIN FILE"""
        field_size = Structure.stat_field_size
        num_of_stats = len(Structure.player_stats)

        with open(self.file_obj, "rb") as file:
            consecutive_count = 0
            offset = -1

            while (chunk := file.read(field_size)):
                values = [x for x in chunk]
                leading_bytes = values[:-1]
                last_byte = values[-1]

                if not any(leading_bytes) and (1 <= last_byte < 10):
                    consecutive_count += 1
                    if consecutive_count == 1:
                        print("IT GOG HERE")
                        offset = file.tell() - field_size

                    tests_passed = [
                        consecutive_count == num_of_stats
                    ]
                    if all(tests_passed):
                        break
                else:
                    consecutive_count = 0

            file.seek(offset -10)
            print([x for x in file.read(2)])
            file.seek(offset + 30)
            print([x for x in file.read(2)])

        self.stat_location = offset

    def read_n_bytes(self, n, offset=0, whence=0):
        """READ CERTAIN NUMBER OF BYTES FROM FILE, WITH OR WITHOUT OFFSET"""
        with self.file_obj.open('b+r') as file:
            file.seek(offset, whence)
            read_bytes = file.read(n)

        return (read_bytes)

    def get_stat_values(self):
        """ONCE WE HAVE THE STAT BLOCK GOES TO IT IN MEMORY AND READS 28 BYTES
        AND TRANSLATES THAT TO A DICTIONARY WHERE THE NAMES ARE THE KEYS AND
        THE VALUES ARE THE VALUES"""
        field_size = Structure.stat_field_size
        names = Structure.player_stats.keys()

        raw_data = self.read_n_bytes(Structure.stat_block_size, self.stat_location)
        values = [
            raw_data[i:i+field_size][-1] for i in range(0, len(raw_data), field_size)
        ]
        self.stat_values = dict(zip(names, values))

x = File(filepath)

print(vars(x))
