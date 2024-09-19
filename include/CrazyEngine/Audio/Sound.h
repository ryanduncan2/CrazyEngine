#ifndef CRAZYENGINE_AUDIO_SOUND_H_
#define CRAZYENGINE_AUDIO_SOUND_H_

#include <cstdint>

namespace CrazyEngine
{
    struct WavFile {
        // RIFF Chunk
        std::uint32_t riffId;
        std::uint32_t riffChunkSize;
        std::uint32_t waveId;

        // fmt Chunk
        std::uint32_t fmtId;
        std::uint32_t fmtChunkSize;
        std::uint16_t formatCode;
        std::uint16_t numChannels;
        std::uint32_t sampleRate;
        std::uint32_t byteRate;
        std::uint16_t blockAlign;
        std::uint16_t bitsPerSample;
        // These are not present for PCM Wav Files
        // uint16_t cbSize;
        // uint16_t wValidBitsPerSample;
        // uint32_t dwChannelMask;
        // char subFormatGUID[16];

        // data Chunk
        std::uint32_t dataId;
        std::uint32_t dataChunkSize;
        std::int16_t samples[]; // actual samples start here
    };

    class Sound
    {
    private:

        WavFile* m_File;

    public:

        Sound(const char* filePath);
        ~Sound();

        std::int16_t SampleLeft(std::uint32_t index);
        std::int16_t SampleRight(std::uint32_t index);
        std::uint32_t GetSampleCount();

        WavFile* GetFile();
    };
}

#endif