#include "Vector2f.hpp"

Vector2f::Vector2f(float x, float y) {
    X = x;
    Y = y;
}

float Vector2f::GetLenght() const {
    return sqrt(X*X + Y*Y);
}

void Vector2f::Normalize() {
    float l = GetLenght();
    X /= l;
    Y /= l;
}
