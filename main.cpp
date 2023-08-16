#include <iostream>
#include <fstream>
#include <string>

int main() {
    std::ifstream hexFile("SAVE.DAT", std::ios::binary);

    if (!hexFile.is_open()) {
        std::cerr << "Failed to open the file." << std::endl;
        return 1;
    }

    const int patternLength = 4; // Adjust to match the length of your pattern
    std::string desiredPattern = "0 0 46 50"; // Example pattern as a string

    bool patternFound = false;
    std::streampos offset = 0x08c;

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

        if (std::string(readData, patternLength) == desiredPattern) {
            patternFound = true;
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
