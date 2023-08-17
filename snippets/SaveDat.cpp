#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>

using namespace std;

namespace SaveDat
{
    class File
    {
        private:
            string filepath;

            ssize_t find_bytes(char search_seq[], size_t search_size)
            {
                std::ifstream file(this->filepath, std::ios::binary);

                file.seekg(0, std::ios::end);
                size_t fileSize = file.tellg();
                file.seekg(0, std::ios::beg);

                std::vector<char> buffer(fileSize);
                file.read(buffer.data(), fileSize);

                ssize_t position = -1;

                for (ssize_t i = 0; i < fileSize - search_size + 1; ++i) {
                    if (memcmp(buffer.data() + i, search_seq, search_size) == 0) {
                        position = i - search_size;
                        break;
                    }
                }
                file.close();

                return (position);
            }

        public:
            File(string path)
            {
                filepath = path;
            }

            string get_path() const
            {
                return (filepath);
            }
    };
};
