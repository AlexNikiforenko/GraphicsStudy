#pragma once

#include "Vertex.h"
#include "../include/glad/glad.h"
#include "../include/glm/glm.hpp"
#include <vector>

namespace Engine {

    enum class GlyphSortType {
        NONE,
        FRONT_TO_BACK,
        BACK_TO_FRONT,
        TEXTURE
    };

    struct Glyph {
        GLuint texture;
        float depth;

        Vertex topLeft;
        Vertex bottomLeft;
        Vertex topRight;
        Vertex bottomRight;
    };

    class RenderBatch {
    public:
        RenderBatch(GLuint offset, GLuint numVertices, GLuint texture)
            : offset(offset), numVertices(numVertices), texture(texture) {}

        GLuint offset;
        GLuint numVertices;
        GLuint texture;
    };

    class SpriteBatch {
    public:
        SpriteBatch();
        ~SpriteBatch();

        void init();

        void begin(GlyphSortType sortType = GlyphSortType::TEXTURE);
        void end();

        void draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture, float depth, const Color& color);

        void renderBatch();
    private:
        void createRenderBatches();
        void createVertexArray();
        void sortGlyphs();

        GLuint m_vbo;
        GLuint m_vao;

        GlyphSortType m_sortType;

        std::vector<Glyph*> m_glyphs;
        std::vector<RenderBatch> m_renderBatches;
    };
}