#include "CrazyEngine/Graphics/TextureFont.h"

#include <fstream>
#include <iostream>

#include "CrazyEngine/Math/Calculator.h"

namespace CrazyEngine
{
    TextureFont* TextureFont::Load(const char* filePath)
    {
        std::ifstream file(filePath, std::ios::binary | std::ios::beg);
        TextureFont* font = new TextureFont();

        // Header

        std::size_t size = 0;
        file.read((char*)&size, sizeof(size_t));
        
        char* header = new char[size + 1];
        file.read(header, size);
        header[size] = '\0';

        if (strcmp(header, FONT_FILE_HEADER))
        {
            std::cout << "Incompatible font file detected." << std::endl;
            return nullptr;
        }

        // Glyph Count

        file.read((char*)&size, sizeof(std::size_t));
        font->m_Glyphs.resize(size, { });

        // Glyphs

        for (std::size_t i = 0; i < size; ++i)
        {
            file.read((char*)&font->m_Glyphs[i].ASCIICode, sizeof(std::uint32_t));
            file.read((char*)&font->m_Glyphs[i].Width, sizeof(std::uint32_t));
            file.read((char*)&font->m_Glyphs[i].Height, sizeof(std::uint32_t));
            file.read((char*)&font->m_Glyphs[i].BearingX, sizeof(std::int32_t));
            file.read((char*)&font->m_Glyphs[i].BearingY, sizeof(std::int32_t));
            file.read((char*)&font->m_Glyphs[i].Advance, sizeof(std::int32_t));
            file.read((char*)&font->m_Glyphs[i].TextureX, sizeof(std::size_t));
            file.read((char*)&font->m_Glyphs[i].TextureY, sizeof(std::size_t));
        }

        // Texture Atlas

        std::size_t atlasWidth = 0;
        std::size_t atlasHeight = 0;

        file.read((char*)&atlasWidth, sizeof(std::size_t));
        file.read((char*)&atlasHeight, sizeof(std::size_t));

        std::uint8_t* atlasData = new std::uint8_t[atlasWidth * atlasHeight * sizeof(std::uint8_t)];
        file.read((char*)atlasData, atlasWidth * atlasHeight * sizeof(std::uint8_t));
        file.close();
        
        font->m_GlyphAtlas = Texture::CreateGlyph(atlasWidth, atlasHeight, atlasData, FilterType::LINEAR_MIPMAP_LINEAR);

        return font;
    }

    TextureFont::~TextureFont()
    {
        delete m_GlyphAtlas;
    }

    Vector2 TextureFont::MeasureString(const char* str, float scale) const noexcept
    {
        std::uint32_t maxY = 0;
        std::uint32_t minY = 0;
        Vector2 dimensions;

        std::size_t length = strlen(str);

        if (length == 0)
        {
            return dimensions;
        }

        // First Character

        Glyph firstGlyph = GetGlyph(str[0]);
        dimensions.X = firstGlyph.BearingX < 0 ? firstGlyph.Width + std::abs(firstGlyph.BearingX) : firstGlyph.Width;
        maxY = firstGlyph.BearingY;
        minY = firstGlyph.Height - firstGlyph.BearingY;

        // Middle Characters

        for (std::size_t i = 1; i < length - 1; ++i)
        {
            Glyph glyph = GetGlyph(str[i]);
            dimensions.X += glyph.Advance;

            maxY = Calculator::Max(maxY, glyph.BearingY);
            minY = Calculator::Max(minY, glyph.Height - glyph.BearingY);
        }

        // Last Character

        if (length >= 2)
        {   
            Glyph lastGlyph = GetGlyph(str[length - 1]);
            dimensions.X += lastGlyph.BearingX + lastGlyph.Width;

            maxY = Calculator::Max(maxY, lastGlyph.BearingY);
            minY = Calculator::Max(minY, lastGlyph.Height - lastGlyph.BearingY);
        }

        dimensions.Y = maxY + minY;
        dimensions *= scale;

        return dimensions;
    }
}