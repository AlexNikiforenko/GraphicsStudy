#pragma once

#include "Engine/Window.h"
#include "Engine/GLSLProgram.h"
#include "Engine/Camera2D.h"
#include "Engine/InputManager.h"
#include "Engine/SpriteBatch.h"

#include "Level.h"
#include "Player.h"

class Zombie;

enum class GameState {
    PLAY,
    EXIT
};

class MainGame {
public:
    MainGame();
    ~MainGame();

    // Runs the game
    void run();
private:
    // Initalizes the core systems
    void initSystems();

    // Initializes the level and sets up everything
    void initLevel();

    // Initializes the shaders
    void initShaders();

    // Main game loop
    void gameLoop();

    // Updates all agents
    void updateAgents();

    // Handles inputs processing
    void processInput();

    // Renders the game
    void drawGame();

    Engine::Window m_Window;

    Engine::GLSLProgram m_TextureProgram;

    Engine::InputManager m_InputManager;

    Engine::Camera2D m_Camera;

    Engine::SpriteBatch m_AgentSpriteBatch; // Draws all agents

    std::vector<Level*> m_Levels;

    int m_ScreenWidth, m_ScreenHeight;

    float m_FPS;

    int m_CurrentLevel;

    Player* m_Player;
    std::vector<Human*> m_Humans;
    std::vector<Zombie*> m_Zombies;

    GameState m_GameState;
};