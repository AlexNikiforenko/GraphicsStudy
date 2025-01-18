#ifndef GL_TEXTURE_H
#define GL_TEXTURE_H

#include "../include/glad/glad.h"

struct GLTexture {
    GLuint id;
    int width;
    int height;
};

#endif