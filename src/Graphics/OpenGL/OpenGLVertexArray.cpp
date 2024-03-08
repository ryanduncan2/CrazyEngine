#include "CrazyEngine/Graphics/OpenGL/OpenGLVertexArray.h"

#include "CrazyEngine/Graphics/Vertex.h"

#include <Vendor/glad/glad.h>

namespace CrazyEngine
{
    OpenGLVertexArray::OpenGLVertexArray()
    {
        glGenVertexArrays(1, &m_ArrayID);
        glBindVertexArray(m_ArrayID);
    }

    OpenGLVertexArray::~OpenGLVertexArray()
    {
        glDeleteVertexArrays(1, &m_ArrayID);
    }

    void OpenGLVertexArray::Bind() const
    {
        glBindVertexArray(m_ArrayID);
    }

    void OpenGLVertexArray::Unbind() const
    {
        glBindVertexArray(0);
    }

    void OpenGLVertexArray::SetVertexBuffer(const VertexBuffer* buffer)
    {
        m_VertexBuffer = (OpenGLVertexBuffer*)buffer;

        glBindVertexArray(m_ArrayID);
        m_VertexBuffer->Bind();

        std::vector<BufferElement> layout = m_VertexBuffer->GetLayout().GetElements();
        for (std::size_t i = 0; i < layout.size(); ++i)
        {
            switch (layout[i].Type)
            {
                case ShaderDataType::FLOAT:
                {
                    glEnableVertexAttribArray(i);
                    glVertexAttribPointer(i, 1, GL_FLOAT, GL_FALSE, m_VertexBuffer->GetLayout().GetSize(), (const void*)(layout[i].Offset));
                } break;
                case ShaderDataType::FLOAT2:
                {
                    glEnableVertexAttribArray(i);
                    glVertexAttribPointer(i, 2, GL_FLOAT, GL_FALSE, m_VertexBuffer->GetLayout().GetSize(), (const void*)(layout[i].Offset));
                } break;
                case ShaderDataType::FLOAT3:
                {
                    glEnableVertexAttribArray(i);
                    glVertexAttribPointer(i, 3, GL_FLOAT, GL_FALSE, m_VertexBuffer->GetLayout().GetSize(), (const void*)(layout[i].Offset));
                } break;
                case ShaderDataType::FLOAT4:
                {
                    glEnableVertexAttribArray(i);
                    glVertexAttribPointer(i, 4, GL_FLOAT, GL_FALSE, m_VertexBuffer->GetLayout().GetSize(), (const void*)(layout[i].Offset));
                } break;
                case ShaderDataType::MAT3:
                {
                } break;
                case ShaderDataType::MAT4:
                {
                } break;
                case ShaderDataType::INT:
                {
                    glEnableVertexAttribArray(i);
                    glVertexAttribPointer(i, 1, GL_INT, GL_FALSE, m_VertexBuffer->GetLayout().GetSize(), (const void*)(layout[i].Offset));
                } break;
                case ShaderDataType::INT2:
                {
                    glEnableVertexAttribArray(i);
                    glVertexAttribPointer(i, 2, GL_INT, GL_FALSE, m_VertexBuffer->GetLayout().GetSize(), (const void*)(layout[i].Offset));
                } break;
                case ShaderDataType::INT3:
                {
                    glEnableVertexAttribArray(i);
                    glVertexAttribPointer(i, 3, GL_INT, GL_FALSE, m_VertexBuffer->GetLayout().GetSize(), (const void*)(layout[i].Offset));
                } break;
                case ShaderDataType::INT4:
                {
                    glEnableVertexAttribArray(i);
                    glVertexAttribPointer(i, 4, GL_INT, GL_FALSE, m_VertexBuffer->GetLayout().GetSize(), (const void*)(layout[i].Offset));
                } break;
                case ShaderDataType::BOOL:
                {
                    glEnableVertexAttribArray(i);
                    glVertexAttribPointer(i, 1, GL_BOOL, GL_FALSE, m_VertexBuffer->GetLayout().GetSize(), (const void*)(layout[i].Offset));
                } break;
            }
        }
    }

    void OpenGLVertexArray::SetIndexBuffer(const IndexBuffer* buffer)
    {
        m_IndexBuffer = (OpenGLIndexBuffer*)buffer;
    }

    VertexBuffer* OpenGLVertexArray::GetVertexBuffer() const noexcept
    {
        return m_VertexBuffer;
    }

    IndexBuffer* OpenGLVertexArray::GetIndexBuffer() const noexcept
    {
        return m_IndexBuffer;
    }
}