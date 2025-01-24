#ifndef IO_MANAGER_H
#define IO_MANAGER_H

#include <vector>
namespace Engine {

    class IOManager {
    public:
        static bool readFileToBuffer(std::string filePath, std::vector<unsigned char>& buffer);
    };
}

#endif