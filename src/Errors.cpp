#include "Errors.h"

#include <cstdlib>
#include <iostream>
#include <SDL2/SDL.h>

void logSDLError(std::string msg) {
    std::cout << msg << " SDL Error: " << SDL_GetError() << std::endl;
}

void fatalError(std::string msg) {
    std::cout << msg << std::endl;
    SDL_Quit();
    exit(1);
}