#include "MainGame.h"

#include "Engine/Engine.h"
#include "Engine/Errors.h"
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
    for (auto& sprite : m_sprites) {
        delete sprite;
    }
}

void MainGame::run() {
    initSystems();
    m_sprites.push_back(new Engine::Sprite(0.0f, 0.0f, m_screenWidth / 2, m_screenWidth / 2, "../Textures/Duck/Sprites/Idle/Idle 002.png"));
    m_sprites.push_back(new Engine::Sprite(m_screenWidth / 2, 0.0f, m_screenWidth / 2, m_screenWidth / 2, "../Textures/Duck/Sprites/Idle/Idle 002.png"));

    // Centres camera's position
    m_camera.setPosition(m_camera.getPosition() + glm::vec2(m_screenWidth / 2.0f, m_screenHeight / 2.0f));
    gameLoop();
}

void MainGame::initSystems() {
    Engine::init();
    m_camera.init(m_screenWidth, m_screenHeight);

    m_window.create("GameEngine", m_screenWidth, m_screenHeight, 0);

    initShaders();
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
        float startTicks = SDL_GetTicks();

        processInput();
        m_time += 0.001;
        m_camera.update();
        drawGame();
        calculateFPS();

        // prints once per 10 frames
        static int frameCounter = 0;
        frameCounter++;
        if (frameCounter == 10) {
            std::cout << "FPS: " << m_fps << std::endl;
            frameCounter = 0;
        }

        float frameTicks = SDL_GetTicks() - startTicks;

        // Limit FPS to the max FPS
        // if (1000.0f / m_maxFPS > frameTicks) {
        //     SDL_Delay(1000.0f / m_maxFPS - frameTicks);
        // }
    }
}

void MainGame::processInput() {
    SDL_Event e;

    const float CAMERA_SPEED = 20.0f;
    const float SCALE_SPEED = 0.1f;

    while (SDL_PollEvent(&e)) {
        switch (e.type) {
            case SDL_QUIT:
                m_game_state = GameState::EXIT;
                break;
            case SDL_MOUSEMOTION:
                //std::cout << e.motion.x << " " << e.motion.y << std::endl;
                break;
            case SDL_KEYDOWN:
                switch (e.key.keysym.sym) {
                    case SDLK_w:
                        m_camera.setPosition(m_camera.getPosition() + glm::vec2(0.0f, CAMERA_SPEED));
                        break;
                     case SDLK_s:
                        m_camera.setPosition(m_camera.getPosition() + glm::vec2(0.0f, -CAMERA_SPEED));
                        break;
                     case SDLK_a:
                        m_camera.setPosition(m_camera.getPosition() + glm::vec2(-CAMERA_SPEED, 0.0f));
                        break;
                     case SDLK_d:
                        m_camera.setPosition(m_camera.getPosition() + glm::vec2(CAMERA_SPEED, 0.0f));
                        break;
                     case SDLK_q:
                        m_camera.setScale(m_camera.getScale() + SCALE_SPEED);
                        break;
                     case SDLK_e:
                        m_camera.setScale(m_camera.getScale() - SCALE_SPEED);
                        break;
                }
                break;
        }
    }
}

void MainGame::drawGame() {
    glClearDepth(1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_colorProgram.use();
    glActiveTexture(GL_TEXTURE0);
    GLint textureLocation = m_colorProgram.getUniformLocation("mySampler");
    glUniform1i(textureLocation, 0);

    // Set constantly changing time value
    GLint timeLocation = m_colorProgram.getUniformLocation("time");
    glUniform1f(timeLocation, m_time);

    // Set the camera matrix
    GLint pLocation = m_colorProgram.getUniformLocation("P");
    glm::mat4 cameraMatrix = m_camera.getCameraMatrix();
    glUniformMatrix4fv(pLocation, 1, GL_FALSE, &cameraMatrix[0][0]);

    for (Engine::Sprite*& sprite : m_sprites) {
        sprite->draw();
    }

    glBindTexture(GL_TEXTURE_2D, 0);
    m_colorProgram.unuse();

    m_window.swapBuffer();
}

void MainGame::calculateFPS() {
    static const int NUM_SAMPLES = 10;
    static float frameTimes[NUM_SAMPLES];
    static int currentFrame = 0;

    static float prevTicks = SDL_GetTicks();
    float currentTicks = SDL_GetTicks();

    m_frame_time = currentTicks - prevTicks;
    frameTimes[currentFrame % NUM_SAMPLES] = m_frame_time;

    prevTicks = currentTicks;

    int count;

    currentFrame++;
    if (currentFrame < NUM_SAMPLES) {
        count = currentFrame;
    }
    else {
        count = NUM_SAMPLES;
    }

    float frameTimeAverage = 0.0f;
    for (int i = 0; i < count; i++) {
        frameTimeAverage += frameTimes[i];
    }
    frameTimeAverage /= count;

    if (frameTimeAverage > 0) {
        m_fps = 1000.0f / frameTimeAverage;
    }
    else {
        m_fps = 60.0f;
    }

}