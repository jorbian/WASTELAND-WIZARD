#!/usr/bin/env python3

import binascii
import os

from pathlib import Path

test_path = "/home/boller/Documents/GitHub/WASTELAND WIZARD/data/test_data/third_party/Fallout1/Saves 1 to 10/SLOT01/SAVE.DAT"

class SaveDAT:
    """CLASS OBJECT TO MANIPULATE 'SAVE.DAT' FILE FOR TESTING AND DEBUG PURPOSES"""

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
        def export_to_json(cls, filename="", filter=(lambda x: x)):
            """CREATE A JSON FILE TO SAVE THE DATA STRUCTURE"""
            json_file = filename if filename else (
                "./{}_{}.json".format(
                    Path(__file__).stem,
                    cls.__name__.lower()
                )
            )


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


SaveDAT.Structure.export_to_json()