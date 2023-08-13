#!/usr/bin/env python3
#
# Structuring the code this way allows the project's code base to be more
# easily changed. You can change how you treat the data structure (like if
# you and to use JSON vs YAML or XML or something else) AND rewrite savedat.hpp
# at exactly the same time. Plus gives us a chance to model some of the logica
# that will have to be carried over into C++.

import binascii
import os

from pathlib import Path

test_path = "/home/boller/Documents/GitHub/WASTELAND WIZARD/data/test_files/third_party/Fallout2/Saves 51 to 60/SLOT01/SAVE.DAT"

class Structure:
    """NESTED CLASS REPRESENTING THE ABSTRACT DATA STRUCTURE"""
    class Field:
        """SUB-NESTED CLASS MODELLING INDIVIDUAL FIELDS OF BINARY DATA WITHIN THE FILE"""
        def __init__(self, *args):
            self.name = args[0]
            self.offset = args[1]
            self.size = args[2]
            self.description = args[3]

    # DATE STRUCTURE AS DESCRIBED HERE:
    # https://falloutmods.fandom.com/wiki/SAVE.DAT_File_Format
    header = (
        Field("FILE SIGNATURE", 0x00, 0x18, "Value: 'FALLOUT SAVE FILE '"),
        Field("PLAYER NAME", 0x1D, 0x20, "ASCII string -- 31 characters max"),
        Field("SAVE NAME", 0x3D, 0x1E, " ASCII string -- 31 characters max"),
        Field("DAY OF SAVE", 0x5B, 0x02, "Day game was saved (realtime, not gametime.)"),
        Field("MONTH OF SAVE", 0x5D, 0x02, "The month game was saved (realtime, not gametime.)"),
        Field("YEAR OF SAVE", 0x5D, 0x02, "The year game was saved (realtime, not gametime.)"),
        Field("INGAME DATE VALUE", 0x6B, 0x04, "Number of seconds since midnight 12/5/2161 x10"),
        Field("NUM OF CURRENT MAP", 0x6F, 0x04, "Number of current on map. 1st 2 bytes = level, 2nd 2 = map num"),
        Field("NAME OF CURRENT MAP", 0x73, 0x10, "Filename of map player is on -- ASCII string.")
    )


    @classmethod
    def export_to_json(cls, filename="", get_data=None):
        """CREATE A JSON FILE TO SAVE THE DATA STRUCTURE"""
        import json

        if (not get_data):
            get_data = (lambda x: {})

        json_file = filename if filename else (
            "./{}_{}.json".format(
                Path(__file__).stem,
                cls.__name__.lower()
            )
        )
        needed_data = get_data(cls)

        Path(json_file).write_text(
            json.dumps(
                needed_data,
                indent=4,
                sort_keys=True
            )
        )

    @staticmethod
    def filter_data(class_obj):
        """GET DATA READY FOR EXPORT AS JSON, SAVEDAT.HPP OR WHATEVER"""
        return dict([(y[0], [vars(z) for z in y[1]] )for y in [x for x in vars(class_obj).items() if (
                    ("_" not in x[0]) and
                    ("class" not in str(x[1])) and
                    (not callable(x[1]))
        )]])


class File:
    """NESTED CLASS REPRESENTING ANY PARTICULAR 'SAVE.DAT' FILE ON THE COMPUTER"""
    def __init__(self, path):
        self.file_obj = Path(path)
        self.stat = os.stat(path)

        parsed_path = self.file_obj.parts
        if (len(parsed_path) < 3):
            raise ValueError()

        self.output_name = "{}_BYTES".format(
            "-".join([
                x.replace(" ", "-") for x in (parsed_path[:-1])[-3:]
            ]
        ))

    def read_n_bytes(self, n, offset=0, whence=0):
        """READ CERTAIN NUMBER OF BYTES FROM FILE, WITH OR WITHOUT OFFSET"""
        with self.file_obj.open('b+r') as file:
            file.seek(offset, whence)
            read_bytes = file.read(n)

        return (read_bytes)

    def print_file_header(self):
        print(self.file_obj.resolve())

        for field in Structure.header:
            field_data = binascii.hexlify(
                self.read_n_bytes(field.size, field.offset), " ", 1
            )
            print(f"{field.name}: ", end="")
            print(field_data)

        print()

Structure.export_to_json("", Structure.filter_data)
