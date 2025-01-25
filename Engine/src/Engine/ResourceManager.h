#pragma once

#include "TextureCache.h"
#include "GLTexture.h"
#include <string>

namespace Engine {

    class ResourceManager {
    public:
        ResourceManager();
        ~ResourceManager();

        static GLTexture getTexture(std::string texturePath);

    private:
        static TextureCache m_textureCache;
    };
}
