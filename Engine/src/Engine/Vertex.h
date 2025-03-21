#pragma once

#include "../include/glad/glad.h"
namespace Engine {

    struct Position {
        float x;
        float y;
    };

    struct Color {
        Color() {}

        Color(GLubyte r, GLubyte g, GLubyte b, GLubyte a)
            : r(r), g(g), b(b), a(a) {}

        void setColor(GLubyte r, GLubyte g, GLubyte b, GLubyte a) {
            this->r = r;
            this->g = g;
            this->b = b;
            this->a = a;
        }

        GLubyte r;
        GLubyte g;
        GLubyte b;
        GLubyte a;
    };

    struct UV {
        float u;
        float v;
    };

    struct Vertex {
        Position position;

        Color color;

        UV uv;

        void setPosition(float x, float y) {
            position.x = x;
            position.y = y;
        }

        void setColor(GLubyte r, GLubyte g, GLubyte b, GLubyte a) {
            color.r = r;
            color.g = g;
            color.b = b;
            color.a = a;
        }

        void setUV(float u, float v) {
            uv.u = u;
            uv.v = v;
        }
    };
}