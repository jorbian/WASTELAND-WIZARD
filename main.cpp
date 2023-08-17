#include <iostream>
#include <fstream>
#include <string>
#include <cstring>


int main() {
    std::ifstream hexFile("SAVE.DAT", std::ios::binary);

    if (!hexFile.is_open()) {
        std::cerr << "Failed to open the file." << std::endl;
        return 1;
    }

    const int patternLength = 4; // Adjust to match the length of your pattern
    const char desiredPattern[5] = "\x00\x00\x46\x50"; // Example pattern as a string

    bool patternFound = false;
    std::streampos offset = 0;
    int strength = 0; // Variable to store strength value

    while (!hexFile.eof()) {
        hexFile.seekg(offset);

        char readData[patternLength];
        hexFile.read(readData, patternLength);

        if (hexFile.gcount() != patternLength) {
            break; // Reached end of file or unable to read more bytes
        }

        if (memcmp(readData, desiredPattern, 4) == 0) {
            patternFound = true;
            offset += patternLength; // Move offset to the position after the pattern
            break;
        }
        offset += 1; // Increment offset within the loop
    }

    if (patternFound) {
        std::cout << "Pattern found at offset " << (offset - static_cast<std::streampos>(patternLength)) << std::endl;
        offset += 239; // Set offset to 239 bytes after the pattern
        std::cout << "Offset set to " << offset << std::endl;

        hexFile.seekg(static_cast<std::streamoff>(offset) + 4); // Move to the new offset + 4 bytes
        char newValue[1];
        int stroffset, peroffset, endoffset, charoffset, intoffset, agiloffset, luckoffset;
        stroffset = offset;
        std::cout << "Strength Offset set to " << stroffset << std::endl;
        hexFile.read(newValue, 1);
        strength = static_cast<int>(newValue[0]);
        std::cout << "Strength value: " << strength << std::endl;
        hexFile.seekg(static_cast<std::streamoff>(stroffset) + 4); // Move to the new offset + 4 bytes
        peroffset = stroffset += 4;
        std::cout << "Perception Offset set to " << peroffset << std::endl;
        hexFile.read(newValue, 1);
        strength = static_cast<int>(newValue[0]);
        std::cout << "Perception value: " << strength << std::endl;
        hexFile.seekg(static_cast<std::streamoff>(peroffset) + 4); // Move to the new offset + 4 bytes
        endoffset = peroffset += 4;
        std::cout << "Endurance Offset set to " << endoffset << std::endl;
        hexFile.read(newValue, 1);
        strength = static_cast<int>(newValue[0]);
        std::cout << "Endurance value: " << strength << std::endl;
        hexFile.seekg(static_cast<std::streamoff>(endoffset) + 4); // Move to the new offset + 4 bytes
        charoffset = endoffset += 4;
        std::cout << "Charisma Offset set to " << charoffset << std::endl;
        hexFile.read(newValue, 1);
        strength = static_cast<int>(newValue[0]);
        std::cout << "Charisma value: " << strength << std::endl;
        hexFile.seekg(static_cast<std::streamoff>(charoffset) + 4); // Move to the new offset + 4 bytes
        intoffset = charoffset += 4;
        std::cout << "Intelligence Offset set to " << intoffset << std::endl;
        hexFile.read(newValue, 1);
        strength = static_cast<int>(newValue[0]);
        std::cout << "Intelligence value: " << strength << std::endl;
        hexFile.seekg(static_cast<std::streamoff>(intoffset) + 4); // Move to the new offset + 4 bytes
        agiloffset = intoffset += 4;
        std::cout << "Agility Offset set to " << agiloffset << std::endl;
        hexFile.read(newValue, 1);
        strength = static_cast<int>(newValue[0]);
        std::cout << "Agility value: " << strength << std::endl;
        hexFile.seekg(static_cast<std::streamoff>(agiloffset) + 4); // Move to the new offset + 4 bytes
        luckoffset = agiloffset += 4;
        std::cout << "Luck Offset set to " << luckoffset << std::endl;
        hexFile.read(newValue, 1);
        strength = static_cast<int>(newValue[0]);
        std::cout << "Luck value: " << strength << std::endl;
    } else {
        std::cout << "Pattern not found." << std::endl;
        std::cout << "Desired pattern: " << desiredPattern << std::endl;
    }

    hexFile.close();

    return 0;
}

