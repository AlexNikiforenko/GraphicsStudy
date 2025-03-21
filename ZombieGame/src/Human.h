#pragma once

#include "Agent.h"

class Human : public Agent {
public:
    Human();
    virtual ~Human();

    void update(const std::vector<std::string>& levelData,
        std::vector<Human*>& humans,
        std::vector<Zombie*>& zombies) override;
};