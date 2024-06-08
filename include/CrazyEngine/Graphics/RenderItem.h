#ifndef CRAZYENGINE_GRAPHICS_RENDERITEM_H_
#define CRAZYENGINE_GRAPHICS_RENDERITEM_H_

#include "CrazyEngine/Graphics/Texture.h"
#include "CrazyEngine/Graphics/Vertex.h"
#include "CrazyEngine/Math/Rectangle.h"

namespace CrazyEngine
{
    class RenderItem
    {
    private:
        Rectanglef m_Bounds;
        Rectanglef m_Source;
        Texture* m_Texture;
        Vector4 m_Colour;
        float m_Depth;
        float m_Rotation;
        int m_Flags;

    public:
        RenderItem(const Rectanglef& bounds, const Rectanglef& source, Texture* texture, Vector4 colour, float depth, float rotation, int flags);
        ~RenderItem();

        void WriteVertices(Vertex* vertices, float textureIndex) const noexcept;

        float GetDepth() const noexcept;
        Texture* GetTexture() const noexcept;
    };
}

#endif