#pragma once

#include "Engine/InputManager.h"

#include "Human.h"


class Player : public Human {
public:
    Player();
    ~Player();

    void init(float speed, glm::vec2 position, Engine::InputManager* inputManager);

    void update(const std::vector<std::string>& levelData,
        std::vector<Human*>& humans,
        std::vector<Zombie*>& zombies) override;
private:
    Engine::InputManager* m_InputManager;
};