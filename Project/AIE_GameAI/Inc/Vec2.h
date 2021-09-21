#pragma once
#include <math.h>
#include "raymath.h"
#include "GameObject.h"

class Vec2
{
public:
    float x = 0.0f;
    float y = 0.0f;
    // default construcot
    Vec2() {}
    // construct from raylib Vector2 class
    Vec2(const Vector2& vec) : x(vec.x), y(vec.y) {}
    // overloaded constructor
    Vec2(float x, float y) : x(x), y(y) {}

    // implicit conversion from Vec2 to raylib Vector2 class
    operator Vector2() const { return { x, y }; }
    // overload plus operator
    Vec2 operator + (const Vec2& rhs) const
    {
        return Vec2(x + rhs.x, y + rhs.y);
    }
    // overload plus equal operator
    Vec2& operator += (const Vec2& rhs)
    {
        x += rhs.x;
        y += rhs.y;
        return *this;
    }
    // overload minus operator
    Vec2 operator - (const Vec2& rhs) const
    {
        return Vec2(x - rhs.x, y - rhs.y);
    }

    // overload minus equal operator
    Vec2& operator -= (const Vec2& rhs)
    {
        x -= rhs.x;
        y -= rhs.y;
        return *this;
    }
    // overload the multiply operator
    Vec2 operator * (float rhs) const
    {
        return Vec2(x * rhs, y * rhs);
    }
    // overload the multiply equal operator
    Vec2& operator *= (float rhs)
    {
        x *= rhs;
        y *= rhs;
        return *this;
    }
    // overload the divide operator
    Vec2 operator / (float rhs) const
    {
        return Vec2(x / rhs, y / rhs);
    }
    // overload the divide equal operator
    Vec2& operator /= (float rhs)
    {
        x /= rhs;
        y /= rhs;
        return *this;
    }
    // overload is equal operator
    bool operator == (const Vec2& rhs) const
    {
        return x == rhs.x && y == rhs.y;
    }
    // overload not equal operator
    bool operator != (const Vec2& rhs) const
    {
        return !(x == rhs.x && y == rhs.y);
    }
    float Length() const
    {
        return sqrt(x * x + y * y);
    }

    Vec2 Normalise() const
    {
        float len = Length();

        if (len == 0)
            return Vec2(0, 0);
        return Vec2(x / len, y / len);
    }

    float Dot(const Vec2& rhs) const
    {
        return x * rhs.x + y * rhs.y;
    }

};