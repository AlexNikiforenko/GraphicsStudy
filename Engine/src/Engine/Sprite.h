#ifndef SPRITE_H
#define SPRITE_H

#include "GLTexture.h"
#include "../include/glad/glad.h"
#include <string>

namespace Engine {

    class Sprite {
    public:
        Sprite();
        Sprite(float x, float y, float width, float height, std::string texturePath);
        ~Sprite();

        void init(float x, float y, float width, float height, std::string texturePath);

        void draw();

    private:
        float m_x;
        float m_y;
        float m_width;
        float m_height;
        GLuint m_vboID;
        GLTexture m_texture;

    };
}

#endif