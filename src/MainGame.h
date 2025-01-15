#ifndef MAIN_GAME_H
#define MAIN_GAME_H

#include "GLSLProgram.h"
#include "Sprite.h"
#include "../include/glad/glad.h"
#include "SDL2/SDL.h"

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

    SDL_Window* m_window;
    int m_screen_width;
    int m_screen_height;
    GameState m_game_state;

    Sprite m_sprite;
    GLSLProgram m_colorProgram;

    float m_time;
};

#endif