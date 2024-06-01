#include <cmath>

#include "CrazyEngine/Math/Calculator.h"

namespace CrazyEngine
{
    float Calculator::DegreesToRadians(float angle)
    {
        return angle * Pi / 180.0f;
    }

    float Calculator::RadiansToDegrees(float angle)
    {
        return angle * 180.0f / Pi;
    }

    float Calculator::WrapAngle(float angle)
    {
        return angle - (floorf(angle / 360.0f) * 360.0f);
    }

    float Calculator::WrapAngle180(float angle)
    {
        float wrappedAngle = WrapAngle(angle);

        if (wrappedAngle > 180.0f)
        {
            wrappedAngle = -(360.0f - wrappedAngle);
        }

        return wrappedAngle;
    }

    float Calculator::Lerp(float a, float b, float t)
    {
        return (1.0f - t) * a + t * b;
    }

    float Calculator::Clamp(const float value, const float lower, const float upper)
    {
        if (value < lower)
        {
            return lower;
        }
        else if (value > upper)
        {
            return upper;
        }

        return value;
    }

    std::uint32_t Calculator::Max(const std::uint32_t a, const std::uint32_t b)
    {
        if (a <= b)
        {
            return b;
        }

        return a;
    }

    std::uint32_t Calculator::Min(const std::uint32_t a, const std::uint32_t b)
    {
        if (a <= b)
        {
            return a;
        }

        return b;
    }

    float Calculator::Maxf(const float a, const float b)
    {
        if (a <= b)
        {
            return b;
        }

        return a;
    }

    float Calculator::Minf(const float a, const float b)
    {
        if (a <= b)
        {
            return a;
        }

        return b;
    }

    std::uint32_t Calculator::Mod(std::int32_t a, std::uint32_t m)
    {
        std::int32_t result = a % m;
        return result >= 0 ? result : result + m;
    }
}