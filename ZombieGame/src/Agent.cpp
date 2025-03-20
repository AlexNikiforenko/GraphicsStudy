#include "Agent.h"

#include "Engine/ResourceManager.h"
#include "Level.h"

#include <algorithm>

Agent::Agent() {

}

Agent::~Agent() {

}

void Agent::collideWithLevel(const std::vector<std::string>& levelData) {
    std::vector<glm::vec2> collideTilePositions;

    // Check the four corners

    // First corner
    checkTilePosition(levelData,
                      collideTilePositions,
                      m_Position.x,
                      m_Position.y);

    // Second corner
    checkTilePosition(levelData,
                      collideTilePositions,
                      m_Position.x + AGENT_WIDTH,
                      m_Position.y);

    // Third corner
    checkTilePosition(levelData,
                      collideTilePositions,
                      m_Position.x,
                      m_Position.y + AGENT_WIDTH);
    // Fourth corner
    checkTilePosition(levelData,
                      collideTilePositions,
                      m_Position.x + AGENT_WIDTH,
                      m_Position.y + AGENT_WIDTH);

    for (int i = 0; i < collideTilePositions.size(); i++)
    {
        collideWithTile(collideTilePositions[i]);
    }


}

void Agent::draw(Engine::SpriteBatch& spriteBatch) {

    static int textureID = Engine::ResourceManager::getTexture("../../ZombieGame/Textures/Circle.png").id;

    const glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);
    glm::vec4 destRect(m_Position.x, m_Position.y, AGENT_WIDTH, AGENT_WIDTH);
    printf("m_Color RGBA: %d %d %d %d\n", m_Color.r, m_Color.g, m_Color.b, m_Color.a);

    spriteBatch.draw(destRect, uvRect, textureID, 0.0f, m_Color);
}

// TODO: C++ casting
void Agent::checkTilePosition(const std::vector<std::string>& levelData,
                       std::vector<glm::vec2>& collideTilePositions,
                       float x, float y) {

    glm::vec2 cornerPos = glm::vec2(floor(x / (float)TILE_WIDTH),
                                       floor(y / (float)TILE_WIDTH));

    if (levelData[cornerPos.y][cornerPos.x] != '.') {
        collideTilePositions.push_back(cornerPos * (float)TILE_WIDTH + glm::vec2(TILE_WIDTH / 2.0f));
    }
}

void Agent::collideWithTile(glm::vec2 tilePos) {
    const float AGENT_RADIUS = AGENT_WIDTH / 2.0f;
    const float TILE_RADIUS = TILE_WIDTH / 2.0f;
    const float MIN_DISTANCE = AGENT_RADIUS + TILE_RADIUS;

    glm::vec2 centerPlayerPos = m_Position + glm::vec2(AGENT_RADIUS);
    glm::vec2 distVec = centerPlayerPos - tilePos;

    float xDepth = MIN_DISTANCE - abs(distVec.x);
    float yDepth = MIN_DISTANCE - abs(distVec.y);

    // If this true — we are colliding
    if (xDepth > 0 || yDepth > 0) {
        if (std::max(xDepth, 0.0f) < std::max(yDepth, 0.0f)) {
            if (distVec.x < 0) {
                m_Position.x -= xDepth;
            }
            else {
                m_Position.x += xDepth;
            }
        }
        else {
            if (distVec.y < 0) {
                m_Position.y -= yDepth;
            }
            else {
                m_Position.y += yDepth;
            }
        }
    }
}
