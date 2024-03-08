#include "CrazyEngine/Math/Vector4.h"

#include <cmath>
#include <algorithm>

namespace CrazyEngine
{
    const Vector4 Zero = Vector4(0, 0, 0, 0);
    const Vector4 One = Vector4(1, 1, 1, 1);
    const Vector4 UnitX = Vector4(1, 0, 0, 0);
    const Vector4 UnitY = Vector4(0, 1, 0, 0);
    const Vector4 UnitZ = Vector4(0, 0, 1, 0);
    const Vector4 UnitW = Vector4(0, 0, 0, 1);

    Vector4::Vector4(const float x, const float y, const float z, const float w) noexcept : X(x), Y(y), Z(z), W(w)
    {
    }

    Vector4::Vector4(const Vector2& vector, const float z, const float w) noexcept : X(vector.X), Y(vector.Y), Z(z), W(w)
    {
    }

    Vector4::Vector4(const Vector3& vector, const float w) noexcept : X(vector.X), Y(vector.Y), Z(vector.Z), W(w)
    {
    }

    Vector4::Vector4(const float value) noexcept : X(value), Y(value), Z(value), W(value)
    {
    }

    Vector4::Vector4() noexcept : X(0), Y(0), Z(0), W(0)
    {
    }

    float Vector4::Dot(const Vector4& vector) const noexcept
    {
        return (X * vector.X) + (Y * vector.Y) + (Z * vector.Z) + (W * vector.W);
    }

    float Vector4::Magnitude() const noexcept
    {
        return sqrt((X * X) + (Y * Y) + (Z * Z) + (W * W));
    }

    float Vector4::Distance(const Vector4& vector) const noexcept
    {
        return sqrt(((X - vector.X) * (X - vector.X)) + ((Y - vector.Y) * (Y - vector.Y)) + ((Z - vector.Z) * (Z - vector.Z)) + ((W - vector.W) * (W - vector.W)));
    }

    float Vector4::DistanceSquared(const Vector4& vector) const noexcept
    {
        return ((X - vector.X) * (X - vector.X)) + ((Y - vector.Y) * (Y - vector.Y)) + ((Z - vector.Z) * (Z - vector.Z)) + ((W - vector.W) * (W - vector.W));
    }

    void Vector4::Clamp(const Vector4& firstBound, const Vector4& secondBound) noexcept
    {
        X = std::clamp(X, std::min(firstBound.X, secondBound.X), std::max(firstBound.X, secondBound.X));
        Y = std::clamp(Y, std::min(firstBound.Y, secondBound.Y), std::max(firstBound.Y, secondBound.Y));
        Z = std::clamp(Y, std::min(firstBound.Z, secondBound.Z), std::max(firstBound.Z, secondBound.Z));
        W = std::clamp(Y, std::min(firstBound.W, secondBound.W), std::max(firstBound.W, secondBound.W));
    }

    std::string Vector4::ToString() const noexcept
    {
        return "Vector4[X: " + std::to_string(X) + ", Y: " + std::to_string(Y) + ", Z: " + std::to_string(Z) + ", W: " + std::to_string(W) + "]";
    }

    const std::vector<float> Vector4::ToStdVector() const noexcept
    {
        return { X, Y, Z, W };
    }

    void Vector4::Add(const Vector4& vector) noexcept
    {
        X += vector.X;
        Y += vector.Y;
        Z += vector.Z;
        W += vector.W;
    }

    void Vector4::Subtract(const Vector4& vector) noexcept
    {
        X -= vector.X;
        Y -= vector.Y;
        Z -= vector.Z;
        W -= vector.W;
    }

    void Vector4::Multiply(const float scalar) noexcept
    {
        X *= scalar;
        Y *= scalar;
        Z *= scalar;
        W *= scalar;
    }

    void Vector4::Multiply(const Vector4& vector) noexcept
    {
        X *= vector.X;
        Y *= vector.Y;
        Z *= vector.Z;
        W *= vector.W;
    }

    void Vector4::Divide(const float scalar)
    {
        if (scalar == 0)
        {
            throw std::string("Vector4::Divide", "Divisor cannot be zero.");
        }

        X /= scalar;
        Y /= scalar;
        Z /= scalar;
        W /= scalar;
    }

    void Vector4::Divide(const Vector4& vector)
    {
        if (vector.X == 0 || vector.Y == 0 || vector.Z == 0 || vector.W == 0)
        {
            throw std::string("Vector4::Divide", "Divisor cannot be zero.");
        }

        X /= vector.X;
        Y /= vector.Y;
        Z /= vector.Z;
        W /= vector.W;
    }
    
    bool Vector4::Equals(const Vector4& vector) const noexcept
    {
        return X == vector.X && Y == vector.Y && Z == vector.Z && W == vector.W;
    }

    void Vector4::Negate() noexcept
    {
        X = -X;
        Y = -Y;
        Z = -Z;
        W = -W;
    }

    void Vector4::Floor() noexcept
    {
        X = floorf(X);
        Y = floorf(Y);
        Z = floorf(Z);
        W = floorf(W);
    }
    
    void Vector4::Ceiling() noexcept
    {
        X = ceilf(X);
        Y = ceilf(Y);
        Z = ceilf(Z);
        W = ceilf(W);
    }
    
    void Vector4::Round() noexcept
    {
        X = roundf(X);
        Y = roundf(Y);
        Z = roundf(Z);
        W = roundf(W);
    }

    void Vector4::Abs() noexcept
    {
        X = abs(X);
        Y = abs(Y);
        Z = abs(Z);
        W = abs(W);
    }
    
    void Vector4::Normalise() noexcept
    {
        float magnitude = Magnitude();

        if (magnitude != 0)
        {
            X /= magnitude;
            Y /= magnitude;
            Z /= magnitude;
            W /= magnitude;
        }
    }
    
    void Vector4::operator+=(const Vector4& vector) noexcept
    {
        X += vector.X;
        Y += vector.Y;
        Z += vector.Z;
        W += vector.W;
    }
    
    void Vector4::operator-=(const Vector4& vector) noexcept
    {
        X -= vector.X;
        Y -= vector.Y;
        Z -= vector.Z;
        W -= vector.W;
    }
        
    void Vector4::operator*=(const float scalar) noexcept
    {
        X *= scalar;
        Y *= scalar;
        Z *= scalar;
        W *= scalar;
    }

    void Vector4::operator*=(const Vector4& vector) noexcept
    {
        X *= vector.X;
        Y *= vector.Y;
        Z *= vector.Z;
        W *= vector.W;
    }
    
    void Vector4::operator/=(const float scalar)
    {
        if (scalar == 0)
        {
            throw std::string("Vector4::operator /=", "Divisor cannot be zero.");
        }

        X /= scalar;
        Y /= scalar;
        Z /= scalar;
        W /= scalar;
    }

    void Vector4::operator/=(const Vector4& vector)
    {
        if (vector.X == 0 || vector.Y == 0 || vector.Z == 0 || vector.W == 0)
        {
            throw std::string("Vector4::operator /=", "Divisor cannot be zero.");
        }

        X /= vector.X;
        Y /= vector.Y;
        Z /= vector.Z;
        W /= vector.W;
    }

    Vector4 Vector4::operator-() const noexcept
    {
        return Vector4(-X, -Y, -Z, -W);
    }
    
    float Vector4::operator[](int index) const
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
        else if (index == 3)
        {
            return W;
        }
        else
        {
            throw std::string("Vector4::operator []", "Index out of bounds of Vector4.");
        }
    }

    float& Vector4::operator[](int index)
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
        else if (index == 3)
        {
            return W;
        }
        else
        {
            throw std::string("Vector4::operator []", "Index out of bounds of Vector4.");
        }
    }

    Vector4 Vector4::Max(const Vector4& firstVector, const Vector4& secondVector) noexcept
    {
        return Vector4(std::max(firstVector.X, secondVector.X), std::max(firstVector.Y, secondVector.Y), std::max(firstVector.Z, secondVector.Z), std::max(firstVector.W, secondVector.W));
    }

    Vector4 Vector4::Min(const Vector4& firstVector, const Vector4& secondVector) noexcept
    {
        return Vector4(std::min(firstVector.X, secondVector.X), std::min(firstVector.Y, secondVector.Y), std::min(firstVector.Z, secondVector.Z), std::min(firstVector.W, secondVector.W));
    }

    Vector4 Vector4::Lerp(const Vector4& firstVector, const Vector4& secondVector, const float t) noexcept
    {
        return Vector4(firstVector.X + (secondVector.X - firstVector.X) * t, firstVector.Y + (secondVector.Y - firstVector.Y) * t, firstVector.Z + (secondVector.Z - firstVector.Z) * t, firstVector.W + (secondVector.W - firstVector.W) * t);
    }
}

CrazyEngine::Vector4 operator+(const CrazyEngine::Vector4& firstVector, const CrazyEngine::Vector4& secondVector) noexcept
{
    return CrazyEngine::Vector4(firstVector.X + secondVector.X, firstVector.Y + secondVector.Y, firstVector.Z + secondVector.Z, firstVector.W + secondVector.W);
}

CrazyEngine::Vector4 operator-(const CrazyEngine::Vector4& firstVector, const CrazyEngine::Vector4& secondVector) noexcept
{
    return CrazyEngine::Vector4(firstVector.X - secondVector.X, firstVector.Y - secondVector.Y, firstVector.Z - secondVector.Z, firstVector.W - secondVector.W);
}

CrazyEngine::Vector4 operator*(const CrazyEngine::Vector4& vector, const float scalar) noexcept
{
    return CrazyEngine::Vector4(vector.X * scalar, vector.Y * scalar, vector.Z * scalar, vector.W * scalar);
}

CrazyEngine::Vector4 operator*(const CrazyEngine::Vector4& firstVector, const CrazyEngine::Vector4& secondVector) noexcept
{
    return CrazyEngine::Vector4(firstVector.X * secondVector.X, firstVector.Y * secondVector.Y, firstVector.Z * secondVector.Z, firstVector.W * secondVector.W);
}

CrazyEngine::Vector4 operator/(const CrazyEngine::Vector4& vector, const float scalar)
{
    if (scalar == 0)
    {
        throw std::string("Vector4 Division by zero.");
    }

    return CrazyEngine::Vector4(vector.X / scalar, vector.Y / scalar, vector.Z / scalar, vector.W / scalar);
}

CrazyEngine::Vector4 operator/(const CrazyEngine::Vector4& firstVector, const CrazyEngine::Vector4& secondVector)
{
    if (secondVector.X == 0 || secondVector.Y == 0 || secondVector.Z == 0 || secondVector.W == 0)
    {
        throw std::string("Vector4 Division by zero.");
    }

    return CrazyEngine::Vector4(firstVector.X / secondVector.X, firstVector.Y / secondVector.Y, firstVector.Z / secondVector.Z, firstVector.W / secondVector.W);
}

bool operator==(const CrazyEngine::Vector4& firstVector, const CrazyEngine::Vector4& secondVector) noexcept
{
    return firstVector.X == secondVector.X && firstVector.Y == secondVector.Y && firstVector.Z == secondVector.Z && firstVector.W == secondVector.W;
}

bool operator!=(const CrazyEngine::Vector4& firstVector, const CrazyEngine::Vector4& secondVector) noexcept
{
    return firstVector.X != secondVector.X || firstVector.Y != secondVector.Y || firstVector.Z != secondVector.Z || firstVector.W != secondVector.W;
}

std::ostream& operator<<(std::ostream& os, const CrazyEngine::Vector4& vector) noexcept
{
    return os << vector.ToString();
}
