#include "InputManager.h"

namespace Engine {

    InputManager::InputManager() : m_mouseCoords(0.0f) {

    }

    InputManager::~InputManager() {

    }

    void InputManager::pressKey(unsigned int keyID) {
        m_keyMap[keyID] = true;
    }

    void InputManager::releaseKey(unsigned int keyID) {
        m_keyMap[keyID] = false;
    }

    void InputManager::setMouseCoords(float x, float y) {
        m_mouseCoords.x = x;
        m_mouseCoords.y = y;
    }

    bool InputManager::isKeyPressed(unsigned int keyID) {
        auto it = m_keyMap.find(keyID);
        if (it != m_keyMap.end()) {
            return it->second;
        }
        return false;
    }
}