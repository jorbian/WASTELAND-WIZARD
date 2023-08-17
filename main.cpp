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
        hexFile.read(newValue, 1);
        strength = static_cast<int>(newValue[0]);
        std::cout << "Strength value: " << strength << std::endl;
        hexFile.seekg(static_cast<std::streamoff>(offset) + 4); // Move to the new offset + 4 bytes
        hexFile.read(newValue, 1);
        strength = static_cast<int>(newValue[0]);
        std::cout << "Perception value: " << strength << std::endl;
        hexFile.seekg(static_cast<std::streamoff>(offset) + 4); // Move to the new offset + 4 bytes
        hexFile.read(newValue, 1);
        strength = static_cast<int>(newValue[0]);
        std::cout << "Endurance value: " << strength << std::endl;
        hexFile.seekg(static_cast<std::streamoff>(offset) + 4); // Move to the new offset + 4 bytes
        hexFile.read(newValue, 1);
        strength = static_cast<int>(newValue[0]);
        std::cout << "Charisma value: " << strength << std::endl;
        hexFile.seekg(static_cast<std::streamoff>(offset) + 4); // Move to the new offset + 4 bytes
        hexFile.read(newValue, 1);
        strength = static_cast<int>(newValue[0]);
        std::cout << "Intelligence value: " << strength << std::endl;
        hexFile.seekg(static_cast<std::streamoff>(offset) + 4); // Move to the new offset + 4 bytes
        hexFile.read(newValue, 1);
        strength = static_cast<int>(newValue[0]);
        std::cout << "Agility value: " << strength << std::endl;
        hexFile.seekg(static_cast<std::streamoff>(offset) + 4); // Move to the new offset + 4 bytes
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
