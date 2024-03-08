#ifndef CRAZYENGINE_MATH_DURATION_H_
#define CRAZYENGINE_MATH_DURATION_H_

#include <cstdint>
#include <iostream>

namespace CrazyEngine
{
    class Duration
    {
    private:
        
        std::uint32_t m_Milliseconds;

    public:
        Duration();
        Duration(std::uint32_t milliseconds);

        void SetValue(std::uint32_t milliseconds) noexcept;

        float TotalSeconds() const noexcept;
        float TotalMinutes() const noexcept;
        float TotalHours() const noexcept;

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