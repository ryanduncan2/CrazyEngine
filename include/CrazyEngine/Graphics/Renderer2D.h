#ifndef CRAZYENGINE_GRAPHICS_RENDERER2D_H_
#define CRAZYENGINE_GRAPHICS_RENDERER2D_H_

#include <cstdint>
#include <array>

#include "CrazyEngine/Graphics/RendererAPI.h"
#include "CrazyEngine/Graphics/Shader.h"
#include "CrazyEngine/Graphics/Vertex.h"
#include "CrazyEngine/Graphics/Buffers.h"
#include "CrazyEngine/Graphics/VertexArray.h"
#include "CrazyEngine/Graphics/Texture.h"
#include "CrazyEngine/Graphics/TextureFont.h"

#include "CrazyEngine/Math/Rectangle.h"
#include "CrazyEngine/Math/Matrix4.h"

#define MAX_QUADS 1024
#define MAX_TEXTURE_SLOTS 32

namespace CrazyEngine
{
    class Renderer2D
    {
    private:

        RendererAPI* m_API;

        Shader* m_Shader;

        VertexArray* m_VertexArray;
        VertexBuffer* m_VertexBuffer;
        IndexBuffer* m_IndexBuffer;

        std::array<Texture*, MAX_TEXTURE_SLOTS> m_TextureSlots;
        std::uint32_t m_NextTextureIndex;

        Vertex* m_Vertices;
        Vertex* m_NextVertex;
        std::uint32_t m_IndexCount;

        Matrix4 m_ProjectionMatrix;

        Vector2 m_Viewport;

    public:
        Renderer2D();
        ~Renderer2D();

        void Initialise(const std::uint32_t width, const std::uint32_t height);
        void Terminate();

        void Begin();
        void Flush();
        void End();

        inline Vector2 GetViewport() const noexcept { return m_Viewport; }
        inline void SetShader(Shader* shader) noexcept { m_Shader = shader; }
        inline Shader* GetShader() const noexcept { return m_Shader; }

        void Resize(std::uint32_t width, std::uint32_t height);

        void Draw(const Rectanglef& bounds, Texture* texture, int flags = 0);
        void Draw(const Rectanglef& bounds, const Rectanglef& source, Texture* texture, int flags = 0);
        void Draw(const Rectanglef& bounds, const Rectanglef& source, Texture* texture, float rotation, int flags = 0);

        void DrawString(const std::string& str, const Vector2& position, const Vector4& colour, TextureFont* font, float scale, int flags = 0);
    };
}

#endif