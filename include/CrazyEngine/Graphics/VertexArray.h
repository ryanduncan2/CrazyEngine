#ifndef CRAZYENGINE_GRAPHICS_VERTEXARRAY_H_
#define CRAZYENGINE_GRAPHICS_VERTEXARRAY_H_

#include "CrazyEngine/Graphics/Buffers.h"

namespace CrazyEngine
{
    class VertexArray
    {
    public:
    
        static VertexArray* Create();
    
        VertexArray();
        ~VertexArray();

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        virtual void SetVertexBuffer(const VertexBuffer* buffer) = 0;
        virtual void SetIndexBuffer(const IndexBuffer* buffer) = 0;

        virtual VertexBuffer* GetVertexBuffer() const noexcept = 0;
        virtual IndexBuffer* GetIndexBuffer() const noexcept = 0;
    };
}

#endif