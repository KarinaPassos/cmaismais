#ifndef H_VECTOR2
#define H_VECTOR2

#include "numeric.h"

#include <iostream>
#include <cmath>

struct Vector2
{
    double dist2(const Vector2 &v) const
    {
        double dx = x - v.x;
        double dy = y - v.y;
        return dx * dx + dy * dy;
    }

    double dist(const Vector2 &v) const
    {
        return hypot(x - v.x, y - v.y);
    }

    double norm2() const
    {
        return x * x + y * y;
    }

    double x;
    double y;
};

#endif
