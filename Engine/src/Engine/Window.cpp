#include "Window.h"
#include "Errors.h"

#include <iostream>

namespace Engine {

    Window::Window() {

    }

    Window::~Window() {

    }

    int Window::create(std::string windowName, int screenWidth, int screenHeight, unsigned int currentFlags) {
        unsigned int flags = SDL_WINDOW_OPENGL;

        if (currentFlags & INVISIBLE) {
            flags |= SDL_WINDOW_HIDDEN;
        }
        if (currentFlags & FULLSCREEN) {
            flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
        }
        if (currentFlags & BORDERLESS) {
            flags |= SDL_WINDOW_BORDERLESS;
        }
        // Create window
        m_sdlWindow = SDL_CreateWindow(windowName.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, flags);
        if (!m_sdlWindow) {
            logSDLError("SDL couldn't create a window!");
            return -1;
        }

        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

        // Set up Glad
        SDL_GLContext gl_context = SDL_GL_CreateContext(m_sdlWindow);
        if (!gl_context) {
            logSDLError("SDL_GL context couldn't be created!");
            return -1;
        }

        gladLoadGLLoader(SDL_GL_GetProcAddress);

        std::cout << "OpenGL loaded\n";
        std::cout << "Vendor: " << glGetString(GL_VENDOR) << "\n";
        std::cout << "Renderer: " << glGetString(GL_RENDERER) << "\n";
        std::cout << "Version: " << glGetString(GL_VERSION) << "\n";

        // Set the background color
        glClearColor(0.0f, 0.0f, 1.0f, 1.0f);

        // Set VSync
        SDL_GL_SetSwapInterval(0);

        GLuint vaoID;
        glGenVertexArrays(1, &vaoID);
        glBindVertexArray(vaoID);

        return 0; // TODO: add error codes
    }

    void Window::swapBuffer() {
        SDL_GL_SwapWindow(m_sdlWindow);
    }
}