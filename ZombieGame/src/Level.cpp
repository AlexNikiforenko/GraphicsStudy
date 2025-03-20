#include "Level.h"

#include "Engine/Errors.h"
#include "Engine/ResourceManager.h"

#include <fstream>
#include <iostream>

Level::Level(const std::string& fileName) {

    std::ifstream file(fileName);

    // Error checking
    if (file.fail()) {
        Engine::fatalError("Faild to open " + fileName);
    }

    // Throw away the first string in tmp
    std::string tmp;
    file >> tmp >> m_NumHumans;

    while (std::getline(file, tmp)) {
        m_LevelData.push_back(tmp);
    }

    m_SpriteBatch.init();
    m_SpriteBatch.begin();

    glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);
    Engine::Color whiteColor(255, 255, 255, 255);

    for (int y = 0; y < m_LevelData.size(); y++) {
        for (int x = 0; x < m_LevelData[y].size(); x++) {
            // Grab the tile
            char tile = m_LevelData[y][x];

            // Get dest rect
            glm::vec4 destRect(x * TILE_WIDTH, y * TILE_WIDTH, TILE_WIDTH, TILE_WIDTH);

            // Process the tile
            switch (tile) {
                case 'r':
                case 'R':
                    m_SpriteBatch.draw(destRect,
                                       uvRect,
                                       Engine::ResourceManager::getTexture("../../ZombieGame/Textures/Bricks.png").id,
                                       0.0f,
                                       whiteColor);
                    break;
                case 'L':
                    m_SpriteBatch.draw(destRect,
                                       uvRect,
                                       Engine::ResourceManager::getTexture("../../ZombieGame/Textures/BrickOV.png").id,
                                       0.0f,
                                       whiteColor);
                    break;
                case 'G':
                    m_SpriteBatch.draw(destRect,
                                       uvRect,
                                       Engine::ResourceManager::getTexture("../../ZombieGame/Textures/Glass.png").id,
                                       0.0f,
                                       whiteColor);
                    break;
                case '@':
                    m_LevelData[y][x] = '.'; // We don't collide with @/Z
                    m_StartPlayerPos.x = x * TILE_WIDTH;
                    m_StartPlayerPos.y = y * TILE_WIDTH;
                    break;
                case 'Z':
                    m_LevelData[y][x] = '.';
                    m_ZombieStartPosition.emplace_back(x * TILE_WIDTH, y * TILE_WIDTH);
                    break;
                case '.':
                    break;
                default:
                    printf("Unexpected symbol %c at (%d, %d)", tile, x, y);
                    break;
            }
        }
    }

    m_SpriteBatch.end();
}

Level::~Level() {

}

void Level::draw() {
    m_SpriteBatch.renderBatch();
}