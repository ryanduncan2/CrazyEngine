#include "CrazyEngine/Math/Vector3.h"

#include <cmath>
#include <algorithm>

namespace CrazyEngine
{
    const Vector3 Zero = Vector3(0, 0, 0);
    const Vector3 One = Vector3(1, 1, 1);
    const Vector3 UnitX = Vector3(1, 0, 0);
    const Vector3 UnitY = Vector3(0, 1, 0);
    const Vector3 UnitZ = Vector3(0, 0, 1);

    Vector3::Vector3(const float x, const float y, const float z) noexcept : X(x), Y(y), Z(z)
    {
    }

    Vector3::Vector3(const Vector2& vector, const float z) noexcept : X(vector.X), Y(vector.Y), Z(z)
    {
    }

    Vector3::Vector3(const float value) noexcept : X(value), Y(value), Z(value)
    {
    }

    Vector3::Vector3() noexcept : X(0), Y(0), Z(0)
    {
    }

    float Vector3::Dot(const Vector3& vector) const noexcept
    {
        return (X * vector.X) + (Y * vector.Y) + (Z * vector.Z);
    }

    Vector3 Vector3::Cross(const Vector3& vector) const noexcept
    {
        return Vector3(Y * vector.Z - Z * vector.Y, Z * vector.X - X * vector.Z, X * vector.Y - Y * vector.X);
    }

    float Vector3::Magnitude() const noexcept
    {
        return sqrt((X * X) + (Y * Y) + (Z * Z));
    }

    float Vector3::Distance(const Vector3& vector) const noexcept
    {
        return sqrt(((X - vector.X) * (X - vector.X)) + ((Y - vector.Y) * (Y - vector.Y)) + ((Z - vector.Z) * (Z - vector.Z)));
    }

    float Vector3::DistanceSquared(const Vector3& vector) const noexcept
    {
        return ((X - vector.X) * (X - vector.X)) + ((Y - vector.Y) * (Y - vector.Y)) + ((Z - vector.Z) * (Z - vector.Z));
    }

    void Vector3::Clamp(const Vector3& firstBound, const Vector3& secondBound) noexcept
    {
        X = std::clamp(X, std::min(firstBound.X, secondBound.X), std::max(firstBound.X, secondBound.X));
        Y = std::clamp(Y, std::min(firstBound.Y, secondBound.Y), std::max(firstBound.Y, secondBound.Y));
        Z = std::clamp(Y, std::min(firstBound.Z, secondBound.Z), std::max(firstBound.Z, secondBound.Z));
    }

    std::string Vector3::ToString() const noexcept
    {
        return "Vector3[X: " + std::to_string(X) + ", Y: " + std::to_string(Y) + ", Z: " + std::to_string(Z) + "]";
    }

    const std::vector<float> Vector3::ToStdVector() const noexcept
    {
        return { X, Y, Z };
    }

    void Vector3::Add(const Vector3& vector) noexcept
    {
        X += vector.X;
        Y += vector.Y;
        Z += vector.Z;
    }

    void Vector3::Subtract(const Vector3& vector) noexcept
    {
        X -= vector.X;
        Y -= vector.Y;
        Z -= vector.Z;
    }

    void Vector3::Multiply(const float scalar) noexcept
    {
        X *= scalar;
        Y *= scalar;
        Z *= scalar;
    }

    void Vector3::Multiply(const Vector3& vector) noexcept
    {
        X *= vector.X;
        Y *= vector.Y;
        Z *= vector.Z;
    }

    void Vector3::Divide(const float scalar)
    {
        if (scalar == 0)
        {
            throw std::string("Vector3::Divide", "Divisor cannot be zero.");
        }

        X /= scalar;
        Y /= scalar;
        Z /= scalar;
    }

    void Vector3::Divide(const Vector3& vector)
    {
        if (vector.X == 0 || vector.Y == 0 || vector.Z == 0)
        {
            throw std::string("Vector3::Divide", "Divisor cannot be zero.");
        }

        X /= vector.X;
        Y /= vector.Y;
        Z /= vector.Z;
    }
    
    bool Vector3::Equals(const Vector3& vector) const noexcept
    {
        return X == vector.X && Y == vector.Y && Z == vector.Z;
    }

    void Vector3::Negate() noexcept
    {
        X = -X;
        Y = -Y;
        Z = -Z;
    }

    void Vector3::Floor() noexcept
    {
        X = floorf(X);
        Y = floorf(Y);
        Z = floorf(Z);
    }
    
    void Vector3::Ceiling() noexcept
    {
        X = ceilf(X);
        Y = ceilf(Y);
        Z = ceilf(Z);
    }
    
    void Vector3::Round() noexcept
    {
        X = roundf(X);
        Y = roundf(Y);
        Z = roundf(Z);
    }

    void Vector3::Abs() noexcept
    {
        X = abs(X);
        Y = abs(Y);
        Z = abs(Z);
    }
    
    void Vector3::Normalise() noexcept
    {
        float magnitude = Magnitude();

        if (magnitude != 0)
        {
            X /= magnitude;
            Y /= magnitude;
            Z /= magnitude;
        }
    }
    
    void Vector3::operator+=(const Vector3& vector) noexcept
    {
        X += vector.X;
        Y += vector.Y;
        Z += vector.Z;
    }
    
    void Vector3::operator-=(const Vector3& vector) noexcept
    {
        X -= vector.X;
        Y -= vector.Y;
        Z -= vector.Z;
    }
        
    void Vector3::operator*=(const float scalar) noexcept
    {
        X *= scalar;
        Y *= scalar;
        Z *= scalar;
    }

    void Vector3::operator*=(const Vector3& vector) noexcept
    {
        X *= vector.X;
        Y *= vector.Y;
        Z *= vector.Z;
    }
    
    void Vector3::operator/=(const float scalar)
    {
        if (scalar == 0)
        {
            throw std::string("Vector3::operator /=", "Divisor cannot be zero.");
        }

        X /= scalar;
        Y /= scalar;
        Z /= scalar;
    }

    void Vector3::operator/=(const Vector3& vector)
    {
        if (vector.X == 0 || vector.Y == 0 || vector.Z == 0)
        {
            throw std::string("Vector3::operator /=", "Divisor cannot be zero.");
        }

        X /= vector.X;
        Y /= vector.Y;
        Z /= vector.Z;
    }

    Vector3 Vector3::operator-() const noexcept
    {
        return Vector3(-X, -Y, -Z);
    }
    
    float Vector3::operator[](int index) const
    {
        if (index == 0)
        {
            return X;
        }
        else if (index == 1)
        {
            return Y;
        }
        else if (index == 2)
        {
            return Z;
        }
        else
        {
            throw std::string("Vector3::operator []", "Index out of bounds of Vector3.");
        }
    }

    float& Vector3::operator[](int index)
    {
        if (index == 0)
        {
            return X;
        }
        else if (index == 1)
        {
            return Y;
        }
        else if (index == 2)
        {
            return Z;
        }
        else
        {
            throw std::string("Vector3::operator []", "Index out of bounds of Vector3.");
        }
    }

    Vector3 Vector3::Max(const Vector3& firstVector, const Vector3& secondVector) noexcept
    {
        return Vector3(std::max(firstVector.X, secondVector.X), std::max(firstVector.Y, secondVector.Y), std::max(firstVector.Z, secondVector.Z));
    }

    Vector3 Vector3::Min(const Vector3& firstVector, const Vector3& secondVector) noexcept
    {
        return Vector3(std::min(firstVector.X, secondVector.X), std::min(firstVector.Y, secondVector.Y), std::min(firstVector.Z, secondVector.Z));
    }

    Vector3 Vector3::Lerp(const Vector3& firstVector, const Vector3& secondVector, const float t) noexcept
    {
        return Vector3(firstVector.X + (secondVector.X - firstVector.X) * t, firstVector.Y + (secondVector.Y - firstVector.Y) * t, firstVector.Z + (secondVector.Z - firstVector.Z) * t);
    }
}

CrazyEngine::Vector3 operator+(const CrazyEngine::Vector3& firstVector, const CrazyEngine::Vector3& secondVector) noexcept
{
    return CrazyEngine::Vector3(firstVector.X + secondVector.X, firstVector.Y + secondVector.Y, firstVector.Z + secondVector.Z);
}

CrazyEngine::Vector3 operator-(const CrazyEngine::Vector3& firstVector, const CrazyEngine::Vector3& secondVector) noexcept
{
    return CrazyEngine::Vector3(firstVector.X - secondVector.X, firstVector.Y - secondVector.Y, firstVector.Z - secondVector.Z);
}

CrazyEngine::Vector3 operator*(const CrazyEngine::Vector3& vector, const float scalar) noexcept
{
    return CrazyEngine::Vector3(vector.X * scalar, vector.Y * scalar, vector.Z * scalar);
}

CrazyEngine::Vector3 operator*(const CrazyEngine::Vector3& firstVector, const CrazyEngine::Vector3& secondVector) noexcept
{
    return CrazyEngine::Vector3(firstVector.X * secondVector.X, firstVector.Y * secondVector.Y, firstVector.Z * secondVector.Z);
}

CrazyEngine::Vector3 operator/(const CrazyEngine::Vector3& vector, const float scalar)
{
    if (scalar == 0)
    {
        throw std::string("Vector3 Division by zero.");
    }

    return CrazyEngine::Vector3(vector.X / scalar, vector.Y / scalar, vector.Z / scalar);
}

CrazyEngine::Vector3 operator/(const CrazyEngine::Vector3& firstVector, const CrazyEngine::Vector3& secondVector)
{
    if (secondVector.X == 0 || secondVector.Y == 0 || secondVector.Z == 0)
    {
        throw std::string("Vector3 Division by zero.");
    }

    return CrazyEngine::Vector3(firstVector.X / secondVector.X, firstVector.Y / secondVector.Y, firstVector.Z / secondVector.Z);
}

bool operator==(const CrazyEngine::Vector3& firstVector, const CrazyEngine::Vector3& secondVector) noexcept
{
    return firstVector.X == secondVector.X && firstVector.Y == secondVector.Y && firstVector.Z == secondVector.Z;
}

bool operator!=(const CrazyEngine::Vector3& firstVector, const CrazyEngine::Vector3& secondVector) noexcept
{
    return firstVector.X != secondVector.X || firstVector.Y != secondVector.Y || firstVector.Z != secondVector.Z;
}

std::ostream& operator<<(std::ostream& os, const CrazyEngine::Vector3& vector) noexcept
{
    return os << vector.ToString();
}
