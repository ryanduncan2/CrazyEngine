#include "CECT/ContentLoader.h"

#include <string>
#include <iostream>
#include <array>
#include <vector>
#include <fstream>
#include <filesystem>

#include <ft2build.h>
#include FT_FREETYPE_H

namespace CECT
{
    Font* ContentLoader::LoadFont(const char* fontPath, std::uint32_t fontSize)
    {
        // Initialising Freetype

        FT_Library library;

        if (FT_Init_FreeType(&library))
        {
            throw std::string("Failed to initialise Freetype library.");
        }

        // Loading Font Face

        FT_Face fontFace;

        FT_Error error = FT_New_Face(library, fontPath, 0, &fontFace);
        if (error == FT_Err_Unknown_File_Format)
        {
            throw std::string("Font format unsupported.");
        }
        else if (error)
        {
            throw std::string("Failed to load font.");
        }

        // Setting Font Size

        int newSize = fontSize;
        for (int i = fontFace->num_fixed_sizes - 1; i >= 0; --i)
        {
            if (newSize == (fontFace->available_sizes[i].size / 64))
            {
                newSize--;
            }
        }

        FT_Set_Pixel_Sizes(fontFace, 0, newSize);

        // Loading Glyphs 33-126

        Font* font = new Font();

        for (int i = 33; i <= 126; ++i)
        {
            FT_UInt charIndex = FT_Get_Char_Index(fontFace, i);

            if (FT_Load_Glyph(fontFace, charIndex, FT_LOAD_DEFAULT))
            {
                std::cout << "Failed to load glyph " + std::to_string(i) + "." << std::endl;
                throw std::string("Failed to load glyph " + std::to_string(i) + ".");
            }

            if (FT_Render_Glyph(fontFace->glyph, FT_RENDER_MODE_NORMAL))
            {
                std::cout << "Failed to render glyph " + std::to_string(i) + "." << std::endl;
                throw std::string("Failed to render glyph " + std::to_string(i) + ".");
            }

            Glyph* glyph = new Glyph(i, fontFace->glyph->bitmap.width, fontFace->glyph->bitmap.rows, fontFace->glyph->bitmap_left, fontFace->glyph->bitmap_top, (std::int32_t)fontFace->glyph->advance.x / 64);
            glyph->Data = new std::uint8_t[glyph->Width * glyph->Height];

            for (std::uint32_t y = 0; y < glyph->Height; ++y)
            {
                for (std::uint32_t x = 0; x < glyph->Width; ++x)
                {
                    std::uint32_t index = x + (glyph->Width * y);
                    glyph->Data[index] = fontFace->glyph->bitmap.buffer[index];
                }
            }

            font->AddGlyph(glyph);
        }

        FT_Done_Face(fontFace);
        FT_Done_FreeType(library);

        return font;
    }

    std::size_t ContentLoader::GetFontSerialSize(Font* font)
    {
        std::size_t fontSize = 0;

        fontSize += 4 * sizeof(std::size_t);
        fontSize += strlen(FONT_FILE_HEADER) * sizeof(char);
        fontSize += font->GetGlyphs().size() * ((3 * sizeof(std::uint32_t)) + (3 * sizeof(std::int32_t)) + (2 * sizeof(std::size_t)));

        return fontSize;
    }

    void ContentLoader::CreateFontFile(Font* font, const char* fileName)
    {
        // Serial Structure: [Header Size]["CECT-FONT-FILE [Version]"][Glyph Count][Glyph 1 Metadata]...[Glyph N Metadata][Glyph Texture Atlas]

        std::uint8_t* serial = new std::uint8_t[GetFontSerialSize(font) + 9000];
        std::size_t index = 0, size;
        
        // File Header

        const char* header = FONT_FILE_HEADER;
        size = strlen(header) * sizeof(char);
        memcpy(serial + index, &size, sizeof(std::size_t));
        index += sizeof(std::size_t);

        memcpy(serial + index, header, size);
        index += size;

        // Glyph Count

        std::size_t glyphCount = font->GetGlyphs().size();
        size = sizeof(std::size_t);
        memcpy(serial + index, &glyphCount, size);
        index += size;

        // Glyph Data

        std::size_t atlasWidth = font->GetGlyphs()[0]->Height * (int)std::ceil(std::sqrt(glyphCount));
        std::size_t atlasHeight = atlasWidth;
        std::uint8_t* glyphAtlas = new std::uint8_t[atlasWidth * atlasHeight];
        memset(glyphAtlas, 0, atlasWidth * atlasHeight * sizeof(std::uint8_t));
        std::vector<std::array<int, 4>> partitions;

        for (std::size_t i = 0; i < font->GetGlyphs().size(); ++i)
        {
            Glyph* glyph = font->GetGlyphs()[i];

            // Glyph Metadata

            size = sizeof(std::uint32_t);
            memcpy(serial + index, &glyph->ASCIICode, size);
            index += size;

            memcpy(serial + index, &glyph->Width, size);
            index += size;

            memcpy(serial + index, &glyph->Height, size);
            index += size;

            size = sizeof(std::int32_t);
            memcpy(serial + index, &glyph->BearingX, size);
            index += size;

            memcpy(serial + index, &glyph->BearingY, size);
            index += size;

            memcpy(serial + index, &glyph->Advance, size);
            index += size;
                    
            // Glyph Texture Packing

            std::size_t textureX, textureY;

            int y = 0;
            while (true)
            {
                for (std::size_t x = 0; x < atlasWidth - glyph->Width; ++x)
                {
                    bool intersectionFound = false;

                    for (std::size_t i = 0; i < partitions.size(); ++i)
                    {
                        if (x <= partitions[i][0] + partitions[i][2] && x + glyph->Width >= partitions[i][0] && y <= partitions[i][1] + partitions[i][3] && y + glyph->Height >= partitions[i][1])
                        {
                            intersectionFound = true;
                        }
                    }

                    if (!intersectionFound)
                    {
                        // Found location, packing texture.

                        for (std::size_t texX = 0; texX < glyph->Width; ++texX)
                        {
                            for (std::size_t texY = 0; texY < glyph->Height; ++texY)
                            {
                                int sourcePixelIndex = texX + (texY * glyph->Width);
                                int destPixelIndex = (y * atlasWidth) + (texY * atlasWidth) + x + texX;

                                glyphAtlas[destPixelIndex] = glyph->Data[sourcePixelIndex];
                            }
                        }

                        std::array<int, 4> bounds = { x, y, glyph->Width, glyph->Height };
                        partitions.push_back(bounds);

                        textureX = x;
                        textureY = y;

                        goto break_loop;
                    }
                }

                // Incrementing Y and expanding texture.

                y++;

                if (y + glyph->Height >= atlasHeight)
                {
                    std::size_t newHeight = atlasHeight + (glyph->Height * 2);

                    std::uint8_t* newAtlas = new std::uint8_t[atlasWidth * newHeight];
                    memset(newAtlas, 0, atlasWidth * newHeight * sizeof(std::uint8_t));
                    memcpy(newAtlas, glyphAtlas, atlasWidth * atlasHeight);
                    delete[] glyphAtlas;
                    glyphAtlas = newAtlas;
                    atlasHeight = newHeight;
                }
            }

            break_loop:

            memcpy(serial + index, &textureX, sizeof(std::size_t));
            index += sizeof(std::size_t);
            memcpy(serial + index, &textureY, sizeof(std::size_t));
            index += sizeof(std::size_t);
        }

        memcpy(serial + index, &atlasWidth, sizeof(std::size_t));
        index += sizeof(std::size_t);
        memcpy(serial + index, &atlasHeight, sizeof(std::size_t));
        index += sizeof(std::size_t);

        std::uint8_t* newSerial = new std::uint8_t[index + (atlasWidth * atlasHeight)];
        memcpy(newSerial, serial, index);
        delete[] serial;
        serial = newSerial;

        memcpy(serial + index, glyphAtlas, atlasWidth * atlasHeight * sizeof(std::uint8_t));
        index += atlasWidth * atlasHeight;

        // Saving File

        std::ofstream file(fileName, std::ios::out | std::ios::binary | std::ios::trunc);
        file.write((const char*)serial, index);
        file.close();

        // Cleaning Up

        delete[] serial;
    }
}