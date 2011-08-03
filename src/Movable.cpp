#include "Movable.hpp"

Movable::Movable()
    : mPosition(Vector3f(0,0,0)),
      mRotation(Quaternion(0,0,1,0)),
      mScale(Vector3f(1,1,1)) {}

Movable::~Movable() {}

void Movable::SetPosition(Vector3f position) {
    mPosition = position;
}

void Movable::SetRotation(Quaternion rotation) {
    mRotation = rotation;
}

void Movable::SetScale(Vector3f scale) {
    mScale = scale;
}

Vector3f Movable::GetPosition() {
    return mPosition;
}

Quaternion Movable::GetRotation() {
    return mRotation;
}

Vector3f Movable::GetScale() {
    return mScale;
}
