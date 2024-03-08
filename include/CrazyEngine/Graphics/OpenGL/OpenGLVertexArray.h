#ifndef CRAZYENGINE_GRAPHICS_OPENGL_OPENGLVERTEXARRAY_H_
#define CRAZYENGINE_GRAPHICS_OPENGL_OPENGLVERTEXARRAY_H_

#include "CrazyEngine/Graphics/VertexArray.h"
#include "CrazyEngine/Graphics/OpenGL/OpenGLBuffers.h"

namespace CrazyEngine
{
    class OpenGLVertexArray : public VertexArray
    {
    private:

        std::uint32_t m_ArrayID;

        OpenGLVertexBuffer* m_VertexBuffer;
        OpenGLIndexBuffer* m_IndexBuffer;

    public:

        OpenGLVertexArray();
        ~OpenGLVertexArray();

        void Bind() const override;
        void Unbind() const override;

        void SetVertexBuffer(const VertexBuffer* buffer) override;
        void SetIndexBuffer(const IndexBuffer* buffer) override;

        VertexBuffer* GetVertexBuffer() const noexcept override;
        IndexBuffer* GetIndexBuffer() const noexcept override;
    };
}

#endif