#ifndef CRAZYENGINE_GRAPHICS_TEXTUREFONT_H_
#define CRAZYENGINE_GRAPHICS_TEXTUREFONT_H_

#define FONT_FILE_HEADER "CECT-FONT-FILE 1.0.0"

#include <vector>

#include "CrazyEngine/Graphics/Texture.h"

namespace CrazyEngine
{
    struct Glyph
    {
        std::uint32_t ASCIICode;
        std::uint32_t Width;
        std::uint32_t Height;
        std::size_t TextureX;
        std::size_t TextureY;
        std::int32_t BearingX;
        std::int32_t BearingY;
        std::int32_t Advance;
    };

    class TextureFont
    {
    private:

        Texture* m_GlyphAtlas;
        std::vector<Glyph> m_Glyphs;

    public:
        TextureFont() { }
        ~TextureFont() { }

        static TextureFont* Load(const char* filePath);

        inline Texture* GetAtlas() { return m_GlyphAtlas; }
        inline Glyph GetGlyph(char ch) { return m_Glyphs[(int)ch - 33]; }
    };
}

#endif