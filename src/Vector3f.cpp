#include "Vector3f.hpp"

Vector3f::Vector3f(float x, float y, float z) {
    X = x;
    Y = y;
    Z = z;
}

float Vector3f::GetLenght() const {
    return sqrt(X*X + Y*Y + Z*Z);
}

void Vector3f::Normalize() {
    float l = GetLenght();
    X /= l;
    Y /= l;
    Z /= l;
}
