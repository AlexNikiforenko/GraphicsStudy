#include "Player.h"

#include <SDL.h>

Player::Player() {

}

Player::~Player() {

}

void Player::init(float speed, glm::vec2 position, Engine::InputManager* inputManager) {
    m_Speed = speed;
    m_Position = position;
    m_Color.setColor(0, 0, 185, 255);
    m_InputManager = inputManager;
}

void Player::update(const std::vector<std::string>& levelData,
                    std::vector<Human*>& humans,
                    std::vector<Zombie*>& zombies) {

    if (m_InputManager->isKeyPressed(SDLK_w)) {
        m_Position.y += m_Speed;
    }
    if (m_InputManager->isKeyPressed(SDLK_s)) {
        m_Position.y -= m_Speed;
    }
    if (m_InputManager->isKeyPressed(SDLK_a)) {
        m_Position.x -= m_Speed;
    }
    if (m_InputManager->isKeyPressed(SDLK_d)) {
        m_Position.x += m_Speed;
    }

    collideWithLevel(levelData);
}