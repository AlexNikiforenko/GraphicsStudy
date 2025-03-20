#include "TextureCache.h"
#include "ImageLoader.h"

#include <iostream>
namespace Engine {

    TextureCache::TextureCache() {

    }

    TextureCache::~TextureCache() {

    }

    GLTexture TextureCache::getTexture(std::string texturePath) {
        auto mit = m_textureMap.find(texturePath);
        if (mit == m_textureMap.end()) {
            GLTexture newTexture = ImageLoader::loadPNG(texturePath);

            m_textureMap.insert(std::make_pair(texturePath, newTexture));

            //std::cout << "Loaded texture\n";
            return newTexture;
        }

        //std::cout << "Used cached texture\n";
        return mit->second;
    }
}