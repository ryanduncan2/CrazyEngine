#ifndef CRAZYENGINE_GRAPHICS_BUFFERS_H_
#define CRAZYENGINE_GRAPHICS_BUFFERS_H_

#define MAX_QUADS 1024

#include <cstdint>

#include "CrazyEngine/Graphics/Vertex.h"
#include "CrazyEngine/Graphics/BufferLayout.h"

namespace CrazyEngine
{
    class IndexBuffer
    {
    public:

        IndexBuffer() { }
        ~IndexBuffer() { }

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;
        
        virtual std::uint32_t GetCount() const = 0;

        static IndexBuffer* Create(std::uint32_t* indices, std::uint32_t count);
    };

    class VertexBuffer
    {
    public:

        VertexBuffer() { }
        ~VertexBuffer() { }

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        virtual BufferLayout GetLayout() const = 0;

        virtual void SetData(const void* data, std::uint32_t size) = 0;
        virtual void SetLayout(const BufferLayout& layout) = 0;

        static VertexBuffer* Create(std::uint32_t size);
    };
}

#endif