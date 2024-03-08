#include "CrazyEngine/Graphics/Texture.h"

#include "CrazyEngine/Graphics/RendererAPI.h"
#include "CrazyEngine/Graphics/OpenGL/OpenGLTexture.h"

namespace CrazyEngine
{
    Texture* Texture::CreateFromFile(const char* filePath)
    {
        switch (RendererAPI::GetAPI())
        {
            case GraphicsAPI::NONE: return nullptr;
            case GraphicsAPI::OPENGL: return new OpenGLTexture(filePath);
            case GraphicsAPI::VULKAN: return nullptr;
            default: return nullptr;
        }

        return nullptr;
    }

    Texture* Texture::Create(std::uint32_t width, std::uint32_t height, std::uint8_t* data)
    {
        switch (RendererAPI::GetAPI())
        {
            case GraphicsAPI::NONE: return nullptr;
            case GraphicsAPI::OPENGL: return new OpenGLTexture(width, height, data);
            case GraphicsAPI::VULKAN: return nullptr;
            default: return nullptr;
        }

        return nullptr;
    }
}