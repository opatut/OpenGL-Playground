#ifndef _UTIL
#define _UTIL

#include <GL/glew.h>

#include <fstream>
#include <iostream>

namespace util {

bool InitGlew();

template <typename T>
void Clamp(T& v, T min, T max) {
    if(v < min) v = min;
    if(v > max) v = max;
}

template <typename T>
void LinearScale(T& v, T old_min, T old_max, T min, T max) {
    T fac = (min - max) / (old_min - old_max);

    v = (v - old_min) * fac + min;
}

std::string LoadFile(const char *path);

} // namespace util

#endif
