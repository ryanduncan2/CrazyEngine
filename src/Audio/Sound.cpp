#include "CrazyEngine/Audio/Sound.h"

#include <fstream>
#include <Windows.h>

#include <iostream>

namespace CrazyEngine
{
    Sound::Sound(const char* filePath)
    {
        std::ifstream file(filePath, std::ios::binary | std::ios::ate);
        std::size_t fileSize = file.tellg();
        
        std::uint8_t* buffer = new std::uint8_t[fileSize];
        file.seekg(0, std::ios::beg);
        file.read((char*)buffer, fileSize);
        file.close();
        
        m_File = (WavFile*)buffer;
    }

    Sound::~Sound()
    {
        delete[] m_File;
    }

    std::int16_t Sound::SampleLeft(std::uint32_t index)
    {
        return m_File->samples[m_File->numChannels * index];
    }

    std::int16_t Sound::SampleRight(std::uint32_t index)
    {
        return m_File->samples[m_File->numChannels * index + m_File->numChannels - 1];
    }

    std::uint32_t Sound::GetSampleCount()
    {
        return m_File->dataChunkSize / (m_File->numChannels * sizeof(std::uint16_t));
    }

    WavFile* Sound::GetFile()
    {
        return m_File;
    }
}