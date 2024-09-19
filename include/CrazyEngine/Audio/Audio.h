#ifndef CRAZYENGINE_AUDIO_AUDIO_H_
#define CRAZYENGINE_AUDIO_AUDIO_H_

#include <initguid.h>
#include <Windows.h>
#include <Audioclient.h>
#include <mmdeviceapi.h>

#include "CrazyEngine/Core/Clock.h"
#include "CrazyEngine/Audio/Sound.h"

DEFINE_GUID(IID_IMMDeviceEnumerator, 0xA95664D2, 0x9614, 0x4F35, 0xA7, 0x46, 0xDE, 0x8D, 0xB6, 0x36, 0x17, 0xE6);
DEFINE_GUID(CLSID_MMDeviceEnumerator, 0xBCDE0395, 0xE52F, 0x467C, 0x8E, 0x3D, 0xC4, 0x57, 0x92, 0x91, 0x69, 0x2E);
DEFINE_GUID(IID_IAudioClient, 0x1CB9AD4C, 0xDBFA, 0x4c32, 0xB1, 0x78, 0xC2, 0xF5, 0x68, 0xA7, 0x03, 0xB2);
DEFINE_GUID(IID_IAudioRenderClient, 0xF294ACFC, 0x3146, 0x4483, 0xA7, 0xBF, 0xAD, 0xDC, 0xA7, 0xC2, 0x60, 0xE2);
DEFINE_GUID(IID_IAudioCaptureClient, 0xC8ADBD64, 0xE71E, 0x48a0, 0xA4, 0xDE, 0x18, 0x5C, 0x39, 0x5C, 0xD3, 0x17);

namespace CrazyEngine
{
    class Audio
    {
    private:
        
        double playbackTime = 0.0;

        IMMDevice* m_Renderer;
        IMMDevice* m_Recorder;

        IAudioClient* m_RenderClient;
        IAudioClient* m_RecorderClient;

        IAudioRenderClient* m_RenderService;
        IAudioCaptureClient* m_CaptureService;
        
        WAVEFORMATEX m_RenderFormat;
        WAVEFORMATEX* m_CaptureFormat;

        std::vector<std::pair<std::shared_ptr<Sound>, std::uint32_t>> m_Sounds;

    public:

        Audio();
        ~Audio();

        void Update(Clock& clock);
    };
}

#endif