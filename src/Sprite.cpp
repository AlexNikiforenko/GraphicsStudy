#include "Sprite.h"
#include "Vertex.h"

#include <cstddef>

Sprite::Sprite() : m_vboID(0) {

}
Sprite::~Sprite() {
    if (m_vboID != 0) {
        glDeleteBuffers(1, &m_vboID);
    }
}

void Sprite::init(float x, float y, float width, float height) {
    m_x = x;
    m_y = y;
    m_width = width;
    m_height = height;

    if (m_vboID == 0) {
        glGenBuffers(1, &m_vboID);
    }

    Vertex vertexData[6]; // x6 (x, y)

    // First Triangle
    vertexData[0].position.x = x + width;
    vertexData[0].position.y = y + width;

    vertexData[1].position.x = x;
    vertexData[1].position.y = y + height;

    vertexData[2].position.x = x;
    vertexData[2].position.y = y;

    // Second Triangle
    vertexData[3].position.x = x;
    vertexData[3].position.y = y;

    vertexData[4].position.x = x + width;
    vertexData[4].position.y = y;

    vertexData[5].position.x = x + width;
    vertexData[5].position.y = y + height;

    for (Vertex& vertex : vertexData) {
        vertex.setColor(255, 0, 255, 255);
    }

    vertexData[1].setColor(0, 0, 255, 255);

    vertexData[4].setColor(0, 255, 0, 255);

    glBindBuffer(GL_ARRAY_BUFFER, m_vboID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Sprite::draw() {
    glBindBuffer(GL_ARRAY_BUFFER, m_vboID);

    glEnableVertexAttribArray(0);

    // This is the position attribute pointer
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
    // Color attribute pointer
    glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color));

    glDrawArrays(GL_TRIANGLES, 0, 6);

    glDisableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}