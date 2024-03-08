#include <cmath>

#include "CrazyEngine/Math/Calculator.h"

namespace CrazyEngine
{
    constexpr float Calculator::DegreesToRadians(float angle)
    {
        return angle * Pi / 180.0f;
    }

    constexpr float Calculator::RadiansToDegrees(float angle)
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

    constexpr float Calculator::Clamp(const float value, const float lower, const float upper)
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
}