#ifndef CRAZYENGINE_GRAPHICS_OPENGL_OPENGLBUFFERS_H_
#define CRAZYENGINE_GRAPHICS_OPENGL_OPENGLBUFFERS_H_

#include "CrazyEngine/Graphics/Buffers.h"

namespace CrazyEngine
{
    class OpenGLVertexBuffer : public VertexBuffer
    {
    private:
    
        std::uint32_t m_BufferID;
        BufferLayout m_Layout;

    public:

        OpenGLVertexBuffer(std::uint32_t size);
        ~OpenGLVertexBuffer();

        void Bind() const override;
        void Unbind() const override;

        BufferLayout GetLayout() const override { return m_Layout; }

        void SetData(const void* data, std::uint32_t size) override;
        void SetLayout(const BufferLayout& layout) override;
    };

    class OpenGLIndexBuffer : public IndexBuffer
    {
    private:

        std::uint32_t m_BufferID;
        std::uint32_t m_Count;

    public:

        OpenGLIndexBuffer(std::uint32_t* indices, std::uint32_t count);
        ~OpenGLIndexBuffer();

        void Bind() const override;
        void Unbind() const override;
        
        std::uint32_t GetCount() const noexcept override;
    };
}

#endif