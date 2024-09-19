#include "CrazyEngine/Audio/Audio.h"

#include <iostream>
#include <assert.h>
#include <comdef.h>
#include <algorithm>

#include "CrazyEngine/Math/Calculator.h"

// Resources
// https://medium.com/@shahidahmadkhan86/sound-in-windows-the-wasapi-in-c-23024cdac7c6

namespace CrazyEngine
{
    

    Audio::Audio() :
        m_Recorder(nullptr),
        m_Renderer(nullptr),
        m_RecorderClient(nullptr),
        m_RenderClient(nullptr),
        m_RenderService(nullptr),
        m_CaptureService(nullptr),
        m_CaptureFormat(nullptr),
        playbackTime(0)
    {
        HRESULT hr;
        IMMDeviceEnumerator* enumerator = nullptr;

        // Initialise COM library

        hr = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
        assert(SUCCEEDED(hr));
        hr = CoCreateInstance(CLSID_MMDeviceEnumerator, nullptr, CLSCTX_ALL, IID_IMMDeviceEnumerator, (void**)&enumerator);
        assert(SUCCEEDED(hr));

        // Get Audio Devices

        hr = enumerator->GetDefaultAudioEndpoint(eRender, eConsole, &m_Renderer);
        assert(SUCCEEDED(hr));
        hr = enumerator->GetDefaultAudioEndpoint(eCapture, eConsole, &m_Recorder);
        assert(SUCCEEDED(hr));
        hr = enumerator->Release();
        assert(SUCCEEDED(hr));

        hr = m_Renderer->Activate(IID_IAudioClient, CLSCTX_ALL, nullptr, (void**)&m_RenderClient);
        assert(SUCCEEDED(hr));
        hr = m_Recorder->Activate(IID_IAudioClient, CLSCTX_ALL, nullptr, (void**)&m_RecorderClient);
        assert(SUCCEEDED(hr));

        // Set Audio Format

        m_RenderFormat = { };
        m_RenderFormat.wFormatTag = WAVE_FORMAT_PCM;
        m_RenderFormat.nChannels = 2;
        m_RenderFormat.nSamplesPerSec = 48000;
        m_RenderFormat.wBitsPerSample = 16;
        m_RenderFormat.nBlockAlign = (m_RenderFormat.nChannels * m_RenderFormat.wBitsPerSample) / 8;
        m_RenderFormat.nAvgBytesPerSec = m_RenderFormat.nSamplesPerSec * m_RenderFormat.nBlockAlign;

        // WAVEFORMATEX* closestMatch = nullptr;
        // hr = m_RenderClient->IsFormatSupported(AUDCLNT_SHAREMODE_SHARED, format, &closestMatch);
        // m_RenderFormat = hr == S_FALSE ? closestMatch : format;

        // hr = m_RenderClient->GetMixFormat(&m_RenderFormat);
        // assert(SUCCEEDED(hr));

        // hr = m_RecorderClient->GetMixFormat(&m_CaptureFormat);
        // assert(SUCCEEDED(hr));

        hr = m_RenderClient->Initialize(AUDCLNT_SHAREMODE_SHARED, AUDCLNT_STREAMFLAGS_RATEADJUST | AUDCLNT_STREAMFLAGS_AUTOCONVERTPCM | AUDCLNT_STREAMFLAGS_SRC_DEFAULT_QUALITY, 20000000, 0, &m_RenderFormat, nullptr);
        assert(SUCCEEDED(hr));

        // hr = m_RecorderClient->Initialize(AUDCLNT_SHAREMODE_SHARED, 0, 10000000, 0, m_CaptureFormat, nullptr);
        // assert(SUCCEEDED(hr));

        hr = m_RenderClient->GetService(IID_IAudioRenderClient, (void**)&m_RenderService);
        assert(SUCCEEDED(hr));

        // hr = m_RecorderClient->GetService(IID_IAudioCaptureClient, (void**)&m_CaptureService);
        // assert(SUCCEEDED(hr));

        // Audio Shit

        hr = m_RenderClient->Start();
        assert(SUCCEEDED(hr));
        // hr = m_RecorderClient->Start();
        // assert(SUCCEEDED(hr));

        // Loading Test Wav File

        std::shared_ptr<Sound> sound = std::make_shared<Sound>("Flowing-Water.wav");
        std::pair<std::shared_ptr<Sound>, std::uint32_t> t = std::pair<std::shared_ptr<Sound>, std::uint32_t>(sound, 0);
        m_Sounds.push_back(t);

        std::shared_ptr<Sound> sound2 = std::make_shared<Sound>("t.wav");
        std::pair<std::shared_ptr<Sound>, std::uint32_t> t2 = std::pair<std::shared_ptr<Sound>, std::uint32_t>(sound2, 0);
        m_Sounds.push_back(t2);
    }
    
    Audio::~Audio()
    {
        // m_RecorderClient->Stop();
        m_RenderClient->Stop();

        // m_CaptureService->Release();
        m_RenderService->Release();

        // m_RecorderClient->Release();
        m_RenderClient->Release();

        // m_Recorder->Release();
        m_Renderer->Release();

        CoUninitialize();
    }

    void Audio::Update(Clock& clock)
    {
        if (m_Sounds.size() == 0)
        {
            return;
        }

        HRESULT hr;
        std::uint16_t* renderBuffer;

        std::uint32_t bufferSize;
        std::uint32_t bufferPadding;

        hr = m_RenderClient->GetCurrentPadding(&bufferPadding);
        hr = m_RenderClient->GetBufferSize(&bufferSize);
        
        std::uint32_t frameCount = bufferSize - bufferPadding;
        hr = m_RenderService->GetBuffer(frameCount, (BYTE**)(&renderBuffer));

        for (std::uint32_t i = 0; i < frameCount; ++i)
        {
            std::int16_t amplitudeLeft = 0;
            std::int16_t amplitudeRight = 0;

            for (std::size_t j = 0; j < m_Sounds.size(); ++j)
            {
                if (m_Sounds[j].second >= m_Sounds[j].first->GetSampleCount())
                {
                    m_Sounds.erase(m_Sounds.begin() + j);
                    j--;

                    continue;
                }

                amplitudeLeft += (m_Sounds[j].first->SampleLeft(m_Sounds[j].second) / (std::int16_t)m_Sounds.size());
                amplitudeRight += (m_Sounds[j].first->SampleRight(m_Sounds[j].second) / (std::int16_t)m_Sounds.size());

                m_Sounds[j].second++;
            }

            if (m_Sounds.size() == 0)
            {
                continue;
            }

            *renderBuffer++ = amplitudeLeft;
            *renderBuffer++ = amplitudeRight;
        }

        // std::uint32_t wavPlaybackSample = 0;
        // std::uint32_t numWavSamples = testFile->dataChunkSize / (testFile->numChannels * sizeof(std::uint16_t));
        // for (std::uint32_t i = 0; i < frameCount; ++i)
        // {
        //     std::uint32_t leftSampleIndex = testFile->numChannels * wavPlaybackSample;
        //     std::uint32_t rightSampleIndex = leftSampleIndex + testFile->numChannels - 1;
        //     std::uint16_t leftSample = testFile->samples[leftSampleIndex];
        //     std::uint16_t rightSample = testFile->samples[rightSampleIndex];
        //     ++wavPlaybackSample;
        //     *renderBuffer++ = leftSample;
        //     *renderBuffer++ = rightSample;

        //     if(wavPlaybackSample >= numWavSamples)
        //         wavPlaybackSample -= numWavSamples;

        //     // float amplitude = ((float)sin(playbackTime * Calculator::PiDouble * (450 + 10)) + (float)sin(playbackTime * Calculator::Pi * (450 + 500)));
        //     // std::int16_t amp = (std::int16_t)(12000 * amplitude);

        //     // *renderBuffer++ = amp;
        //     // *renderBuffer++ = amp;

        //     // playbackTime += 1.0f / m_RenderFormat.nSamplesPerSec;
        // }

        hr = m_RenderService->ReleaseBuffer(frameCount, 0);
    }
}