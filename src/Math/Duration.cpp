#include "CrazyEngine/Math/Duration.h"

#include <cmath>

namespace CrazyEngine
{
    Duration::Duration() : Duration(0.0) 
    { 
    }

    Duration::Duration(double milliseconds) : m_Milliseconds(milliseconds)
    {
    }

    void Duration::SetValue(double milliseconds) noexcept
    {
        m_Milliseconds = milliseconds;
    }

    double Duration::TotalMilliseconds() const noexcept
    {
        return m_Milliseconds;
    }

    double Duration::TotalSeconds() const noexcept
    {
        return m_Milliseconds / 1000.0;
    }

    double Duration::TotalMinutes() const noexcept
    {
        return m_Milliseconds / 60000.0;
    }

    double Duration::TotalHours() const noexcept
    {
        return m_Milliseconds / 3600000.0;
    }

    std::uint32_t Duration::Milliseconds() const noexcept
    {
        return m_Milliseconds;
    }

    std::uint32_t Duration::Seconds() const noexcept
    {
        return std::floor(TotalSeconds());
    }

    std::uint32_t Duration::Minutes() const noexcept
    {
        return std::floor(TotalMinutes());
    }

    std::uint32_t Duration::Hours() const noexcept
    {
        return std::floor(TotalHours());
    }

    void Duration::operator+=(const Duration& duration) noexcept
    {
        m_Milliseconds += duration.m_Milliseconds;
    }

    void Duration::operator-=(const Duration& duration) noexcept
    {
        m_Milliseconds -= duration.m_Milliseconds;
    }
}

CrazyEngine::Duration operator+(const CrazyEngine::Duration& firstDuration, const CrazyEngine::Duration& secondDuration) noexcept
{
    return CrazyEngine::Duration(firstDuration.TotalMilliseconds() + secondDuration.TotalMilliseconds());
}

CrazyEngine::Duration operator-(const CrazyEngine::Duration& firstDuration, const CrazyEngine::Duration& secondDuration) noexcept
{
    return CrazyEngine::Duration(firstDuration.TotalMilliseconds() - secondDuration.TotalMilliseconds());
}

CrazyEngine::Duration operator==(const CrazyEngine::Duration& firstDuration, const CrazyEngine::Duration& secondDuration) noexcept
{
    return firstDuration.TotalMilliseconds() == secondDuration.TotalMilliseconds();
}

CrazyEngine::Duration operator!=(const CrazyEngine::Duration& firstDuration, const CrazyEngine::Duration& secondDuration) noexcept
{
    return firstDuration.TotalMilliseconds() != secondDuration.TotalMilliseconds();
}

std::ostream& operator<<(std::ostream& os, const CrazyEngine::Duration& duration) noexcept
{
    return os << duration.TotalMilliseconds();
}
