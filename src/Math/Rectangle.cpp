#include "CrazyEngine/Math/Rectangle.h"

namespace CrazyEngine
{
    Rectangle::Rectangle() : X(0), Y(0), Width(0), Height(0)
    {
    }
    
    Rectangle::Rectangle(const Vector2& position, const int width, const int height) : X(position.X), Y(position.Y), Width(width), Height(height)
    {
    }
    
    Rectangle::Rectangle(const int x, const int y, const int width, const int height) : X(x), Y(y), Width(width), Height(height)
    {
    }

    std::string Rectangle::ToString() const noexcept 
    {
        return "Rectangle[X: " + std::to_string(X) + ", Y: " + std::to_string(Y) + ", Width: " + std::to_string(Width) + ", Height: " + std::to_string(Height) + "]";
    }

    bool Rectangle::Contains(const Vector2& vector) const noexcept 
    {
        return (vector.X >= X) && (vector.X <= GetRight()) && (vector.Y >= Y) && (vector.Y <= GetBottom());
    }
    
    bool Rectangle::Contains(const Rectangle& rect) const noexcept 
    {
        return (X <= rect.X) && (GetRight() >= rect.GetRight()) && (Y <= rect.Y) && (GetBottom() >= rect.GetBottom());
    }
    
    bool Rectangle::CompletelyContains(const Vector2& vector) const noexcept 
    {
        return (vector.X > X) && (vector.X < GetRight()) && (vector.Y > Y) && (vector.Y < GetBottom());
    }
    
    bool Rectangle::CompletelyContains(const Rectangle& rect) const noexcept 
    {
        return (X < rect.X) && (GetRight() > rect.GetRight()) && (Y < rect.Y) && (GetBottom() > rect.GetBottom());
    }
    
    bool Rectangle::Intersects(const Rectangle& rect) const noexcept 
    {
        return (X < rect.GetRight()) && (GetRight() > rect.GetLeft()) && (Y < rect.GetBottom()) && (GetBottom() > rect.Y);
    }
    
    bool Rectangle::IntersectsOrTouches(const Rectangle& rect) const noexcept 
    {
        return (X <= rect.GetRight()) && (GetRight() >= rect.GetLeft()) && (Y <= rect.GetBottom()) && (GetBottom() >= rect.Y);
    }
    
    bool Rectangle::Equals(const Rectangle& rect) const noexcept 
    {
        return (X == rect.X) && (Y == rect.Y) && (Width == rect.Width) && (Height == rect.Height);
    }

    void Rectangle::operator+=(const Rectangle& rect) noexcept 
    {
        X = std::min(X, rect.X);
        Y = std::min(Y, rect.Y);
        Width = std::max(GetRight() - X, rect.GetRight() - X);
        Height = std::max(GetBottom() - Y, rect.GetBottom() - Y);
    }
}

std::ostream& operator<<(std::ostream& cout, const CrazyEngine::Rectangle& rect) noexcept
{
    return cout << rect.ToString();
}

CrazyEngine::Rectangle operator+(CrazyEngine::Rectangle& firstRect, CrazyEngine::Rectangle& secondRect) noexcept
{
    float X = std::min(firstRect.X, secondRect.X);
    float Y = std::min(firstRect.Y, secondRect.Y);

    return CrazyEngine::Rectangle(X, Y, std::max(firstRect.GetRight() - X, secondRect.GetRight() - X), std::max(firstRect.GetBottom() - Y, secondRect.GetBottom() - Y));
}

bool operator==(const CrazyEngine::Rectangle& firstRect, const CrazyEngine::Rectangle& secondRect) noexcept
{
    return firstRect.Equals(secondRect);
}

bool operator!=(const CrazyEngine::Rectangle& firstRect, const CrazyEngine::Rectangle& secondRect) noexcept
{
    return (firstRect.X != secondRect.X) || (firstRect.Y != secondRect.Y) || (firstRect.Width != secondRect.Width) || (firstRect.Height != secondRect.Height);
}
