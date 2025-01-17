#ifndef IMAGE_LOADER_H
#define IMAGE_LOADER_H

#include "GLTexture.h"

#include "SDL_image.h"
#include <string>

class ImageLoader {
public:
    GLTexture loadPNG(std::string filePath);
private:
    SDL_Surface* loadSurface(std::string filePath);
};

#endif