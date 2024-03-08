#ifndef CRAZY_ENGINE_APPLICATION_H_
#define CRAZY_ENGINE_APPLICATION_H_

#include "CrazyEngine/Platform/Platform.h"
#include "CrazyEngine/Core/Clock.h"

namespace CrazyEngine
{
    class Application
    {
    private:

        bool m_ShouldClose = false;

    public:

        Platform m_Platform;
        Clock m_Clock;
        Input m_Input;

        Application(const std::uint32_t width, const std::uint32_t height, const char* title);

        virtual void OnResize(const std::uint32_t width, const std::uint32_t height) { };
        virtual void OnClose(bool shouldClose);

        virtual void Initialise() { };
        virtual void Terminate() { };
        virtual void Update() { };
        virtual void Draw() { };

        void Run();
    };
}

#endif