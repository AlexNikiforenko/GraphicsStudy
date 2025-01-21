#include "ImageLoader.h"

#include "Errors.h"
namespace Engine {

    SDL_Surface* ImageLoader::loadSurface(std::string filePath) {
        SDL_Surface* surface = IMG_Load(filePath.c_str());
        if (!surface) {
            logSDLImageError("Couldn't load surface!");
            return nullptr;
        }
        SDL_Surface* optimizedSurface = SDL_ConvertSurfaceFormat(surface, SDL_PIXELFORMAT_RGBA32, 0);
        if (!optimizedSurface) {
            logSDLImageError("Couldn't optimize surface to RGBA32!");
            SDL_FreeSurface(surface);
            return nullptr;
        }
        SDL_FreeSurface(surface);
        surface = optimizedSurface;
        return surface;
    }

    GLTexture ImageLoader::loadPNG(std::string filePath) {
        GLTexture texture = {};
        SDL_Surface* surface = loadSurface(filePath);
        if (!surface) {
            fatalError("Couldn't create surface for texture!");
        }
        texture.width = surface->w;
        texture.height = surface->h;

        glGenTextures(1, &texture.id);

        glBindTexture(GL_TEXTURE_2D, texture.id);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture.width, texture.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, surface->pixels);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

        glGenerateMipmap(GL_TEXTURE_2D);

        glBindTexture(GL_TEXTURE_2D, 0);

        return texture;
    }
}