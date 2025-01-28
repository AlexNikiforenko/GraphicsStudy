#include "Camera2D.h"

#include <iostream>

namespace Engine {
    Camera2D::Camera2D()
        : m_scale(1.0f),
        m_position(0.0f, 0.0f),
        m_cameraMatrix(1.0f),
        m_orthoMatrix(1.0f),
        m_needsMatrixUpdate(true),
        m_screenWidth(500),
        m_screenHeight(500) {

    }

    Camera2D::~Camera2D() {

    }

    void Camera2D::init(int screenWidth, int screenHeight) {
        m_screenWidth = screenWidth;
        m_screenHeight = screenHeight;
        m_orthoMatrix = glm::ortho(0.0f, static_cast<float>(m_screenWidth), 0.0f, static_cast<float>(m_screenHeight));
    }

    void Camera2D::update() {
        if (m_needsMatrixUpdate) {
            // Camera Translation
            glm::vec3 translate(-m_position.x + m_screenWidth / 2, -m_position.y + m_screenHeight / 2, 0.0f);
            m_cameraMatrix = glm::translate(m_orthoMatrix, translate);

            // Camera Scale
            glm::vec3 scale(m_scale, m_scale, 0.0f);
            m_cameraMatrix = glm::scale(glm::mat4(1.0f), scale) * m_cameraMatrix;
            //printf("camera x: %f, camera y:%f\n", m_position.x, m_position.y);
            m_needsMatrixUpdate = false;
        }
    }

    glm::vec2 Camera2D::convertScreenToWorld(glm::vec2 screenCoords) {
        // Make it so that 0 is the center
        screenCoords -= glm::vec2(m_screenWidth / 2, m_screenHeight / 2);

        // Scale the coordinates
        screenCoords /= m_scale;

        // Translate with the camera position
        screenCoords += m_position;

        return screenCoords;
    }
}