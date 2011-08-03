#ifndef _MESH
#define _MESH

#include "Movable.hpp"
#include "Texture.hpp"
#include "Vertex.hpp"

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>

class Mesh : public Movable {
public:
    enum Mode {
        MODE_TRIANGLES,
        MODE_QUADS
    };

    Mesh(Texture& texture, Mode mode = MODE_TRIANGLES);
    void SetTexture(Texture& texture);

    void Render();

    void AddVertex(Vertex vertex);
    void AddVertex(Vector3f position, Vector2f tex_coord, Color color = Color::White);

private:
    Texture& mTexture;
    const Mode mMode;
    std::vector<Vertex> mVertices;

};

#endif
