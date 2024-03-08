#ifndef CRAZYENGINE_GRAPHICS_TEXTURE_H_
#define CRAZYENGINE_GRAPHICS_TEXTURE_H_

#include <cstdint>

namespace CrazyEngine
{
    class Texture
    {
    public:

        Texture() { }
        ~Texture() { }

        virtual std::uint32_t GetWidth() const = 0;
        virtual std::uint32_t GetHeight() const = 0;
        virtual std::uint32_t GetHandle() const = 0;

        virtual void Bind(std::uint32_t slot) const = 0;
        virtual void SetData(void* data, std::uint32_t size) = 0;

        virtual bool operator==(const Texture& texture) const = 0;
        virtual bool operator!=(const Texture& texture) const = 0;

        static Texture* CreateFromFile(const char* filePath);
        static Texture* Create(std::uint32_t width, std::uint32_t height, std::uint8_t* data);
    };
}

#endif