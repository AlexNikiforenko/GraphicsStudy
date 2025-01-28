#pragma once

#include "../include/glm/glm.hpp"
#include <unordered_map>

namespace Engine {

    class InputManager {
    public:
        InputManager();
        ~InputManager();
        void pressKey(unsigned int keyID);
        void releaseKey(unsigned int keyID);

        void setMouseCoords(float x, float y);

        bool isKeyPressed(unsigned int keyID);

        // Getters
        glm::vec2 getMouseCoords() const { return m_mouseCoords; }
    private:
        std::unordered_map<unsigned int, bool> m_keyMap;

        glm::vec2 m_mouseCoords;
    };
}