#include "CrazyEngine/Graphics/OpenGL/OpenGLTexture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "Vendor/stb_image.h"

#include <Vendor/glad/glad.h>
#include <iostream>

namespace CrazyEngine
{
    OpenGLTexture* OpenGLTexture::CreateFromFile(const char* filePath, FilterType filter)
    {
        std::uint32_t width;
        std::uint32_t height;
        std::uint32_t channelCount;
        std::uint8_t* data = stbi_load(filePath, (int*)&width, (int*)&height, (int*)&channelCount, 0);

        OpenGLTexture* texture = OpenGLTexture::CreateFromData(width, height, channelCount, data, filter);

        stbi_image_free(data);

        return texture;
    }

    OpenGLTexture* OpenGLTexture::CreateFromData(std::uint32_t width, std::uint32_t height, std::uint32_t channelCount, std::uint8_t* data, FilterType filter)
    {
        OpenGLTexture* texture = new OpenGLTexture(width, height, channelCount);

        glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
        glGenTextures(1, &texture->m_Handle);
        glBindTexture(GL_TEXTURE_2D, texture->m_Handle);

        GLint minFilter;
        GLint magFilter;

        switch (filter)
        {
            case FilterType::LINEAR: minFilter = GL_LINEAR; magFilter = GL_LINEAR; break;
            case FilterType::NEAREST: minFilter = GL_NEAREST; magFilter = GL_NEAREST; break;
            case FilterType::NEAREST_MIPMAP_NEAREST: minFilter = GL_NEAREST_MIPMAP_NEAREST; magFilter = GL_NEAREST; break;
            case FilterType::NEAREST_MIPMAP_LINEAR: minFilter = GL_NEAREST_MIPMAP_LINEAR; magFilter = GL_NEAREST; break;
            case FilterType::LINEAR_MIPMAP_NEAREST: minFilter = GL_LINEAR_MIPMAP_NEAREST; magFilter = GL_NEAREST; break;
            case FilterType::LINEAR_MIPMAP_LINEAR: minFilter = GL_LINEAR_MIPMAP_LINEAR; magFilter = GL_LINEAR; break;
        }

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

        if (texture->m_ChannelCount == 4)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture->m_Width, texture->m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        }
        else
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, texture->m_Width, texture->m_Height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        }
        
        glGenerateMipmap(GL_TEXTURE_2D);

        glBindTexture(GL_TEXTURE_2D, 0);

        return texture;
    }

    OpenGLTexture* OpenGLTexture::CreateGlyphTexture(std::uint32_t width, std::uint32_t height, std::uint8_t* data, FilterType filter)
    {
        OpenGLTexture* texture = new OpenGLTexture(width, height, 4);

        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        glGenTextures(1, &texture->m_Handle);
        glBindTexture(GL_TEXTURE_2D, texture->m_Handle);

        GLint swizzleMask[] = { GL_ONE, GL_ONE, GL_ONE, GL_RED };

        glTexParameteriv(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_RGBA, swizzleMask);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter == FilterType::NEAREST ? GL_NEAREST : GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter == FilterType::NEAREST ? GL_NEAREST : GL_LINEAR);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, texture->m_Width, texture->m_Height, 0, GL_RED, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glBindTexture(GL_TEXTURE_2D, 0);

        return texture;
    }

    OpenGLTexture::OpenGLTexture(std::uint32_t width, std::uint32_t height, std::uint32_t channelCount)
        : m_Width(width),
          m_Height(height),
          m_ChannelCount(channelCount)
    {
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