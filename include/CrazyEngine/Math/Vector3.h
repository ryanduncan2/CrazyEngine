#ifndef CRAZYENGINE_MATH_VECTOR3_H_
#define CRAZYENGINE_MATH_VECTOR3_H_

#include <vector>
#include <string>
#include <iostream>

#include "CrazyEngine/Math/Vector2.h"

namespace CrazyEngine
{
    class Vector3
    {
    public:
    
        float X;
        float Y;
        float Z;

        static const Vector3 Zero;
        static const Vector3 One;
        static const Vector3 UnitX;
        static const Vector3 UnitY;
        static const Vector3 UnitZ;

        Vector3(const float x, const float y, const float z) noexcept;
        Vector3(const Vector2& vector, const float z) noexcept;
        Vector3(const float value) noexcept;
        Vector3() noexcept;

        float Dot(const Vector3& vector) const noexcept;
        Vector3 Cross(const Vector3& vector) const noexcept;
        float Magnitude() const noexcept;
        float Distance(const Vector3& vector) const noexcept;
        float DistanceSquared(const Vector3& vector) const noexcept;
        void Clamp(const Vector3& firstBound, const Vector3& secondBound) noexcept;
        std::string ToString() const noexcept;
        const std::vector<float> ToStdVector() const noexcept;

        // Binary Operations
        void Add(const Vector3& vector) noexcept;
        void Subtract(const Vector3& vector) noexcept;
        void Multiply(const float scalar) noexcept;
        void Multiply(const Vector3& vector) noexcept;
        void Divide(const float scalar);
        void Divide(const Vector3& vector);
        bool Equals(const Vector3& vector) const noexcept;

        // Unary Operations
        void Negate() noexcept;
        void Floor() noexcept;
        void Ceiling() noexcept;
        void Round() noexcept;
        void Abs() noexcept;
        void Normalise() noexcept;

        // Operators
        void operator+=(const Vector3& vector) noexcept;
        void operator-=(const Vector3& vector) noexcept;
        void operator*=(const float scalar) noexcept;
        void operator*=(const Vector3& vector) noexcept;
        void operator/=(const float scalar);
        void operator/=(const Vector3& vector);

        Vector3 operator-() const noexcept;
        float operator[](int index) const;
        float& operator[](int index);

        static Vector3 Max(const Vector3& firstVector, const Vector3& secondVector) noexcept;
        static Vector3 Min(const Vector3& firstVector, const Vector3& secondVector) noexcept;
        static Vector3 Lerp(const Vector3& firstVector, const Vector3& secondVector, const float t) noexcept;
    };
}

CrazyEngine::Vector3 operator+(const CrazyEngine::Vector3& firstVector, const CrazyEngine::Vector3& secondVector) noexcept;
CrazyEngine::Vector3 operator-(const CrazyEngine::Vector3& firstVector, const CrazyEngine::Vector3& secondVector) noexcept;
CrazyEngine::Vector3 operator*(const CrazyEngine::Vector3& vector, const float scalar) noexcept;
CrazyEngine::Vector3 operator*(const CrazyEngine::Vector3& firstVector, const CrazyEngine::Vector3& secondVector) noexcept;
CrazyEngine::Vector3 operator/(const CrazyEngine::Vector3& vector, const float scalar);
CrazyEngine::Vector3 operator/(const CrazyEngine::Vector3& firstVector, const CrazyEngine::Vector3& secondVector);
bool operator==(const CrazyEngine::Vector3& firstVector, const CrazyEngine::Vector3& secondVector) noexcept;
bool operator!=(const CrazyEngine::Vector3& firstVector, const CrazyEngine::Vector3& secondVector) noexcept;
std::ostream& operator<<(std::ostream& os, const CrazyEngine::Vector3& vector) noexcept;

#endif