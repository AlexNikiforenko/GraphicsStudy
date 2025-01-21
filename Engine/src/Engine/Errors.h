#ifndef ERRORS_H
#define ERRORS_H

#include <string>
namespace Engine {

    void logSDLError(std::string msg);
    void logSDLImageError(std::string msg);
    void fatalError(std::string msg);
}
#endif