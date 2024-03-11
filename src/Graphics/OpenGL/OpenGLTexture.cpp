#include "CrazyEngine/Graphics/OpenGL/OpenGLTexture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "Vendor/stb_image.h"

#include <Vendor/glad/glad.h>
#include <iostream>

namespace CrazyEngine
{
    OpenGLTexture::OpenGLTexture(const char* filePath)
    {
        std::uint8_t* data = stbi_load(filePath, (int*)&m_Width, (int*)&m_Height, (int*)&m_ChannelCount, 0);
        
        glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
        glGenTextures(1, &m_Handle);
        glBindTexture(GL_TEXTURE_2D, m_Handle);

        // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, m_Width, m_Height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glBindTexture(GL_TEXTURE_2D, 0);

        stbi_image_free(data);
    }

    OpenGLTexture::OpenGLTexture(std::uint32_t width, std::uint32_t height, std::uint8_t* data) : m_Width(width), m_Height(height)
    {
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        glGenTextures(1, &m_Handle);
        glBindTexture(GL_TEXTURE_2D, m_Handle);

        GLint swizzleMask[] = { GL_ONE, GL_ONE, GL_ONE, GL_RED };

        glTexParameteriv(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_RGBA, swizzleMask);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, m_Width, m_Height, 0, GL_RED, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glBindTexture(GL_TEXTURE_2D, 0);
    }

    OpenGLTexture::~OpenGLTexture()
    {
        glDeleteTextures(1, &m_Handle);
    }

    void OpenGLTexture::Bind(std::uint32_t slot) const
    {
        glActiveTexture(GL_TEXTURE0 + slot);
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, m_Handle);
    }

    void OpenGLTexture::SetData(void* data, std::uint32_t size)
    {
    }

    bool OpenGLTexture::operator==(const Texture& texture) const
    {
        return m_Handle == texture.GetHandle();
    }

    bool OpenGLTexture::operator!=(const Texture& texture) const
    {
        return m_Handle != texture.GetHandle();
    }
}