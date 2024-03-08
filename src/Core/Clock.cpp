#include "CrazyEngine/Core/Clock.h"

#include <ctime>
#include <iostream>
#include <cmath>

namespace CrazyEngine
{
    Clock::Clock() noexcept
    {
    }

    Clock::~Clock() noexcept
    {
    }

    void Clock::Update(const Platform& platform) noexcept
    {
        Duration currentTime = Duration(std::roundf(platform.GetAbsoluteTime() / 1000.0f));

        m_ElapsedGameTime = currentTime - m_LastTime;
        m_TotalGameTime = currentTime;
        m_LastTime = currentTime;
    }
}