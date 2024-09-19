#include "CrazyEngine/Graphics/OpenGL/OpenGLRendererAPI.h"

#include <Vendor/glad/glad.h>

#include <iostream>

namespace CrazyEngine
{
    OpenGLRendererAPI::OpenGLRendererAPI()
    {
    }

    void OpenGLRendererAPI::Initialise()
    {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    void OpenGLRendererAPI::Terminate()
    {
    }

    void OpenGLRendererAPI::SetViewport(const std::uint32_t x, const std::uint32_t y, const std::uint32_t width, const std::uint32_t height)
    {
        glViewport(x, y, width, height);
    }

    void OpenGLRendererAPI::SetClearColour(const Vector4& colour)
    {
        glClearColor(colour.X, colour.Y, colour.Z, colour.W);
    }

    void OpenGLRendererAPI::Clear()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void OpenGLRendererAPI::DrawIndexed(std::uint32_t indexCount)
    {
        glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, nullptr);
    }
}