#include "Vertex.hpp"
#include <iostream>
Vertex::Vertex(Vector3f position, Vector2f texture_coord, Color color)
    : mPosition(position),
      mTextureCoord(texture_coord),
      mColor(color) {}

void Vertex::Set() {
    glTexCoord2f(mTextureCoord.X, mTextureCoord.Y);
    glColor4f(mColor.R / 255.f, mColor.G / 255.f, mColor.B / 255.f, mColor.A / 255.f);
    glVertex3f(mPosition.X, mPosition.Y, mPosition.Z);
}
