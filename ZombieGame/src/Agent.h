#pragma once

#include "Engine/SpriteBatch.h"

#include "glm/glm.hpp"

const float AGENT_WIDTH = 60;

class Zombie;
class Human;

class Agent {
public:
    Agent();
    virtual ~Agent();

    virtual void update(const std::vector<std::string>& levelData,
                        std::vector<Human*>& humans,
                        std::vector<Zombie*>& zombies) = 0;

    void collideWithLevel(const std::vector<std::string>& levelData);


    void draw(Engine::SpriteBatch& spriteBatch);

    glm::vec2 getPosition() const { return m_Position; };
protected:
    void checkTilePosition(const std::vector<std::string>& levelData,
                           std::vector<glm::vec2>& collideTilePositions,
                           float x, float y);

    void collideWithTile(glm::vec2 tilePos);

    glm::vec2 m_Position;
    Engine::Color m_Color;
    float m_Speed;
};