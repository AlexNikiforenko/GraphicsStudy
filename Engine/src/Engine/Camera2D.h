#ifndef CAMERA2D_H
#define CAMERA2D_H

#include "../include/glm/glm.hpp"
#include "../include/glm/gtc/matrix_transform.hpp"

namespace Engine {

    class Camera2D{
    public:
        Camera2D();
        ~Camera2D();

        void init(int screenWidth, int screenHeight);

        void update();

        // Setters
        void setPosition(const glm::vec2& m_position);
        void setScale(float m_scale);

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

#endif