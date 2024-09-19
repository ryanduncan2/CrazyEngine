#ifndef CRAZYENGINE_GRAPHICS_BUFFERLAYOUT_H_
#define CRAZYENGINE_GRAPHICS_BUFFERLAYOUT_H_

#include <cstdint>
#include <vector>

namespace CrazyEngine
{
    enum class ShaderDataType
    {
        NONE, FLOAT, FLOAT2, FLOAT3, FLOAT4, MAT3, MAT4, INT, INT2, INT3, INT4, BOOL
    };

    static std::uint32_t ShaderTypeSize(ShaderDataType type)
    {
        switch (type)
        {
            case ShaderDataType::FLOAT: return 4;
            case ShaderDataType::FLOAT2: return 4 * 2;
            case ShaderDataType::FLOAT3: return 4 * 3;
            case ShaderDataType::FLOAT4: return 4 * 4;
            case ShaderDataType::MAT3: return 4 * 3 * 3;
            case ShaderDataType::MAT4: return 4 * 4 * 4;
            case ShaderDataType::INT: return 4;
            case ShaderDataType::INT2: return 4 * 2;
            case ShaderDataType::INT3: return 4 * 3;
            case ShaderDataType::INT4: return 4 * 4;
            case ShaderDataType::BOOL: return 1;
        }

        return 0;
    }

    struct BufferElement
    {
        ShaderDataType Type;
        std::size_t Size;
        std::size_t Offset;

        BufferElement(ShaderDataType type, std::uint32_t offset) : Type(type), Size(ShaderTypeSize(type)), Offset(offset) { }
    };

    class BufferLayout
    {
    private:
        
        std::vector<BufferElement> m_Elements;
        std::uint32_t m_Size;

    public:
    
        BufferLayout();
        ~BufferLayout();

        void AddElement(ShaderDataType type);
        inline std::vector<BufferElement>& GetElements() { return m_Elements; }
        inline std::uint32_t GetSize() const noexcept { return m_Size; }
    };
}

#endif