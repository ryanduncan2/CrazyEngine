#ifndef CRAZYENGINE_PLATFORM_PLATFORM_H_
#define CRAZYENGINE_PLATFORM_PLATFORM_H_

#include <cstdint>
#include <functional>

#include "CrazyEngine/Defines.h"
#include "CrazyEngine/Core/Input.h"

namespace CrazyEngine
{
    // TODO: remove std::optional and find better solution for resizing callback.
    struct Callbacks
    {
        std::function<void(Key, bool)> KeyCallback;
        std::function<void(MouseButton, bool)> MouseButtonCallback;
        std::function<void(int, int)> MousePositionCallback;
        std::function<void(int)> MouseWheelCallback;
        std::function<void(int, int)> WindowResizeCallback;
        std::function<void(bool)> WindowCloseCallback;
    };

    class Platform
    {
    private:
        void* m_InternalState;

    public:
        Platform(const char* appTitle, std::uint32_t x, std::uint32_t y, std::uint32_t width, std::uint32_t height);
        inline ~Platform() { }

        void Terminate();

        void SetCallbacks(Callbacks callbacks);

        double GetAbsoluteTime() const noexcept;
        bool PumpMessages();
        void Sleep(std::uint64_t milliseconds);
        void SwapBuffers();
    };
}

#endif