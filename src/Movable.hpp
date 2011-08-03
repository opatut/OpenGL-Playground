#ifndef _MOVABLE
#define _MOVABLE

#include "Vector3f.hpp"
#include "Quaternion.hpp"

class Movable {
public:
    Movable();
    virtual ~Movable() = 0;

    void SetPosition(Vector3f position);
    void SetRotation(Quaternion rotation);
    void SetScale(Vector3f scale);

    Vector3f GetPosition();
    Quaternion GetRotation();
    Vector3f GetScale();

protected:
    Vector3f mPosition;
    Quaternion mRotation;
    Vector3f mScale;
};

#endif
