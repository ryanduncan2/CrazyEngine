#include "CrazyEngine/Graphics/VertexArray.h"

#include "CrazyEngine/Graphics/RendererAPI.h"
#include "CrazyEngine/Graphics/OpenGL/OpenGLVertexArray.h"

namespace CrazyEngine
{
    VertexArray* VertexArray::Create()
    {
        switch (RendererAPI::GetAPI())
        {
            case GraphicsAPI::NONE: return nullptr;
            case GraphicsAPI::OPENGL: return new OpenGLVertexArray();
            case GraphicsAPI::VULKAN: return nullptr;
            default: return nullptr;
        }

        return nullptr;
    }
}