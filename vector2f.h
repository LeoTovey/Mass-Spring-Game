//
// Created by Leo on 2021/10/11.
//

#ifndef MASS_SPRING_GAME_VECTOR2F_H
#define MASS_SPRING_GAME_VECTOR2F_H

#include <math.h>
class Vector2f
{
public:

    Vector2f(){}

    Vector2f(float x_, float y_) : x(x_), y(y_){}

    Vector2f operator -() const{ Vector2f v(-x, -y); return v;}

    Vector2f operator *(const Vector2f& v) const
    {
        Vector2f ret(x * v.x, y * v.y);
        return ret;
    }

    Vector2f operator *(float f) const
    {
        Vector2f ret(x * f, y * f);
        return ret;
    }

    Vector2f operator -(const Vector2f& v) const
    {
        Vector2f ret(x - v.x, y - v.y);
        return ret;
    }

    Vector2f operator +(const Vector2f& v) const
    {
        Vector2f ret(x + v.x, y + v.y);
        return ret;
    }

    void operator += (const Vector2f& v)
    {
        x += v.x;
        y += v.y;
    }

    Vector2f operator -(float f) const
    {
        Vector2f ret(x - f, y - f);
        return ret;
    }

    float Length() const { return std::sqrt(x * x + y * y); }

    float LengthSquared() const { return x * x + y * y; }

    Vector2f Normalized() const
    {
        float invLength = 1 / Length();
        return {x * invLength, y * invLength};
    }

    void Normalize()
    {
        float invLength = 1 / Length();
        x *= invLength;
        y *= invLength;
    }

    float x,y;
};

inline float Dot(const Vector2f& a, const Vector2f& b)
{
    return a.x * b.x + a.y * b.y;
}

inline Vector2f operator *(float f, const Vector2f& v)
{
    return {f * v.x, f * v.y};
}
#endif //MASS_SPRING_GAME_VECTOR2F_H
