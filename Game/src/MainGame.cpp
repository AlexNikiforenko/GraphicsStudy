#include "MainGame.h"

#include "Engine/Engine.h"
#include "Engine/Errors.h"
#include "Engine/ResourceManager.h"
#include "SDL_image.h"

#include <iostream>
#include <string>

MainGame::MainGame()
    : m_screenWidth(1024),
    m_screenHeight(768),
    m_game_state(GameState::PLAY),
    m_time(0.0f),
    m_maxFPS(60.0f)
{
    run();
}

MainGame::~MainGame()
{

}

void MainGame::run() {
    initSystems();

    // Centres camera's position
    //m_camera.setPosition(m_camera.getPosition() + glm::vec2(m_screenWidth / 2.0f, m_screenHeight / 2.0f));

    gameLoop();
}

void MainGame::initSystems() {
    Engine::init();
    m_camera.init(m_screenWidth, m_screenHeight);

    m_window.create("GameEngine", m_screenWidth, m_screenHeight, 0);

    initShaders();
    m_spriteBatch.init();
    m_fpsLimiter.init(m_maxFPS);
}

void MainGame::initShaders() {
    m_colorProgram.compileShaders("../Shaders/colorShading.vert", "../Shaders/colorShading.frag");
    m_colorProgram.addAttribute("vertexPosition");
    m_colorProgram.addAttribute("vertexColor");
    m_colorProgram.addAttribute("vertexUV");
    m_colorProgram.linkShaders();
}

void MainGame::gameLoop() {
    while (m_game_state != GameState::EXIT) {
        // Used for frame time measuring
        m_fpsLimiter.begin();

        processInput();
        m_time += 0.001;

        m_camera.update();

        // Update bullets
        for (int i = 0; i < m_bullets.size();) {
            if (m_bullets[i].update()) {
                m_bullets[i] = m_bullets.back();
                m_bullets.pop_back();
            }
            else {
                i++;
            }
        }
        drawGame();

        m_FPS = m_fpsLimiter.end();

        // prints once per 10 frames
        static int frameCounter = 0;
        frameCounter++;
        if (frameCounter == 10000) {
            std::cout << "FPS: " << m_FPS << std::endl;
            frameCounter = 0;
        }
    }
}

void MainGame::processInput() {
    SDL_Event e;

    const float CAMERA_SPEED = 0.2f;
    const float SCALE_SPEED = 0.001f;

    while (SDL_PollEvent(&e)) {
        switch (e.type) {
            case SDL_QUIT:
                m_game_state = GameState::EXIT;
                break;
            case SDL_KEYDOWN:
                m_inputManager.pressKey(e.key.keysym.sym);
                break;
            case SDL_KEYUP:
                m_inputManager.releaseKey(e.key.keysym.sym);
                break;
            case SDL_MOUSEBUTTONDOWN:
                m_inputManager.pressKey(e.button.button);
                break;
             case SDL_MOUSEBUTTONUP:
                m_inputManager.releaseKey(e.button.button);
                break;
            case SDL_MOUSEMOTION:
                m_inputManager.setMouseCoords(e.motion.x, e.motion.y);
                break;
        }
    }

    if (m_inputManager.isKeyPressed(SDLK_w)) {
        m_camera.setPosition(m_camera.getPosition() + glm::vec2(0.0f, CAMERA_SPEED));
    }
    if (m_inputManager.isKeyPressed(SDLK_s)) {
        m_camera.setPosition(m_camera.getPosition() + glm::vec2(0.0f, -CAMERA_SPEED));
    }
    if (m_inputManager.isKeyPressed(SDLK_a)) {
        m_camera.setPosition(m_camera.getPosition() + glm::vec2(-CAMERA_SPEED, 0.0f));
    }
    if (m_inputManager.isKeyPressed(SDLK_d)) {
        m_camera.setPosition(m_camera.getPosition() + glm::vec2(CAMERA_SPEED, 0.0f));
    }
    if (m_inputManager.isKeyPressed(SDLK_q)) {
        m_camera.setScale(m_camera.getScale() * (1 + SCALE_SPEED));
    }
    if (m_inputManager.isKeyPressed(SDLK_e)) {
        m_camera.setScale(m_camera.getScale() * (1 - SCALE_SPEED));
    }

    if (m_inputManager.isKeyPressed(SDL_BUTTON_LEFT)) {
        glm::vec2 mouseCoords = m_inputManager.getMouseCoords();
        mouseCoords = m_camera.convertScreenToWorld(mouseCoords);

        glm::vec2 playerPosition(0.0f);
        glm::vec2 direction = mouseCoords - playerPosition;
        direction = glm::normalize(direction);

        m_bullets.emplace_back(playerPosition, direction, 1.0f, 1000);
    }

}

void MainGame::drawGame() {
    // Set the base depth to 1.0
    glClearDepth(1.0f);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Enable the shader
    m_colorProgram.use();

    glActiveTexture(GL_TEXTURE0);
    GLint textureLocation = m_colorProgram.getUniformLocation("mySampler");
    glUniform1i(textureLocation, 0);

    // Set constantly changing time value
    // GLint timeLocation = m_colorProgram.getUniformLocation("time");
    // glUniform1f(timeLocation, m_time);

    // Set the camera matrix
    GLint pLocation = m_colorProgram.getUniformLocation("cameraMatrix");
    glm::mat4 cameraMatrix = m_camera.getCameraMatrix();
    glUniformMatrix4fv(pLocation, 1, GL_FALSE, &cameraMatrix[0][0]);

    m_spriteBatch.begin();

    glm::vec4 pos(0.0f, 0.0f, 50.0f, 50.0f);
    glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);
    static Engine::GLTexture texture = Engine::ResourceManager::getTexture("../../Textures/Duck/Sprites/Idle/Idle 002.png");
    Engine::Color color(255, 255, 255, 255);

    m_spriteBatch.draw(pos, uv, texture.id, 0.0f, color);

    for (Bullet& b : m_bullets) {
        b.draw(m_spriteBatch);
    }

    m_spriteBatch.end();

    m_spriteBatch.renderBatch();

    glBindTexture(GL_TEXTURE_2D, 0);

    // Disable the shader
    m_colorProgram.unuse();

    m_window.swapBuffer();
}
