#pragma once

#include "../include/glm/glm.hpp"
#include "../include/glm/gtc/matrix_transform.hpp"

namespace Engine {

    class Camera2D{
    public:
        Camera2D();
        ~Camera2D();

        void init(int screenWidth, int screenHeight);

        void update();

        glm::vec2 convertScreenToWorld(glm::vec2 screenCoords);

        // Setters
        void setPosition(const glm::vec2& position) { m_position = position; m_needsMatrixUpdate = true; }
        void setScale(float scale) { m_scale = scale; m_needsMatrixUpdate = true; }

        // Getters
        glm::vec2 getPosition() { return m_position; }
        float getScale() { return m_scale; }
        glm::mat4 getCameraMatrix() { return m_cameraMatrix; }

    private:
        int m_screenWidth;
        int m_screenHeight;
        bool m_needsMatrixUpdate;
        float m_scale;
        glm::vec2 m_position;
        glm::mat4 m_cameraMatrix;
        glm::mat4 m_orthoMatrix;

    };
}
