#ifndef SPRITE_H
#define SPRITE_H

#include "../include/glad/glad.h"
#include <iostream>

class Sprite {
public:
    Sprite();
    ~Sprite();

    void init(float x, float y, float width, float height);

    void draw();

private:
    float m_x;
    float m_y;
    float m_width;
    float m_height;
    GLuint m_vboID;
};

#endif