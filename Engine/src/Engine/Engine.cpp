#include "Engine.h"
#include "Errors.h"
#include "SDL.h"
#include "SDL_image.h"
#include "../include/glad/glad.h"

namespace Engine {

    int init() {
        // Initialize SDL
        if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
            logSDLError("SDL couldn't be initialize!");
            return -1;
        }

        // Set double buffered window
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

        // Initialize SDL_image
        if (IMG_Init(IMG_INIT_PNG) < 0) {
            logSDLImageError("SDL_image couldn't be initialize!");
            return -1;
        }
        return 0;
    }
}