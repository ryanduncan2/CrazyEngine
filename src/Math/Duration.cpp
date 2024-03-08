#include "CrazyEngine/Math/Duration.h"

#include <cmath>

namespace CrazyEngine
{
    Duration::Duration() : Duration(0) 
    { 
    }

    Duration::Duration(std::uint32_t milliseconds) : m_Milliseconds(milliseconds)
    {
    }

    void Duration::SetValue(std::uint32_t milliseconds) noexcept
    {
        m_Milliseconds = milliseconds;
    }

    float Duration::TotalSeconds() const noexcept
    {
        return (float)m_Milliseconds / 1000.0f;
    }

    float Duration::TotalMinutes() const noexcept
    {
        return (float)m_Milliseconds / 60000.0f;
    }

    float Duration::TotalHours() const noexcept
    {
        return (float)m_Milliseconds / 3600000.0f;
    }

    std::uint32_t Duration::Milliseconds() const noexcept
    {
        return m_Milliseconds;
    }

    std::uint32_t Duration::Seconds() const noexcept
    {
        return std::floorf(TotalSeconds());
    }

    std::uint32_t Duration::Minutes() const noexcept
    {
        return std::floorf(TotalMinutes());
    }

    std::uint32_t Duration::Hours() const noexcept
    {
        return std::floorf(TotalHours());
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
    return CrazyEngine::Duration(firstDuration.Milliseconds() + secondDuration.Milliseconds());
}

CrazyEngine::Duration operator-(const CrazyEngine::Duration& firstDuration, const CrazyEngine::Duration& secondDuration) noexcept
{
    return CrazyEngine::Duration(firstDuration.Milliseconds() - secondDuration.Milliseconds());
}

CrazyEngine::Duration operator==(const CrazyEngine::Duration& firstDuration, const CrazyEngine::Duration& secondDuration) noexcept
{
    return firstDuration.Milliseconds() == secondDuration.Milliseconds();
}

CrazyEngine::Duration operator!=(const CrazyEngine::Duration& firstDuration, const CrazyEngine::Duration& secondDuration) noexcept
{
    return firstDuration.Milliseconds() != secondDuration.Milliseconds();
}

std::ostream& operator<<(std::ostream& os, const CrazyEngine::Duration& duration) noexcept
{
    return os << duration.Milliseconds();
}
