#ifndef MAIN_GAME_H
#define MAIN_GAME_H

#include "Engine/Window.h"
#include "Engine/GLSLProgram.h"
#include "Engine/Sprite.h"
#include "Engine/GLTexture.h"

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

    std::vector<Engine::Sprite*> m_sprites;
    Engine::GLSLProgram m_colorProgram;

    float m_fps;
    float m_maxFPS;
    float m_frame_time;

    float m_time;
};

#endif