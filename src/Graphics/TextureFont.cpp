#include "CrazyEngine/Graphics/TextureFont.h"

#include <fstream>
#include <iostream>

namespace CrazyEngine
{
    TextureFont* TextureFont::Load(const char* filePath)
    {
        std::ifstream file(filePath, std::ios::binary | std::ios::ate);

        std::size_t size = file.tellg();
        std::uint8_t* buffer = new std::uint8_t[size];
        file.seekg(0, std::ios::beg);
        file.read((char*)buffer, size);
        file.close();

        TextureFont* font = new TextureFont();

        // Header

        std::size_t index = 0;
        memcpy(&size, buffer + index, sizeof(std::size_t));
        index += sizeof(std::size_t);

        char* header = new char[size + 1];
        memcpy(header, buffer + index, size);
        index += size * sizeof(char);
        header[size] = '\0';
        
        if (strcmp(header, FONT_FILE_HEADER))
        {
            std::cout << "Incompatible file detected." << std::endl;
            return nullptr;
        }

        // Glyph Count

        std::size_t glyphCount;
        memcpy(&glyphCount, buffer + index, sizeof(std::size_t));
        index += sizeof(std::size_t);

        font->m_Glyphs.resize(glyphCount, { });

        for (std::size_t i = 0; i < glyphCount; ++i)
        {
            memcpy(&font->m_Glyphs[i].ASCIICode, buffer + index, sizeof(std::uint32_t));
            index += sizeof(std::uint32_t);
            memcpy(&font->m_Glyphs[i].Width, buffer + index, sizeof(std::uint32_t));
            index += sizeof(std::uint32_t);
            memcpy(&font->m_Glyphs[i].Height, buffer + index, sizeof(std::uint32_t));
            index += sizeof(std::uint32_t);
            memcpy(&font->m_Glyphs[i].BearingX, buffer + index, sizeof(std::int32_t));
            index += sizeof(std::int32_t);
            memcpy(&font->m_Glyphs[i].BearingY, buffer + index, sizeof(std::int32_t));
            index += sizeof(std::int32_t);
            memcpy(&font->m_Glyphs[i].Advance, buffer + index, sizeof(std::int32_t));
            index += sizeof(std::int32_t);
            memcpy(&font->m_Glyphs[i].TextureX, buffer + index, sizeof(std::size_t));
            index += sizeof(std::size_t);
            memcpy(&font->m_Glyphs[i].TextureY, buffer + index, sizeof(std::size_t));
            index += sizeof(std::size_t);
        }

        // Texture Atlas

        std::size_t atlasWidth, atlasHeight;
        memcpy(&atlasWidth, buffer + index, sizeof(std::size_t));
        index += sizeof(std::size_t);
        memcpy(&atlasHeight, buffer + index, sizeof(std::size_t));
        index += sizeof(std::size_t);

        font->m_GlyphAtlas = Texture::Create(atlasWidth, atlasHeight, buffer + index);

        return font;
    }
}