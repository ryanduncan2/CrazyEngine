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
        m_TotalGameTime = Duration(platform.GetAbsoluteTime());

        m_ElapsedGameTime = m_TotalGameTime - m_LastTime;
        m_LastTime = m_TotalGameTime;
    }
}