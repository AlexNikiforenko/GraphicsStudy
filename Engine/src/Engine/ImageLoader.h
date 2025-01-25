#pragma once

#include "GLTexture.h"

#include "SDL_image.h"
#include <string>
namespace Engine {

    class ImageLoader {
    public:
        static GLTexture loadPNG(std::string filePath);
    private:
        static SDL_Surface* loadSurface(std::string filePath);
    };
}
