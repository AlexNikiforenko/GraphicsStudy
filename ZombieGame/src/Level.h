#pragma once

#include "Engine/SpriteBatch.h"

#include <string>
#include <vector>

const int TILE_WIDTH = 64;

class Level {
public:
    // Load the level
    Level(const std::string& fileName);
    ~Level();

    void draw();

    // Getters
    glm::vec2 getStartPlayerPos() const { return m_StartPlayerPos; }
    const std::vector<glm::vec2>& getStartZombiePos() const { return m_ZombieStartPosition; }
    const std::vector<std::string>& getLevelData() const { return m_LevelData; }
private:
    std::vector<std::string> m_LevelData;
    int m_NumHumans;
    Engine::SpriteBatch m_SpriteBatch;

    glm::vec2 m_StartPlayerPos;
    std::vector<glm::vec2> m_ZombieStartPosition;

};