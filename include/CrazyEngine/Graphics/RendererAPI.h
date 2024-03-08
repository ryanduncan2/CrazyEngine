#ifndef CRAZYENGINE_GRAPHICS_RENDERERAPI_H_
#define CRAZYENGINE_GRAPHICS_RENDERERAPI_H_

#include <cstdint>

#include "CrazyEngine/Math/Vector4.h"

namespace CrazyEngine
{
    enum GraphicsAPI
    {
        NONE, OPENGL, VULKAN
    };

    class RendererAPI
    {
    private:
    
        static GraphicsAPI s_API;

    public:

        RendererAPI() { }
        ~RendererAPI() { }

        virtual void Initialise() = 0;
        virtual void Terminate() = 0;

        virtual void SetViewport(const std::uint32_t x, const std::uint32_t y, const std::uint32_t width, const std::uint32_t height) = 0;
        virtual void SetClearColour(const Vector4& colour) = 0;
        virtual void Clear() = 0;

        virtual void DrawIndexed(std::uint32_t indexCount) = 0;

        static GraphicsAPI GetAPI() { return s_API; }
        static void SetAPI(GraphicsAPI api) { s_API = api; }
        static RendererAPI* Create();
    };
}

#endif