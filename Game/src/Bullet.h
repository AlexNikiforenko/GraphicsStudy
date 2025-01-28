#pragma once

#include "glm/glm.hpp"
#include "Engine/SpriteBatch.h"

class Bullet {
public:
    Bullet(glm::vec2 position, glm::vec2 direction, float speed, int lifeTime);
    ~Bullet();

    void init(glm::vec2 position, glm::vec2 direction, float speed, int lifeTime);
    void draw(Engine::SpriteBatch& spriteBatch);
    // Returns true when object is out of lifetime
    bool update();

private:
    int m_lifeTime;
    float m_speed;
    glm::vec2 m_direction;
    glm::vec2 m_position;
};