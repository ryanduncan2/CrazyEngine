#include "CrazyEngine/Graphics/Shader.h"

#include "CrazyEngine/Graphics/RendererAPI.h"
#include "CrazyEngine/Graphics/OpenGL/OpenGLShader.h"

namespace CrazyEngine
{
    Shader* Shader::Create(const char* vertexFilePath, const char* fragmentFilePath)
    {
        switch (RendererAPI::GetAPI())
        {
            case GraphicsAPI::NONE: return nullptr;
            case GraphicsAPI::OPENGL: return new OpenGLShader(vertexFilePath, fragmentFilePath);
            case GraphicsAPI::VULKAN: return nullptr;
            default: return nullptr;
        }

        return nullptr;
    }

    Shader* Shader::Create(const char* vertexFilePath, const char* fragmentFilePath, int textureSlots)
    {
        switch (RendererAPI::GetAPI())
        {
            case GraphicsAPI::NONE: return nullptr;
            case GraphicsAPI::OPENGL: return new OpenGLShader(vertexFilePath, fragmentFilePath, textureSlots);
            case GraphicsAPI::VULKAN: return nullptr;
            default: return nullptr;
        }

        return nullptr;
    }

    Shader::Shader()
    {
    }

    Shader::~Shader()
    {
    }
}