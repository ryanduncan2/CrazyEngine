#include "CrazyEngine/Math/Vector2.h"

#include <cmath>
#include <algorithm>

namespace CrazyEngine
{
    const Vector2 Zero = Vector2(0, 0);
    const Vector2 One = Vector2(1, 1);
    const Vector2 UnitX = Vector2(1, 0);
    const Vector2 UnitY = Vector2(0, 1);

    Vector2::Vector2(const float x, const float y) noexcept : X(x), Y(y) 
    {
    }

    Vector2::Vector2(const float value) noexcept : X(value), Y(value) 
    {
    }

    Vector2::Vector2() noexcept : X(0), Y(0)
    {
    }

    float Vector2::Dot(const Vector2& vector) const noexcept
    {
        return (X * vector.X) + (Y * vector.Y);
    }

    float Vector2::Magnitude() const noexcept
    {
        return sqrt((X * X) + (Y * Y));
    }

    float Vector2::Distance(const Vector2& vector) const noexcept
    {
        return sqrt(((X - vector.X) * (X - vector.X)) + ((Y - vector.Y) * (Y - vector.Y)));
    }

    float Vector2::DistanceSquared(const Vector2& vector) const noexcept
    {
        return ((X - vector.X) * (X - vector.X)) + ((Y - vector.Y) * (Y - vector.Y));
    }

    void Vector2::Clamp(const Vector2& firstBound, const Vector2& secondBound) noexcept
    {
        X = std::clamp(X, std::min(firstBound.X, secondBound.X), std::max(firstBound.X, secondBound.X));
        Y = std::clamp(Y, std::min(firstBound.Y, secondBound.Y), std::max(firstBound.Y, secondBound.Y));
    }

    std::string Vector2::ToString() const noexcept
    {
        return "Vector2[X: " + std::to_string(X) + ", Y: " + std::to_string(Y) + "]";
    }

    const std::vector<float> Vector2::ToStdVector() const noexcept
    {
        return { X, Y };
    }

    void Vector2::Add(const Vector2& vector) noexcept
    {
        X += vector.X;
        Y += vector.Y;
    }

    void Vector2::Subtract(const Vector2& vector) noexcept
    {
        X -= vector.X;
        Y -= vector.Y;
    }

    void Vector2::Multiply(const float scalar) noexcept
    {
        X *= scalar;
        Y *= scalar;
    }

    void Vector2::Multiply(const Vector2& vector) noexcept
    {
        X *= vector.X;
        Y *= vector.Y;
    }

    void Vector2::Divide(const float scalar)
    {
        if (scalar == 0)
        {
            throw std::string("Vector2::Divide", "Divisor cannot be zero.");
        }

        X /= scalar;
        Y /= scalar;
    }

    void Vector2::Divide(const Vector2& vector)
    {
        if (vector.X == 0 || vector.Y == 0)
        {
            throw std::string("Vector2::Divide", "Divisor cannot be zero.");
        }

        X /= vector.X;
        Y /= vector.Y;
    }
    
    bool Vector2::Equals(const Vector2& vector) const noexcept
    {
        return X == vector.X && Y == vector.Y;
    }

    void Vector2::Negate() noexcept
    {
        X = -X;
        Y = -Y;
    }

    void Vector2::Floor() noexcept
    {
        X = floorf(X);
        Y = floorf(Y);
    }
    
    void Vector2::Ceiling() noexcept
    {
        X = ceilf(X);
        Y = ceilf(Y);
    }
    
    void Vector2::Round() noexcept
    {
        X = roundf(X);
        Y = roundf(Y);
    }

    void Vector2::Abs() noexcept
    {
        X = abs(X);
        Y = abs(Y);
    }
    
    void Vector2::Normalise() noexcept
    {
        float magnitude = Magnitude();

        if (magnitude != 0)
        {
            X /= magnitude;
            Y /= magnitude;
        }
    }
    
    void Vector2::operator+=(const Vector2& vector) noexcept
    {
        X += vector.X;
        Y += vector.Y;
    }
    
    void Vector2::operator-=(const Vector2& vector) noexcept
    {
        X -= vector.X;
        Y -= vector.Y;
    }
        
    void Vector2::operator*=(const float scalar) noexcept
    {
        X *= scalar;
        Y *= scalar;
    }

    void Vector2::operator*=(const Vector2& vector) noexcept
    {
        X *= vector.X;
        Y *= vector.Y;
    }
    
    void Vector2::operator/=(const float scalar)
    {
        if (scalar == 0)
        {
            throw std::string("Vector2::operator /=", "Divisor cannot be zero.");
        }

        X /= scalar;
        Y /= scalar;
    }

    void Vector2::operator/=(const Vector2& vector)
    {
        if (vector.X == 0 || vector.Y == 0)
        {
            throw std::string("Vector2::operator /=", "Divisor cannot be zero.");
        }

        X /= vector.X;
        Y /= vector.Y;
    }

    Vector2 Vector2::operator-() const noexcept
    {
        return Vector2(-X, -Y);
    }
    
    float Vector2::operator[](int index) const
    {
        if (index == 0)
        {
            return X;
        }
        else if (index == 1)
        {
            return Y;
        }
        else
        {
            throw std::string("Vector2::operator []", "Index out of bounds of Vector2.");
        }
    }

    float& Vector2::operator[](int index)
    {
        if (index == 0)
        {
            return X;
        }
        else if (index == 1)
        {
            return Y;
        }
        else
        {
            throw std::string("Vector2::operator []", "Index out of bounds of Vector2.");
        }
    }

    Vector2 Vector2::Max(const Vector2& firstVector, const Vector2& secondVector) noexcept
    {
        return Vector2(std::max(firstVector.X, secondVector.X), std::max(firstVector.Y, secondVector.Y));
    }

    Vector2 Vector2::Min(const Vector2& firstVector, const Vector2& secondVector) noexcept
    {
        return Vector2(std::min(firstVector.X, secondVector.X), std::min(firstVector.Y, secondVector.Y));
    }

    Vector2 Vector2::Lerp(const Vector2& firstVector, const Vector2& secondVector, const float t) noexcept
    {
        return Vector2(firstVector.X + (secondVector.X - firstVector.X) * t, firstVector.Y + (secondVector.Y - firstVector.Y) * t);
    }
}

CrazyEngine::Vector2 operator+(const CrazyEngine::Vector2& firstVector, const CrazyEngine::Vector2& secondVector) noexcept
{
    return CrazyEngine::Vector2(firstVector.X + secondVector.X, firstVector.Y + secondVector.Y);
}

CrazyEngine::Vector2 operator-(const CrazyEngine::Vector2& firstVector, const CrazyEngine::Vector2& secondVector) noexcept
{
    return CrazyEngine::Vector2(firstVector.X - secondVector.X, firstVector.Y - secondVector.Y);
}

CrazyEngine::Vector2 operator*(const CrazyEngine::Vector2& vector, const float scalar) noexcept
{
    return CrazyEngine::Vector2(vector.X * scalar, vector.Y * scalar);
}

CrazyEngine::Vector2 operator*(const CrazyEngine::Vector2& firstVector, const CrazyEngine::Vector2& secondVector) noexcept
{
    return CrazyEngine::Vector2(firstVector.X * secondVector.X, firstVector.Y * secondVector.Y);
}

CrazyEngine::Vector2 operator/(const CrazyEngine::Vector2& vector, const float scalar)
{
    if (scalar == 0)
    {
        throw std::string("Vector2 Division by zero.");
    }

    return CrazyEngine::Vector2(vector.X / scalar, vector.Y / scalar);
}

CrazyEngine::Vector2 operator/(const CrazyEngine::Vector2& firstVector, const CrazyEngine::Vector2& secondVector)
{
    if (secondVector.X == 0 || secondVector.Y == 0)
    {
        throw std::string("Vector2 Division by zero.");
    }

    return CrazyEngine::Vector2(firstVector.X / secondVector.X, firstVector.Y / secondVector.Y);
}

bool operator==(const CrazyEngine::Vector2& firstVector, const CrazyEngine::Vector2& secondVector) noexcept
{
    return firstVector.X == secondVector.X && firstVector.Y == secondVector.Y;
}

bool operator!=(const CrazyEngine::Vector2& firstVector, const CrazyEngine::Vector2& secondVector) noexcept
{
    return firstVector.X != secondVector.X || firstVector.Y != secondVector.Y;
}

std::ostream& operator<<(std::ostream& os, const CrazyEngine::Vector2& vector) noexcept
{
    return os << vector.ToString();
}
