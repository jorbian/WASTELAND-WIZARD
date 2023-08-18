#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

#define NUM_STATS 7

enum base_stats {
    STR, PER, ENDR, CHA, INT, AGL, LUCK
};


std::uint32_t *get_stats(const char *filepath)
{
    int *stats = new int[NUM_STATS];
    std::uint32_t temp;

    std::ifstream hexFile(filepath, std::ios::binary);
    std::streampos offset = 0x8C30;  // Start offset of the values in the file

    if (!hexFile.is_open())
    {
        std::cerr << "Failed to open the file." << std::endl;
        return nullptr;
    }

    hexFile.seekg(offset);

    for (size_t i = 0; i < NUM_STATS; i++)
    {
        hexFile.read(reinterpret_cast<char*>(&temp), sizeof(temp));
        stats[i] = static_cast<int>(temp);
    }

    hexFile.close();

    return stats;
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cout << "NO FILE NAME ENTERED" << std::endl;
    }
    std::uint32_t *stats = get_stats(argv[1]);

    for (size_t j = 0; j < NUM_STATS; j++)
        std::cout << stats[j] << std::endl;

    return (0);
}
