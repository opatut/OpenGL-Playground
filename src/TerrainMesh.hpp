#ifndef _TERRAINMESH
#define _TERRAINMESH

#include "Mesh.hpp"
#include "Util.hpp"

class TerrainMesh : public Mesh {
public:
    TerrainMesh(Texture& texture, int resolution = 1024, float size = 512.f, float height = 64.f, float tile = 1.0);
    void Generate(float (*generator)(float, float));

private:
    int mResoltion;
    float mSize;
    float mHeight;
    float mTile;
};

#endif
