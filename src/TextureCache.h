#ifndef TEXTURE_CACHE_H
#define TEXTURE_CACHE_H

#include "GLTexture.h"
#include <map>

class TextureCache {
public:
    TextureCache();
    ~TextureCache();

    GLTexture getTexture(std::string texturePath);

private:
    std::map<std::string, GLTexture> m_textureMap;
};

#endif