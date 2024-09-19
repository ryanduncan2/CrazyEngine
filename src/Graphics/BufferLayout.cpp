#include "CrazyEngine/Graphics/BufferLayout.h"

namespace CrazyEngine
{
    BufferLayout::BufferLayout() : m_Size(0)
    {
    }

    BufferLayout::~BufferLayout()
    {
    }

    void BufferLayout::AddElement(ShaderDataType type)
    {
        m_Elements.push_back(BufferElement(type, m_Size));
        m_Size += ShaderTypeSize(type);
    }
}