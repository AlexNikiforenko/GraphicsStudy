#include "Timing.h"

#include "SDL.h"

namespace Engine {

    FPSLimiter::FPSLimiter() {

    }

    FPSLimiter::~FPSLimiter() {

    }

    void FPSLimiter::init(float maxFPS) {
        setMaxFPS(maxFPS);
    }

    void FPSLimiter::setMaxFPS(float maxFPS) {
        m_maxFPS = maxFPS;
    }

    void FPSLimiter::begin() {
        m_startTicks = SDL_GetTicks();
    }

    float FPSLimiter::end() {
        calculateFPS();

        float frameTicks = SDL_GetTicks() - m_startTicks;
        //Limit FPS to the max FPS
        float desiredFrameTime = 1000.0f / m_maxFPS; // Duration of frame
        if (frameTicks < desiredFrameTime) {
            SDL_Delay(desiredFrameTime - frameTicks);
        }

        return m_FPS;
    }

    void FPSLimiter::calculateFPS() {
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
            m_FPS = 1000.0f / frameTimeAverage;
        }
        else {
            m_FPS = 60.0f;
        }
    }
}