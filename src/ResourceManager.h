#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include "TextureCache.h"
#include "GLTexture.h"
#include <string>

class ResourceManager {
public:
    ResourceManager();
    ~ResourceManager();

    static GLTexture getTexture(std::string texturePath);

private:
    static TextureCache m_textureCache;
};

#endif