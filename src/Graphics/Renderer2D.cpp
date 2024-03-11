#include "CrazyEngine/Graphics/Renderer2D.h"

#include <Vendor/glad/glad.h>
#include <iostream>

#include "CrazyEngine/Graphics/RendererAPI.h"
#include "CrazyEngine/Graphics/Shader.h"

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
        RendererAPI::SetAPI(GraphicsAPI::OPENGL);
        m_API = RendererAPI::Create();

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        // Shader Setup

        m_Shader = Shader::Create("../../shaders/shader.vert", "../../shaders/shader.frag");

        int* samplers = new int[MAX_TEXTURE_SLOTS];
        for (int i = 0; i < MAX_TEXTURE_SLOTS; ++i)
        {
            samplers[i] = i;
        }
        
        m_Shader->Bind();
        m_Shader->SetIntArray("u_Textures", MAX_TEXTURE_SLOTS, samplers);
        m_Shader->Unbind();

        // Local Buffer Creation

        m_Vertices = new Vertex[MAX_QUADS * 4];
        m_NextVertex = m_Vertices;
        m_IndexCount = 0;

        m_NextTextureIndex = 0;

        // Buffer Creation

        BufferLayout layout;
        layout.AddElement(ShaderDataType::FLOAT3);
        layout.AddElement(ShaderDataType::FLOAT4);
        layout.AddElement(ShaderDataType::FLOAT2);
        layout.AddElement(ShaderDataType::FLOAT);

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
        delete[] m_Vertices;

        delete m_API;
        delete m_VertexArray;
        delete m_VertexBuffer;
        delete m_IndexBuffer;
        delete m_Shader;
    }

    void Renderer2D::Resize(const std::uint32_t width, const std::uint32_t height)
    {
        m_API->SetViewport(0, 0, width, height);
        m_ProjectionMatrix = Matrix4::CreateOrthographic((float)width, (float)height);
    }

    void Renderer2D::Begin()
    {
        m_API->Clear();

        m_IndexCount = 0;
        m_NextVertex = m_Vertices;

        m_NextTextureIndex = 0;
    }

    void Renderer2D::End()
    {
        for (std::uint32_t i = 0; i < m_NextTextureIndex; ++i)
        {
            m_TextureSlots[i]->Bind(i);
        }

        GLsizeiptr size = (std::uint8_t*)m_NextVertex - (std::uint8_t*)m_Vertices;
        m_VertexBuffer->SetData(m_Vertices, size);
        
        m_Shader->SetMatrix4("u_Projection", m_ProjectionMatrix);
        m_Shader->Bind();

        m_VertexArray->Bind();
        m_API->DrawIndexed(m_IndexCount);
    }

    void Renderer2D::Draw(const Rectangle& bounds, Texture* texture)
    {
        Rectangle source(0, 0, texture->GetWidth(), texture->GetHeight());
        Draw(bounds, source, texture);
    }

    void Renderer2D::Draw(const Rectangle& bounds, const Rectangle& source, Texture* texture)
    {
        // Sanity Check

        if (m_IndexCount >= MAX_QUADS * 6)
        {
            End();
            Begin();
        }

        // Texture Handling

        float textureIndex = -1.0f;
        for (std::uint32_t i = 0; i < m_NextTextureIndex; ++i)
        {
            if (m_TextureSlots[i]->GetHandle() == texture->GetHandle())
            {
                textureIndex = (float)i;
                break;
            }
        }

        if (textureIndex == -1.0f)
        {
            textureIndex = (float)m_NextTextureIndex;
            m_TextureSlots[m_NextTextureIndex] = texture;
            m_NextTextureIndex++;
        }

        // Vertex Definitions

        Vector4 colour = Vector4(1.0f, 1.0f, 1.0f, 1.0f);

        Vertex topLeft = 
        { 
            Vector3(bounds.X, bounds.Y, 0.0f), 
            colour, 
            Vector2((float)source.X / texture->GetWidth(), (float)source.Y / texture->GetHeight()), 
            textureIndex 
        };
        *m_NextVertex = topLeft;
        m_NextVertex++;

        Vertex topRight = 
        { 
            Vector3(bounds.X + bounds.Width, bounds.Y, 0.0f), 
            colour, 
            Vector2((float)(source.X + source.Width) / texture->GetWidth(), (float)source.Y / texture->GetHeight()), 
            textureIndex 
        };
        *m_NextVertex = topRight;
        m_NextVertex++;

        Vertex bottomRight = 
        { 
            Vector3(bounds.X + bounds.Width, bounds.Y + bounds.Height, 0.0f), 
            colour, 
            Vector2((float)(source.X + source.Width) / texture->GetWidth(), (float)(source.Y + source.Height) / texture->GetHeight()), 
            textureIndex 
        };
        *m_NextVertex = bottomRight;
        m_NextVertex++;

        Vertex bottomLeft = 
        { 
            Vector3(bounds.X, bounds.Y + bounds.Height, 0.0f), 
            colour, 
            Vector2((float)source.X / texture->GetWidth(), (float)(source.Y + source.Height) / texture->GetHeight()), 
            textureIndex 
        };
        *m_NextVertex = bottomLeft;
        m_NextVertex++;

        m_IndexCount += 6;
    }

    void Renderer2D::DrawString(const std::string& str, const Vector2& position, const Vector4& colour, TextureFont* font, float scale)
    {
        // Sanity Check

        if (m_IndexCount >= MAX_QUADS * 6)
        {
            End();
            Begin();
        }

        // Texture Handling

        float textureIndex = -1.0f;
        for (std::uint32_t i = 0; i < m_NextTextureIndex; ++i)
        {
            if (m_TextureSlots[i]->GetHandle() == font->GetAtlas()->GetHandle())
            {
                textureIndex = (float)i;
                break;
            }
        }

        if (textureIndex == -1.0f)
        {
            textureIndex = (float)m_NextTextureIndex;
            m_TextureSlots[m_NextTextureIndex] = font->GetAtlas();
            m_NextTextureIndex++;
        }

        // Vertex Definitions

        int origin = position.X;

        for (std::size_t i = 0; i < str.length(); ++i)
        {
            Glyph glyph = font->GetGlyph(str[i]);

            Vertex topLeft = 
            { 
                Vector3(origin + (glyph.BearingX * scale), position.Y - (glyph.BearingY * scale), 0.0f), 
                colour, 
                Vector2((float)glyph.TextureX / font->GetAtlas()->GetWidth(), (float)glyph.TextureY / font->GetAtlas()->GetHeight()), 
                textureIndex 
            };
            *m_NextVertex = topLeft;
            m_NextVertex++;

            Vertex topRight = 
            { 
                Vector3(origin + ((glyph.BearingX + glyph.Width) * scale), position.Y - (glyph.BearingY * scale), 0.0f), 
                colour, 
                Vector2((float)(glyph.TextureX + glyph.Width) / font->GetAtlas()->GetWidth(), (float)glyph.TextureY / font->GetAtlas()->GetHeight()), 
                textureIndex 
            };
            *m_NextVertex = topRight;
            m_NextVertex++;

            Vertex bottomRight = 
            { 
                Vector3(origin + ((glyph.BearingX + glyph.Width) * scale), position.Y + ((-glyph.BearingY + glyph.Height) * scale), 0.0f), 
                colour, 
                Vector2((float)(glyph.TextureX + glyph.Width) / font->GetAtlas()->GetWidth(), (float)(glyph.TextureY + glyph.Height) / font->GetAtlas()->GetHeight()), 
                textureIndex 
            };
            *m_NextVertex = bottomRight;
            m_NextVertex++;

            Vertex bottomLeft = 
            { 
                Vector3(origin + glyph.BearingX, position.Y + ((-glyph.BearingY + glyph.Height) * scale), 0.0f), 
                colour, 
                Vector2((float)glyph.TextureX / font->GetAtlas()->GetWidth(), (float)(glyph.TextureY + glyph.Height) / font->GetAtlas()->GetHeight()), 
                textureIndex 
            };
            *m_NextVertex = bottomLeft;
            m_NextVertex++;

            m_IndexCount += 6;

            origin += glyph.Advance * scale;
        }
    }
}