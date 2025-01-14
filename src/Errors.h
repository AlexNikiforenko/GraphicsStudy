#ifndef ERRORS_H
#define ERRORS_H

#include <string>
#include <iostream>
#include <SDL2/SDL.h>

extern void logSDLError(std::string msg);
extern void fatalError(std::string msg);

#endif