#include "Errors.h"

#include <cstdlib>
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
namespace Engine {

    void logSDLError(std::string msg) {
        std::cout << msg << " SDL Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        exit(1);
    }

    void logSDLImageError(std::string msg) {
        std::cout << msg << " SDL_image Error: " << IMG_GetError() << std::endl;
        IMG_Quit();
        SDL_Quit();
        exit(1);
    }

    void fatalError(std::string msg) {
        std::cout << msg << std::endl;
        SDL_Quit();
        exit(1);
    }
}