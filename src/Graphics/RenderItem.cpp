#include "CrazyEngine/Graphics/RenderItem.h"

namespace CrazyEngine
{
    RenderItem::RenderItem(const Rectanglef& bounds, const Rectanglef& source, Texture* texture, Vector4 colour, float depth, float rotation, int flags) :
        m_Bounds(bounds),
        m_Source(source),
        m_Texture(texture),
        m_Colour(colour),
        m_Depth(depth),
        m_Rotation(rotation),
        m_Flags(flags)
    {
    }

    RenderItem::~RenderItem()
    {
    }

    void RenderItem::WriteVertices(Vertex* vertices, float textureIndex) const noexcept
    {
        if (m_Rotation != 0.0f)
        {
            float sin = std::sinf(m_Rotation);
            float cos = std::cosf(m_Rotation);
            float x = -m_Bounds.Width / 2.0f;
            float y = -m_Bounds.Height / 2.0f;

            Vertex topLeft = 
            { 
                Vector3((x * cos) - (y * sin) + m_Bounds.X, (x * sin) + (y * cos) + m_Bounds.Y, 0.0f), 
                m_Colour, 
                Vector2((float)m_Source.X / m_Texture->GetWidth(), (float)m_Source.Y / m_Texture->GetHeight()), 
                textureIndex,
                m_Flags 
            };

            *vertices = topLeft;

            x = m_Bounds.Width / 2.0f;
            Vertex topRight = 
            { 
                Vector3((x * cos) - (y * sin) + m_Bounds.X, (x * sin) + (y * cos) + m_Bounds.Y, 0.0f), 
                m_Colour, 
                Vector2((float)(m_Source.X + m_Source.Width) / m_Texture->GetWidth(), (float)m_Source.Y / m_Texture->GetHeight()), 
                textureIndex,
                m_Flags 
            };
            *(vertices + 1) = topRight;

            y = m_Bounds.Height / 2.0f;
            Vertex bottomRight = 
            { 
                Vector3((x * cos) - (y * sin) + m_Bounds.X, (x * sin) + (y * cos) + m_Bounds.Y, 0.0f), 
                m_Colour, 
                Vector2((float)(m_Source.X + m_Source.Width) / m_Texture->GetWidth(), (float)(m_Source.Y + m_Source.Height) / m_Texture->GetHeight()), 
                textureIndex,
                m_Flags 
            };
            *(vertices + 2) = bottomRight;

            x = -m_Bounds.Width / 2.0f;
            Vertex bottomLeft = 
            { 
                Vector3((x * cos) - (y * sin) + m_Bounds.X, (x * sin) + (y * cos) + m_Bounds.Y, 0.0f), 
                m_Colour, 
                Vector2((float)m_Source.X / m_Texture->GetWidth(), (float)(m_Source.Y + m_Source.Height) / m_Texture->GetHeight()), 
                textureIndex,
                m_Flags 
            };
            *(vertices + 3) = bottomLeft;
        }
        else
        {
            Vertex topLeft = 
            { 
                Vector3(m_Bounds.X, m_Bounds.Y, 0.0f), 
                m_Colour, 
                Vector2((float)m_Source.X / m_Texture->GetWidth(), (float)m_Source.Y / m_Texture->GetHeight()), 
                textureIndex,
                m_Flags
            };
            *vertices = topLeft;

            Vertex topRight = 
            { 
                Vector3(m_Bounds.X + m_Bounds.Width, m_Bounds.Y, 0.0f), 
                m_Colour, 
                Vector2((float)(m_Source.X + m_Source.Width) / m_Texture->GetWidth(), (float)m_Source.Y / m_Texture->GetHeight()), 
                textureIndex,
                m_Flags
            };
            *(vertices + 1) = topRight;

            Vertex bottomRight = 
            { 
                Vector3(m_Bounds.X + m_Bounds.Width, m_Bounds.Y + m_Bounds.Height, 0.0f), 
                m_Colour, 
                Vector2((float)(m_Source.X + m_Source.Width) / m_Texture->GetWidth(), (float)(m_Source.Y + m_Source.Height) / m_Texture->GetHeight()), 
                textureIndex,
                m_Flags 
            };
            *(vertices + 2) = bottomRight;

            Vertex bottomLeft = 
            { 
                Vector3(m_Bounds.X, m_Bounds.Y + m_Bounds.Height, 0.0f), 
                m_Colour, 
                Vector2((float)m_Source.X / m_Texture->GetWidth(), (float)(m_Source.Y + m_Source.Height) / m_Texture->GetHeight()), 
                textureIndex,
                m_Flags 
            };
            *(vertices + 3) = bottomLeft;
        }
    }

    float RenderItem::GetDepth() const noexcept
    {
        return m_Depth;
    }

    Texture* RenderItem::GetTexture() const noexcept
    {
        return m_Texture;
    }
}