#include "MainGame.h"
#include "Errors.h"
#include <iostream>
#include <string>

MainGame::MainGame()
    : m_window(nullptr),
    m_screen_width(1024),
    m_screen_height(768),
    m_game_state(GameState::PLAY)
{

}

MainGame::~MainGame()
{
    run();
}

void MainGame::run() {
    initSystems();

    m_sprite.init(-1.0f, -1.0f, 2.0f, 2.0f);
    gameLoop();
}

void MainGame::initSystems() {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        logSDLError("SDL couldn't be initialize!");
        return;
    }

    // Create window
    m_window = SDL_CreateWindow("Game Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_screen_width, m_screen_height, SDL_WINDOW_OPENGL);
    if (!m_window) {
        logSDLError("SDL couldn't create a window!");
        return;
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

    // Set up Glad
    SDL_GLContext gl_context = SDL_GL_CreateContext(m_window);
    if (!gl_context) {
        logSDLError("SDL_GL context couldn't be created!");
        return;
    }

    std::cout << "OpenGL loaded\n";
    gladLoadGLLoader(SDL_GL_GetProcAddress);
    std::cout << "Vendor: " << glGetString(GL_VENDOR) << "\n";
    std::cout << "Renderer: " << glGetString(GL_RENDERER) << "\n";
    std::cout << "Version: " << glGetString(GL_VERSION) << "\n";

    // Set double buffered window
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    // Set the background color
    glClearColor(0.0f, 0.0f, 1.0f, 1.0f);

    GLuint vaoID;
    glGenVertexArrays(1, &vaoID);
    glBindVertexArray(vaoID);

    initShaders();
}

void MainGame::initShaders() {
    m_colorProgram.compileShaders("../Shaders/colorShading.vert", "../Shaders/colorShading.frag");
    m_colorProgram.addAttribute("vertexPosition");
    m_colorProgram.addAttribute("vertexColor");
    m_colorProgram.linkShaders();
}

void MainGame::gameLoop() {
    while (m_game_state != GameState::EXIT) {
        processInput();
        drawGame();
    }
}

void MainGame::processInput() {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        switch (e.type) {
            case SDL_QUIT:
                m_game_state = GameState::EXIT;
                break;
            case SDL_MOUSEMOTION:
                std::cout << e.motion.x << " " << e.motion.y << std::endl;
                break;
        }
    }
}

void MainGame::drawGame() {
    glClearDepth(1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_colorProgram.use();

    m_sprite.draw();

    m_colorProgram.unuse();


    SDL_GL_SwapWindow(m_window);
}
