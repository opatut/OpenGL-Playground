#ifndef _VECTOR3F
#define _VECTOR3F

#include <cmath>

class Vector3f {
public:
    float X;
    float Y;
    float Z;

    Vector3f(float x, float y, float z);
    float GetLenght() const;
    void Normalize();
};

#endif
