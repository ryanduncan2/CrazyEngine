#ifndef CRAZYENGINE_MATH_RECTANGLE_H_
#define CRAZYENGINE_MATH_RECTANGLE_H_

#include <iostream>

#include "CrazyEngine/Math/Vector2.h"

namespace CrazyEngine
{
    template <typename T>
    class Rectangle
    {
    static_assert(std::is_same<float, T>() || 
                  std::is_same<std::int32_t, T>() || 
                  std::is_same<double, T>() || 
                  std::is_same<std::int16_t, T>() ||
                  std::is_same<std::int64_t, T>());

    public:
        T X;
        T Y;
        T Width;
        T Height;

        Rectangle() : X(0), Y(0), Width(0), Height(0) { }
        Rectangle(const Vector2& position, const T width, const T height) : X(position.X), Y(position.Y), Width(width), Height(height) { }
        Rectangle(const T x, const T y, const T width, const T height) : X(x), Y(y), Width(width), Height(height) { }

        inline T GetTop() const noexcept { return Y; }
        inline T GetBottom() const noexcept { return Y + Height; }
        inline T GetLeft() const noexcept { return X; }
        inline T GetRight() const noexcept { return X + Width; }
        inline Vector2 GetPosition() const noexcept { return Vector2(X, Y); }
        inline Vector2 GetCentre() const noexcept { return Vector2(X + (Width / 2), Y + (Height / 2)); }
        inline Vector2 GetSize() const noexcept { return Vector2(Width, Height); }

        std::string ToString() const noexcept { return "Rectangle[X: " + std::to_string(X) + ", Y: " + std::to_string(Y) + ", Width: " + std::to_string(Width) + ", Height: " + std::to_string(Height) + "]"; }

        bool Contains(const Vector2& vector) const noexcept { return (vector.X >= X) && (vector.X <= GetRight()) && (vector.Y >= Y) && (vector.Y <= GetBottom()); }
        bool Contains(const Rectangle<T>& rect) const noexcept { return (X <= rect.X) && (GetRight() >= rect.GetRight()) && (Y <= rect.Y) && (GetBottom() >= rect.GetBottom()); }
        bool CompletelyContains(const Vector2& vector) const noexcept { return (vector.X > X) && (vector.X < GetRight()) && (vector.Y > Y) && (vector.Y < GetBottom()); }
        bool CompletelyContains(const Rectangle<T>& rect) const noexcept { return (X < rect.X) && (GetRight() > rect.GetRight()) && (Y < rect.Y) && (GetBottom() > rect.GetBottom()); }
        bool Intersects(const Rectangle<T>& rect) const noexcept { return (X < rect.GetRight()) && (GetRight() > rect.GetLeft()) && (Y < rect.GetBottom()) && (GetBottom() > rect.Y); }
        bool IntersectsOrTouches(const Rectangle<T>& rect) const noexcept { return (X <= rect.GetRight()) && (GetRight() >= rect.GetLeft()) && (Y <= rect.GetBottom()) && (GetBottom() >= rect.Y); }
        bool Equals(const Rectangle<T>& rect) const noexcept { return (X == rect.X) && (Y == rect.Y) && (Width == rect.Width) && (Height == rect.Height); }

        void operator+=(const Rectangle<T>& rect) noexcept
        {
            X = std::min(X, rect.X);
            Y = std::min(Y, rect.Y);
            Width = std::max(GetRight() - X, rect.GetRight() - X);
            Height = std::max(GetBottom() - Y, rect.GetBottom() - Y);
        }
    };

    typedef Rectangle<int> Rectanglei;
    typedef Rectangle<float> Rectanglef;
    typedef Rectangle<double> Rectangled;
}

template<class T>
std::ostream& operator<<(std::ostream& os, const CrazyEngine::Rectangle<T>& rect) noexcept
{
    return os << rect.ToString();
}

template<class T>
CrazyEngine::Rectangle<T> operator+(CrazyEngine::Rectangle<T>& firstRect, CrazyEngine::Rectangle<T>& secondRect) noexcept
{
    float X = std::min(firstRect.X, secondRect.X);
    float Y = std::min(firstRect.Y, secondRect.Y);

    CrazyEngine::Rectangle<T> rect = (X, Y, 
                                    std::max(firstRect.GetRight() - X, secondRect.GetRight() - X), 
                                    std::max(firstRect.GetBottom() - Y, secondRect.GetBottom() - Y));
}

template<class T>
bool operator==(const CrazyEngine::Rectangle<T>& firstRect, const CrazyEngine::Rectangle<T>& secondRect) noexcept
{
    return firstRect.Equals(secondRect);
}

template<class T>
bool operator!=(const CrazyEngine::Rectangle<T>& firstRect, const CrazyEngine::Rectangle<T>& secondRect) noexcept
{
    return !firstRect.Equals(secondRect);
}

#endif