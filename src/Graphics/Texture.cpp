#include "CrazyEngine/Graphics/Texture.h"

#include "CrazyEngine/Graphics/RendererAPI.h"
#include "CrazyEngine/Graphics/OpenGL/OpenGLTexture.h"

namespace CrazyEngine
{
    Texture* Texture::CreateFromFile(const char* filePath, FilterType filter)
    {
        switch (RendererAPI::GetAPI())
        {
            case GraphicsAPI::NONE: return nullptr;
            case GraphicsAPI::OPENGL: return OpenGLTexture::CreateFromFile(filePath, filter);
            case GraphicsAPI::VULKAN: return nullptr;
            default: return nullptr;
        }

        return nullptr;
    }

    Texture* Texture::Create(std::uint32_t width, std::uint32_t height, std::uint8_t* data, FilterType filter)
    {
        switch (RendererAPI::GetAPI())
        {
            case GraphicsAPI::NONE: return nullptr;
            case GraphicsAPI::OPENGL: return OpenGLTexture::CreateFromData(width, height, 4, data, filter);
            case GraphicsAPI::VULKAN: return nullptr;
            default: return nullptr;
        }

        return nullptr;
    }

    Texture* Texture::CreateGlyph(std::uint32_t width, std::uint32_t height, std::uint8_t* data, FilterType filter)
    {
        switch (RendererAPI::GetAPI())
        {
            case GraphicsAPI::NONE: return nullptr;
            case GraphicsAPI::OPENGL: return OpenGLTexture::CreateGlyphTexture(width, height, data, filter);
            case GraphicsAPI::VULKAN: return nullptr;
            default: return nullptr;
        }

        return nullptr;
    }

    Texture::Texture()
    {
    }

    Texture::~Texture()
    {
    }
}