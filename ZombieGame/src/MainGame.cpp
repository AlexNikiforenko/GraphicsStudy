#include "MainGame.h"

#include "Engine/Engine.h"
#include "Engine/Timing.h"

#include "SDL.h"

#include <filesystem>
#include <iostream>

class Zombie;

MainGame::MainGame() : m_ScreenWidth(1024),
                       m_ScreenHeight(768),
                       m_FPS(0.0f),
                       m_CurrentLevel(0),
                       m_Player(nullptr),
                       m_GameState(GameState::PLAY) {

}

MainGame::~MainGame() {
    for (int i = 0; i < m_Levels.size(); i++)
    {
        delete m_Levels[i];
    }

}

void MainGame::run() {
    initSystems();
    initLevel();

    gameLoop();



}

void MainGame::initSystems() {
    Engine::init();
    m_Window.create("ZombieGame", m_ScreenWidth, m_ScreenHeight, 0);
    glClearColor(0.75f, 0.75f, 0.75f, 1.0f);

    initShaders();

    m_AgentSpriteBatch.init();

    m_Camera.init(m_ScreenWidth, m_ScreenHeight);
}

void MainGame::initLevel() {
    // Level 1
    m_Levels.push_back(new Level("../../ZombieGame/Levels/level1.txt"));
    m_CurrentLevel = 0;

    m_Player = new Player();
    m_Player->init(10.0f, m_Levels[m_CurrentLevel]->getStartPlayerPos(), &m_InputManager);

    m_Humans.push_back(m_Player);

}

void MainGame::initShaders() {
    m_TextureProgram.compileShaders("../../Shaders/colorShading.vert", "../../Shaders/colorShading.frag");
    m_TextureProgram.addAttribute("vertexPosition");
    m_TextureProgram.addAttribute("vertexColor");
    m_TextureProgram.addAttribute("vertexUV");
    m_TextureProgram.linkShaders();
}

void MainGame::gameLoop() {
    Engine::FPSLimiter fpsLimiter;
    fpsLimiter.setMaxFPS(60.0f);

    while (m_GameState == GameState::PLAY) {
        fpsLimiter.begin();

        processInput();
        updateAgents();
        m_Camera.setPosition(m_Player->getPosition());
        m_Camera.update();
        drawGame();

        m_FPS = fpsLimiter.end();
        std::cout << "FPS: " << m_FPS << std::endl;
    }
}

void MainGame::updateAgents() {
    // Update all humans
    for (int i = 0; i < m_Humans.size(); i++)
    {
        m_Humans[i]->update(m_Levels[m_CurrentLevel]->getLevelData(),
                            m_Humans,
                            m_Zombies);
    }

    // TODO: Update zombies

}

void MainGame::processInput() {
    SDL_Event e;

    while (SDL_PollEvent(&e)) {
        switch (e.type) {
            case SDL_QUIT:
                m_GameState = GameState::EXIT;
                break;
            case SDL_MOUSEMOTION:
                m_InputManager.setMouseCoords(e.motion.x, e.motion.y);
                break;
            case SDL_MOUSEBUTTONDOWN:
                m_InputManager.pressKey(e.button.button);
                break;
            case SDL_MOUSEBUTTONUP:
                m_InputManager.releaseKey(e.button.button);
                break;
            case SDL_KEYDOWN:
                m_InputManager.pressKey(e.key.keysym.sym);
                break;
            case SDL_KEYUP:
                m_InputManager.releaseKey(e.key.keysym.sym);
                break;
        }
    }
}

void MainGame::drawGame() {
    // Set the base depth to 1.0
    glClearDepth(1.0f);

    // Clear the color and depth bit
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_TextureProgram.use();

    // Draw code
    glActiveTexture(GL_TEXTURE0);

    // Make sure the shader uses texture 0
    GLint textureUniform = m_TextureProgram.getUniformLocation("mySampler");
    glUniform1i(textureUniform, 0);

    // Grab the camera matrix
    glm::mat4 projectionMatrix = m_Camera.getCameraMatrix();
    GLint pUniform = m_TextureProgram.getUniformLocation("cameraMatrix");
    glUniformMatrix4fv(pUniform, 1, GL_FALSE, &projectionMatrix[0][0]);

    // Draw the level
    m_Levels[m_CurrentLevel]->draw();

    m_AgentSpriteBatch.begin();

    // Draw the humans
    for (int i = 0; i < m_Humans.size(); i++) {
        m_Humans[i]->draw(m_AgentSpriteBatch);
    }

    m_AgentSpriteBatch.end();

    m_AgentSpriteBatch.renderBatch();


    m_TextureProgram.unuse();

    // Swaps buffer and draw to screen
    m_Window.swapBuffer();
}