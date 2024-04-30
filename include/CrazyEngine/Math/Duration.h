#ifndef CRAZYENGINE_MATH_DURATION_H_
#define CRAZYENGINE_MATH_DURATION_H_

#include <cstdint>
#include <iostream>

namespace CrazyEngine
{
    class Duration
    {
    private:
        
        double m_Milliseconds;

    public:
        Duration();
        Duration(double milliseconds);

        void SetValue(double milliseconds) noexcept;

        double TotalMilliseconds() const noexcept;
        double TotalSeconds() const noexcept;
        double TotalMinutes() const noexcept;
        double TotalHours() const noexcept;

        std::uint32_t Milliseconds() const noexcept;
        std::uint32_t Seconds() const noexcept;
        std::uint32_t Minutes() const noexcept;
        std::uint32_t Hours() const noexcept;

        void operator+=(const Duration& duration) noexcept;
        void operator-=(const Duration& duration) noexcept;
    };
}

CrazyEngine::Duration operator+(const CrazyEngine::Duration& firstDuration, const CrazyEngine::Duration& secondDuration) noexcept;
CrazyEngine::Duration operator-(const CrazyEngine::Duration& firstDuration, const CrazyEngine::Duration& secondDuration) noexcept;
CrazyEngine::Duration operator==(const CrazyEngine::Duration& firstDuration, const CrazyEngine::Duration& secondDuration) noexcept;
CrazyEngine::Duration operator!=(const CrazyEngine::Duration& firstDuration, const CrazyEngine::Duration& secondDuration) noexcept;
std::ostream& operator<<(std::ostream& os, const CrazyEngine::Duration& duration) noexcept;

#endif