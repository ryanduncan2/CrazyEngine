#include "CrazyEngine/Graphics/Renderer2D.h"

#include <Vendor/glad/glad.h>
#include <iostream>
#include <algorithm>

#include "CrazyEngine/Graphics/RendererAPI.h"
#include "CrazyEngine/Graphics/Shader.h"
#include "CrazyEngine/Math/Calculator.h"

namespace CrazyEngine
{
    Renderer2D::Renderer2D()
    {
    }

    Renderer2D::~Renderer2D()
    {
    }

    void Renderer2D::Initialise(const std::uint32_t width, const std::uint32_t height)
    {
        // Setting Viewport

        m_Viewport = Vector2(width, height);

        // Initialising API

        RendererAPI::SetAPI(GraphicsAPI::OPENGL);
        m_API = RendererAPI::Create();

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        // Local Buffer Creation

        m_VertexData = new Vertex[MAX_QUADS * 4];

        // Buffer Creation

        BufferLayout layout;
        layout.AddElement(ShaderDataType::FLOAT3);
        layout.AddElement(ShaderDataType::FLOAT4);
        layout.AddElement(ShaderDataType::FLOAT2);
        layout.AddElement(ShaderDataType::FLOAT);
        layout.AddElement(ShaderDataType::INT);

        m_VertexBuffer = VertexBuffer::Create(layout.GetSize() * 4 * MAX_QUADS);
        m_VertexBuffer->SetLayout(layout);
        m_VertexArray = VertexArray::Create();
        m_VertexArray->SetVertexBuffer(m_VertexBuffer);

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

        m_IndexBuffer = IndexBuffer::Create(indices, MAX_QUADS * 6);

        m_VertexBuffer->Unbind();
        m_VertexArray->Unbind();

        m_ProjectionMatrix = Matrix4::CreateOrthographic(width, height);

        m_API->SetClearColour(Vector4(0.2f, 0.3f, 0.3f, 1.0f));
    }

    void Renderer2D::Terminate()
    {
        delete m_API;
        delete m_VertexArray;
        delete m_VertexBuffer;
        delete m_IndexBuffer;
        delete[] m_VertexData;
    }

    void Renderer2D::Resize(const std::uint32_t width, const std::uint32_t height)
    {
        m_Viewport = Vector2(width, height);
        
        m_API->SetViewport(0, 0, width, height);
        m_ProjectionMatrix = Matrix4::CreateOrthographic((float)width, (float)height);
    }

    void Renderer2D::Begin()
    {
        m_API->Clear();
    }

    void Renderer2D::Flush()
    {
    }

    void Renderer2D::End()
    {
        // Sort by Depth

        std::ranges::sort(m_RenderItems, [](const RenderItem& a, const RenderItem& b)
        {
            return a.GetDepth() < b.GetDepth();
        });

        // Draw all Batches

        Vertex* nextVertex = m_VertexData;
        
        std::uint32_t itemCount = 0;
        std::uint32_t indexCount = 0;
        std::uint32_t nextTextureIndex = 0;

        for (std::size_t i = 0; i < m_RenderItems.size(); ++i)
        {
            if (i != 0 && itemCount % MAX_QUADS == 0)
            {
                // Flushing Data

                for (std::uint32_t i = 0; i < nextTextureIndex; ++i)
                {
                    m_TextureSlots[i]->Bind(i);
                }

                m_VertexBuffer->SetData(m_VertexData, itemCount * sizeof(Vertex) * 4);
                m_Shader->Bind();
                m_Shader->SetMatrix4("u_Projection", m_ProjectionMatrix);
                m_VertexArray->Bind();
                m_API->DrawIndexed(indexCount);

                indexCount = 0;
                itemCount = 0;
                nextVertex = m_VertexData;
                nextTextureIndex = 0;
            }

            RenderItem item = m_RenderItems[i];

            // Handle Textures

            float textureIndex = -1.0f;
            for (std::uint32_t i = 0; i < nextTextureIndex; ++i)
            {
                if (m_TextureSlots[i]->GetHandle() == item.GetTexture()->GetHandle())
                {
                    textureIndex = (float)i;
                    break;
                }
            }

            if (textureIndex == -1.0f)
            {
                if (nextTextureIndex >= MAX_TEXTURE_SLOTS)
                {
                    // Flushing Data

                    for (std::uint32_t i = 0; i < nextTextureIndex; ++i)
                    {
                        m_TextureSlots[i]->Bind(i);
                    }

                    m_VertexBuffer->SetData(m_VertexData, itemCount * sizeof(Vertex) * 4);
                    m_Shader->Bind();
                    m_Shader->SetMatrix4("u_Projection", m_ProjectionMatrix);
                    m_VertexArray->Bind();
                    m_API->DrawIndexed(indexCount);

                    indexCount = 0;
                    itemCount = 0;
                    nextVertex = m_VertexData;
                    nextTextureIndex = 0;

                    i--;
                    continue;
                }

                textureIndex = (float)nextTextureIndex;
                m_TextureSlots[nextTextureIndex] = item.GetTexture();
                nextTextureIndex++;
            }

            // Write Vertices

            m_RenderItems[i].WriteVertices(nextVertex, textureIndex);

            indexCount += 6;
            itemCount++;
            nextVertex += 4;
        }

        // Flushing Final Data

        if (indexCount != 0)
        {
            for (std::uint32_t i = 0; i < nextTextureIndex; ++i)
            {
                m_TextureSlots[i]->Bind(i);
            }

            m_VertexBuffer->SetData(m_VertexData, itemCount * sizeof(Vertex) * 4);
            m_Shader->Bind();
            m_Shader->SetMatrix4("u_Projection", m_ProjectionMatrix);
            m_VertexArray->Bind();
            m_API->DrawIndexed(indexCount);
        }

        m_RenderItems.clear();
    }

    void Renderer2D::Draw(const Rectanglef& bounds, Texture* texture, float depth, int flags)
    {
        Rectanglef source(0, 0, texture->GetWidth(), texture->GetHeight());
        Draw(bounds, source, texture, depth, flags);
    }

    void Renderer2D::Draw(const Rectanglef& bounds, const Rectanglef& source, Texture* texture, float depth, int flags)
    {
        if (m_RenderItems.size() >= MAX_QUADS)
        {
            Flush();
        }

        m_RenderItems.push_back(RenderItem(bounds, source, texture, Vector4(1.0f, 1.0f, 1.0f, 1.0f), depth, 0.0f, flags));
    }

    void Renderer2D::Draw(const Rectanglef& bounds, const Rectanglef& source, Texture* texture, float rotation, float depth, int flags)
    {
        if (m_RenderItems.size() >= MAX_QUADS)
        {
            Flush();
        }

        m_RenderItems.push_back(RenderItem(bounds, source, texture, Vector4(1.0f, 1.0f, 1.0f, 1.0f), depth, rotation, flags));
    }

    void Renderer2D::DrawString(const std::string& str, const Vector2& position, const Vector4& colour, TextureFont* font, float scale, float depth, int flags)
    {
        // Sanity Check

        if (m_RenderItems.size() >= MAX_QUADS)
        {
            Flush();
        }

        // Drawing Glyphs

        int origin = position.X;
        for (std::size_t i = 0; i < str.length(); ++i)
        {
            Glyph glyph = font->GetGlyph(str[i]);

            if (str[i] == ' ')
            {
                origin += glyph.Advance * scale;

                continue;
            }

            Rectanglef bounds(origin + (glyph.BearingX * scale), position.Y - (glyph.BearingY * scale), glyph.Width * scale, glyph.Height * scale);
            Rectanglef source((float)glyph.TextureX, (float)glyph.TextureY, glyph.Width, glyph.Height);

            m_RenderItems.push_back(RenderItem(bounds, source, font->GetAtlas(), colour, depth, 0.0f, flags));

            origin += glyph.Advance * scale;
        }
    }
}