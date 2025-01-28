#include "Bullet.h"

#include "Engine/GLTexture.h"
#include "Engine/ResourceManager.h"

Bullet::Bullet(glm::vec2 position, glm::vec2 direction, float speed, int lifeTime)
    : m_position(position), m_direction(direction), m_speed(speed), m_lifeTime(lifeTime) {

}

Bullet::~Bullet() {

}

void Bullet::draw(Engine::SpriteBatch& spriteBatch) {
    glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);
    static Engine::GLTexture texture = Engine::ResourceManager::getTexture("../../Textures/Duck/Sprites/Idle/Idle 002.png");
    Engine::Color color(255, 255, 255, 255);

    glm::vec4 posAndSize(m_position.x, m_position.y, 30, 30);

    spriteBatch.draw(posAndSize, uv, texture.id, 0.0f, color);
}

bool Bullet::update() {
    m_position += m_direction * m_speed;
    m_lifeTime--;
    if (m_lifeTime == 0) {
        return true;
    }
    return false;
}