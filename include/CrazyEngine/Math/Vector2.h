#ifndef CRAZYENGINE_MATH_VECTOR2_H_
#define CRAZYENGINE_MATH_VECTOR2_H_

#include <vector>
#include <string>
#include <iostream>

namespace CrazyEngine
{
    class Vector2
    {
    public:
        float X;
        float Y;

        static const Vector2 Zero;
        static const Vector2 One;
        static const Vector2 UnitX;
        static const Vector2 UnitY;

        Vector2(const float x, const float y) noexcept;
        Vector2(const float value) noexcept;
        Vector2() noexcept;

        float Dot(const Vector2& vector) const noexcept;
        float Magnitude() const noexcept;
        float Distance(const Vector2& vector) const noexcept;
        float DistanceSquared(const Vector2& vector) const noexcept;
        void Clamp(const Vector2& firstBound, const Vector2& secondBound) noexcept;
        std::string ToString() const noexcept;
        const std::vector<float> ToStdVector() const noexcept;

        // Binary Operations
        void Add(const Vector2& vector) noexcept;
        void Subtract(const Vector2& vector) noexcept;
        void Multiply(const float scalar) noexcept;
        void Multiply(const Vector2& vector) noexcept;
        void Divide(const float scalar);
        void Divide(const Vector2& vector);
        bool Equals(const Vector2& vector) const noexcept;

        // Unary Operations
        void Negate() noexcept;
        void Floor() noexcept;
        void Ceiling() noexcept;
        void Round() noexcept;
        void Abs() noexcept;
        void Normalise() noexcept;

        // Operators
        void operator+=(const Vector2& vector) noexcept;
        void operator-=(const Vector2& vector) noexcept;
        void operator*=(const float scalar) noexcept;
        void operator*=(const Vector2& vector) noexcept;
        void operator/=(const float scalar);
        void operator/=(const Vector2& vector);

        Vector2 operator-() const noexcept;
        float operator[](int index) const;
        float& operator[](int index);

        static Vector2 Max(const Vector2& firstVector, const Vector2& secondVector) noexcept;
        static Vector2 Min(const Vector2& firstVector, const Vector2& secondVector) noexcept;
        static Vector2 Lerp(const Vector2& firstVector, const Vector2& secondVector, const float t) noexcept;
    };
}

CrazyEngine::Vector2 operator+(const CrazyEngine::Vector2& firstVector, const CrazyEngine::Vector2& secondVector) noexcept;
CrazyEngine::Vector2 operator-(const CrazyEngine::Vector2& firstVector, const CrazyEngine::Vector2& secondVector) noexcept;
CrazyEngine::Vector2 operator*(const CrazyEngine::Vector2& vector, const float scalar) noexcept;
CrazyEngine::Vector2 operator*(const CrazyEngine::Vector2& firstVector, const CrazyEngine::Vector2& secondVector) noexcept;
CrazyEngine::Vector2 operator/(const CrazyEngine::Vector2& vector, const float scalar);
CrazyEngine::Vector2 operator/(const CrazyEngine::Vector2& firstVector, const CrazyEngine::Vector2& secondVector);
bool operator==(const CrazyEngine::Vector2& firstVector, const CrazyEngine::Vector2& secondVector) noexcept;
bool operator!=(const CrazyEngine::Vector2& firstVector, const CrazyEngine::Vector2& secondVector) noexcept;
std::ostream& operator<<(std::ostream& os, const CrazyEngine::Vector2& vector) noexcept;

#endif