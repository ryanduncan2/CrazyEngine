#include "CrazyEngine/Graphics/RendererState.h"

namespace CrazyEngine
{
    RendererState::RendererState(int maxQuads, int maxTextures, const BufferLayout& layout)
    {
        m_VBO = VertexBuffer::Create(layout.GetSize() * 4 * maxQuads);
        m_VBO->SetLayout(layout);

        m_VAO = VertexArray::Create();
        m_VAO->SetVertexBuffer(m_VBO);

        std::uint32_t indices[MAX_QUADS * 6];
        std::uint32_t offset = 0;

        for (int i = 0; i < MAX_QUADS * 6; i += 6)
        {
            indices[i + 0] = offset + 0;
            indices[i + 1] = offset + 1;
            indices[i + 2] = offset + 2;
            indices[i + 3] = offset + 2;
            indices[i + 4] = offset + 3;
            indices[i + 5] = offset + 0;

            offset += 4;
        }

        m_EBO = IndexBuffer::Create(indices, MAX_QUADS * 6);
        
        m_VBO->Unbind();
        m_VAO->Unbind();
    }

    RendererState::~RendererState()
    {
        delete m_Shader;
        
        delete m_VAO;
        delete m_VBO;
        delete m_EBO;
    }

    void RendererState::SetShader(Shader* shader)
    {
        m_Shader = shader;
    }

    void RendererState::SetVertexBufferData(const void* data, std::uint32_t size)
    {
        m_VBO->SetData(data, size);
    }

    void RendererState::SetProjection(Matrix4 projectionMatrix)
    {
        m_Shader->SetMatrix4("u_Projection", projectionMatrix);
    }

    void RendererState::Bind()
    {
        m_Shader->Bind();
        m_VAO->Bind();
    }

    void RendererState::Unbind()
    {
        m_Shader->Unbind();
        m_VAO->Unbind();
    }
}