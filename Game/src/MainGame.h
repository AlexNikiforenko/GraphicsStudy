#pragma once

#include "Engine/Window.h"
#include "Engine/GLSLProgram.h"
#include "Engine/Sprite.h"
#include "Engine/GLTexture.h"
#include "Engine/SpriteBatch.h"

#include "Engine/Camera2D.h"

#include "SDL2/SDL.h"

#include <vector>

enum class GameState {
    PLAY,
    EXIT
};

class MainGame {
public:
    MainGame();
    ~MainGame();

    void run();


private:
    void initSystems();
    void initShaders();
    void gameLoop();
    void processInput();
    void drawGame();
    void calculateFPS();

    Engine::Window m_window;
    int m_screenWidth;
    int m_screenHeight;
    GameState m_game_state;

    Engine::GLSLProgram m_colorProgram;
    Engine::Camera2D m_camera;

    Engine::SpriteBatch m_spriteBatch;

    float m_fps;
    float m_maxFPS;
    float m_frame_time;

    float m_time;
};
