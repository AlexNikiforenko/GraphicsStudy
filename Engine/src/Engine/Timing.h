#pragma once

namespace Engine {
    class FPSLimiter {
    public:
        FPSLimiter();
        ~FPSLimiter();

        void init(float maxFPS);

        void setMaxFPS(float maxFPS);

        void begin();

        // End will return FPS
        float end();
    private:
        void calculateFPS();

        float m_FPS;
        float m_maxFPS;
        float m_frame_time;
        unsigned int m_startTicks;
    };
}