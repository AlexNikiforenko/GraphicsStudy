#pragma once

#include "GLTexture.h"
#include <map>
namespace Engine {

    class TextureCache {
    public:
        TextureCache();
        ~TextureCache();

        GLTexture getTexture(std::string texturePath);

    private:
        std::map<std::string, GLTexture> m_textureMap;
    };
}
