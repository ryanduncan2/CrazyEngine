#include "CrazyEngine/Graphics/RendererAPI.h"

#include "CrazyEngine/Graphics/OpenGL/OpenGLRendererAPI.h"

namespace CrazyEngine
{
    GraphicsAPI RendererAPI::s_API = GraphicsAPI::NONE;

    RendererAPI::RendererAPI()
    {
    }

    RendererAPI::~RendererAPI()
    {
    }

    RendererAPI* RendererAPI::Create()
    {
        switch (s_API)
        {
            case GraphicsAPI::NONE: return nullptr;
            case GraphicsAPI::OPENGL: 
            {
                OpenGLRendererAPI* rendererAPI = new OpenGLRendererAPI();
                rendererAPI->Initialise();
                return rendererAPI;
            }
            case GraphicsAPI::VULKAN: return nullptr;
            
            default: return nullptr;
        }

        return nullptr;
    }
}