#ifndef _VERTEX
#define _VERTEX

#include "Color.hpp"
#include "Vector2f.hpp"
#include "Vector3f.hpp"

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>

class Vertex {
public:
    Vertex(Vector3f position, Vector2f texture_coord, Color color);
    void Set();

private:
    Vector3f mPosition;
    Vector2f mTextureCoord;
    Color mColor;
};

#endif
