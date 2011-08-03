#include "Mesh.hpp"

#include <iostream>

Mesh::Mesh(Texture& texture, Mode mode)
    : mTexture(texture),
      mMode(mode) {}

void Mesh::SetTexture(Texture& texture) {
    mTexture = texture;
}

void Mesh::Render() {
    // set position, scale, rotation
    glLoadIdentity();
    glTranslatef(mPosition.X, mPosition.Y, mPosition.Z);
    glScalef(mScale.X, mScale.Y, mScale.Z);
    glRotatef(mRotation.W, mRotation.X, mRotation.Y, mRotation.Z);

    mTexture.Bind();
    glBegin(mMode == MODE_QUADS ? GL_QUADS : GL_TRIANGLES);
    for(std::vector<Vertex>::iterator i = mVertices.begin(); i != mVertices.end(); ++i) {
        i->Set();
    }
    glEnd();
}

void Mesh::AddVertex(Vertex vertex) {
    mVertices.push_back(vertex);
}

void Mesh::AddVertex(Vector3f position, Vector2f tex_coord, Color color) {
    mVertices.push_back(Vertex(position, tex_coord, color));
}
