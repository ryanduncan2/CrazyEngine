#ifndef CRAZYENGINE_GRAPHICS_RENDERER_STATE_H_
#define CRAZYENGINE_GRAPHICS_RENDERER_STATE_H_

#include "CrazyEngine/Graphics/Shader.h"
#include "CrazyEngine/Graphics/Buffers.h"
#include "CrazyEngine/Graphics/VertexArray.h"

namespace CrazyEngine
{
    class RendererState
    {
    private:
        Shader* m_Shader;

        VertexBuffer* m_VBO;
        IndexBuffer* m_EBO;
        VertexArray* m_VAO;

    public:
        RendererState(int maxQuads, int maxTextures, const BufferLayout& layout);
        ~RendererState();

        void SetVertexBufferData(const void* data, std::uint32_t size);
        void SetProjection(Matrix4 projectionMatrix);
        void SetShader(Shader* shader);

        Shader* GetShader() const noexcept { return m_Shader; }

        void Bind();
        void Unbind();
    };
}

#endif