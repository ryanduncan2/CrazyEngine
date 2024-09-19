#ifndef CRAZYENGINE_MATH_VECTOR4_H_
#define CRAZYENGINE_MATH_VECTOR4_H_

#include <vector>
#include <string>
#include <iostream>

#include "CrazyEngine/Math/Vector2.h"
#include "CrazyEngine/Math/Vector3.h"

namespace CrazyEngine
{
    class Vector4
    {
    public:
    
        float X;
        float Y;
        float Z;
        float W;

        static const Vector4 Zero;
        static const Vector4 One;
        static const Vector4 UnitX;
        static const Vector4 UnitY;
        static const Vector4 UnitZ;
        static const Vector4 UnitW;

        Vector4(const float x, const float y, const float z, const float w) noexcept;
        Vector4(const Vector2& vector, const float z, const float w) noexcept;
        Vector4(const Vector3& vector, const float w) noexcept;
        Vector4(const float value) noexcept;
        Vector4() noexcept;

        float Dot(const Vector4& vector) const noexcept;
        float Magnitude() const noexcept;
        float Distance(const Vector4& vector) const noexcept;
        float DistanceSquared(const Vector4& vector) const noexcept;
        void Clamp(const Vector4& firstBound, const Vector4& secondBound) noexcept;
        std::string ToString() const noexcept;
        const std::vector<float> ToStdVector() const noexcept;

        // Binary Operations
        void Add(const Vector4& vector) noexcept;
        void Subtract(const Vector4& vector) noexcept;
        void Multiply(const float scalar) noexcept;
        void Multiply(const Vector4& vector) noexcept;
        void Divide(const float scalar);
        void Divide(const Vector4& vector);
        bool Equals(const Vector4& vector) const noexcept;

        // Unary Operations
        void Negate() noexcept;
        void Floor() noexcept;
        void Ceiling() noexcept;
        void Round() noexcept;
        void Abs() noexcept;
        void Normalise() noexcept;

        // Operators
        void operator+=(const Vector4& vector) noexcept;
        void operator-=(const Vector4& vector) noexcept;
        void operator*=(const float scalar) noexcept;
        void operator*=(const Vector4& vector) noexcept;
        void operator/=(const float scalar);
        void operator/=(const Vector4& vector);

        Vector4 operator-() const noexcept;
        float operator[](int index) const;
        float& operator[](int index);

        static Vector4 Max(const Vector4& firstVector, const Vector4& secondVector) noexcept;
        static Vector4 Min(const Vector4& firstVector, const Vector4& secondVector) noexcept;
        static Vector4 Lerp(const Vector4& firstVector, const Vector4& secondVector, const float t) noexcept;
    };
}

CrazyEngine::Vector4 operator+(const CrazyEngine::Vector4& firstVector, const CrazyEngine::Vector4& secondVector) noexcept;
CrazyEngine::Vector4 operator-(const CrazyEngine::Vector4& firstVector, const CrazyEngine::Vector4& secondVector) noexcept;
CrazyEngine::Vector4 operator*(const CrazyEngine::Vector4& vector, const float scalar) noexcept;
CrazyEngine::Vector4 operator*(const CrazyEngine::Vector4& firstVector, const CrazyEngine::Vector4& secondVector) noexcept;
CrazyEngine::Vector4 operator/(const CrazyEngine::Vector4& vector, const float scalar);
CrazyEngine::Vector4 operator/(const CrazyEngine::Vector4& firstVector, const CrazyEngine::Vector4& secondVector);
bool operator==(const CrazyEngine::Vector4& firstVector, const CrazyEngine::Vector4& secondVector) noexcept;
bool operator!=(const CrazyEngine::Vector4& firstVector, const CrazyEngine::Vector4& secondVector) noexcept;
std::ostream& operator<<(std::ostream& os, const CrazyEngine::Vector4& vector) noexcept;

#endif