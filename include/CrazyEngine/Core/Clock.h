#ifndef CRAZYENGINE_CORE_CLOCK_H_
#define CRAZYENGINE_CORE_CLOCK_H_

#include "CrazyEngine/Platform/Platform.h"
#include "CrazyEngine/Math/Duration.h"

namespace CrazyEngine
{
    class Clock
    {
    private:

        Duration m_ElapsedGameTime;
        Duration m_TotalGameTime;
        Duration m_LastTime;

    public:

        Clock() noexcept;
        ~Clock() noexcept;

        void Update(const Platform& platform) noexcept;
        
        inline float GetElapsedGameTime() const noexcept { m_ElapsedGameTime; }
        inline float GetTotalGameTime() const noexcept { m_TotalGameTime; }
    };
}

#endif