#ifndef CRAZYENGINE_GRAPHICS_VERTEX_H_
#define CRAZYENGINE_GRAPHICS_VERTEX_H_

#include "CrazyEngine/Math/Vector2.h"
#include "CrazyEngine/Math/Vector3.h"
#include "CrazyEngine/Math/Vector4.h"

namespace CrazyEngine
{
    struct Vertex
    {
        Vector3 Position;
        Vector4 Colour;
        Vector2 TextureCoords;
        float TextureIndex;
    };
}

#endif