#ifndef _QUATERNION
#define _QUATERNION

#include <cmath>

class Quaternion {
public:
    float W;
    float X;
    float Y;
    float Z;

    Quaternion(float w, float x, float y, float z);
};

#endif
