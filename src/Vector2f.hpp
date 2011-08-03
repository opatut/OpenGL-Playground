#ifndef _VECTOR2F
#define _VECTOR2F

#include <cmath>

class Vector2f {
public:
    float X;
    float Y;

    Vector2f(float x, float y);
    float GetLenght() const;
    void Normalize();
};

#endif
