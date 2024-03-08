#ifndef CRAZYENGINE_GRAPHICS_OPENGL_OPENGLRENDERERAPI_H_
#define CRAZYENGINE_GRAPHICS_OPENGL_OPENGLRENDERERAPI_H_

#include "CrazyEngine/Graphics/RendererAPI.h"

namespace CrazyEngine
{
    class OpenGLRendererAPI : public RendererAPI
    {
    public:
        OpenGLRendererAPI() { }

        void Initialise() override;
        void Terminate() override;

        void SetViewport(const std::uint32_t x, const std::uint32_t y, const std::uint32_t width, const std::uint32_t height) override;
        void SetClearColour(const Vector4& colour) override;
        void Clear() override;

        void DrawIndexed(std::uint32_t indexCount) override;
    };
}

#endif