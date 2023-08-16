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
    const char desiredPattern[5] = "\x00\x00\x46\x50";  // Example pattern as a string

    bool patternFound = false;
    std::streampos offset = 0;

    while (!hexFile.eof()) {
        hexFile.seekg(offset);

        char readData[patternLength];
        hexFile.read(readData, patternLength);

        if (hexFile.gcount() != patternLength) {
            break; // Reached end of file or unable to read more bytes
        }

        std::cout << "Read data: ";
        for (int i = 0; i < patternLength; ++i) {
            std::cout << static_cast<int>(readData[i]) << " ";
        }
        std::cout << std::endl;

        if (memcmp(readData, desiredPattern, 4) == 0) {
            patternFound = true;
            std::cout << "Read data: ";
        for (int i = 0; i < patternLength; ++i) {
            std::cout << static_cast<int>(readData[i]) << " ";
        }
        std::cout << std::endl;
            offset += patternLength; // Move offset to the position after the pattern
            break;
        }
        offset += 1; // Increment offset within the loop
    }

    if (patternFound) {
        std::cout << "Pattern found at offset " << (offset - static_cast<std::streampos>(patternLength)) << std::endl;
        std::cout << "Offset set to " << offset << std::endl;
    } else {
        std::cout << "Pattern not found." << std::endl;
        std::cout << "Desired pattern: " << desiredPattern << std::endl;
    }

    hexFile.close();

    return 0;
}
