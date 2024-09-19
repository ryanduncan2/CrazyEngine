#include "CrazyEngine/Graphics/Buffers.h"

#include "CrazyEngine/Graphics/RendererAPI.h"
#include "CrazyEngine/Graphics/OpenGL/OpenGLBuffers.h"

namespace CrazyEngine
{
    IndexBuffer::IndexBuffer()
    {
    }

    IndexBuffer::~IndexBuffer()
    {
    }

    IndexBuffer* IndexBuffer::Create(std::uint32_t* indices, std::uint32_t count)
    {
        switch (RendererAPI::GetAPI())
        {
            case GraphicsAPI::NONE: return nullptr;
            case GraphicsAPI::OPENGL: return new OpenGLIndexBuffer(indices, count);
            case GraphicsAPI::VULKAN: return nullptr;
            default: return nullptr;
        }

        return nullptr;
    }

    VertexBuffer::VertexBuffer()
    {
    }

    VertexBuffer::~VertexBuffer()
    {
    }

    VertexBuffer* VertexBuffer::Create(std::uint32_t size)
    {
        switch (RendererAPI::GetAPI())
        {
            case GraphicsAPI::NONE: return nullptr;
            case GraphicsAPI::OPENGL: return new OpenGLVertexBuffer(size);
            case GraphicsAPI::VULKAN: return nullptr;
            default: return nullptr;
        }

        return nullptr;
    }
}