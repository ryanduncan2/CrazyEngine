#ifndef CRAZYENGINE_GRAPHICS_OPENGL_OPENGLTEXTURE_H_
#define CRAZYENGINE_GRAPHICS_OPENGL_OPENGLTEXTURE_H_

#include "CrazyEngine/Graphics/Texture.h"

namespace CrazyEngine
{
    class OpenGLTexture : public Texture
    {
    private:

        std::uint32_t m_Handle;
        std::uint32_t m_Width;
        std::uint32_t m_Height;
        std::uint32_t m_ChannelCount;

    public:

        OpenGLTexture(const char* filePath);
        OpenGLTexture(std::uint32_t width, std::uint32_t height, std::uint8_t* data);
        ~OpenGLTexture();

        inline std::uint32_t GetHandle() const override { return m_Handle; }
        inline std::uint32_t GetWidth() const override { return m_Width; }
        inline std::uint32_t GetHeight() const override { return m_Height; }

        void Bind(std::uint32_t slot) const override;
        void SetData(void* data, std::uint32_t size) override;

        bool operator==(const Texture& texture) const override;
        bool operator!=(const Texture& texture) const override;
    };
}

#endif