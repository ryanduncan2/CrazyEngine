#include "CrazyEngine/Application.h"

#include <functional>
#include <Vendor/glad/glad.h>

#include "CrazyEngine/Graphics/Renderer2D.h"
#include "CrazyEngine/Graphics/Texture.h"

namespace CrazyEngine
{
    Application::Application(const std::uint32_t width, const std::uint32_t height, const char* title) : m_Platform(title, 40, 40, width, height)
    {
        m_Input.Initialise();

        Callbacks callbacks { };
        callbacks.KeyCallback = std::bind(&Input::ProcessKeyboardInput, &m_Input, std::placeholders::_1, std::placeholders::_2);
        callbacks.MouseButtonCallback = std::bind(&Input::ProcessMouseButtonInput, &m_Input, std::placeholders::_1, std::placeholders::_2);
        callbacks.MousePositionCallback = std::bind(&Input::ProcessMouseMovement, &m_Input, std::placeholders::_1, std::placeholders::_2);
        callbacks.WindowResizeCallback = std::bind(&Application::OnResize, this, std::placeholders::_1, std::placeholders::_2);
        callbacks.WindowCloseCallback = std::bind(&Application::OnClose, this, std::placeholders::_1);
        m_Platform.SetCallbacks(callbacks);
    }

    void Application::OnClose(bool shouldClose)
    {
        m_ShouldClose = shouldClose;
    }

    void Application::Run()
    {
        Initialise();

        while (!m_ShouldClose)
        {
            m_Platform.PumpMessages();
            m_Clock.Update(m_Platform);
            m_Input.Update();

            Update();
            Draw();

            m_Platform.SwapBuffers();
        }

        m_Platform.Terminate();
    }
}