#include "TerrainMesh.hpp"

TerrainMesh::TerrainMesh(Texture& texture, int resolution, float size, float height, float tile)
    : Mesh(texture, Mesh::MODE_QUADS),
      mResoltion(resolution),
      mSize(size),
      mHeight(height),
      mTile(tile) {}

void TerrainMesh::Generate(float (*generator)(float, float)) {
    for(int x = 0; x < mResoltion; ++x) {
        for(int y = 0; y < mResoltion; ++y) {
            float x1 = (x + 0) * 1.f / mResoltion; // lower x of quad
            float x2 = (x + 1) * 1.f / mResoltion; // upper x of quad
            float y1 = (y + 0) * 1.f / mResoltion; // lower y of quad
            float y2 = (y + 1) * 1.f / mResoltion; // upper y of quad

            float tx1 = util::mod(x1 * mTile, 1.f);
            float tx2 = tx1 + mTile * 1.f / mResoltion;
            float ty1 = util::mod(y1 * mTile, 1.f);
            float ty2 = ty1 + mTile * 1.f / mResoltion;

            AddVertex(Vector3f((x1 - 0.5) * mSize, mHeight * generator(x1, y1), -(y1 - 0.5) * mSize), Vector2f(tx1, ty1));
            AddVertex(Vector3f((x2 - 0.5) * mSize, mHeight * generator(x2, y1), -(y1 - 0.5) * mSize), Vector2f(tx2, ty1));
            AddVertex(Vector3f((x2 - 0.5) * mSize, mHeight * generator(x2, y2), -(y2 - 0.5) * mSize), Vector2f(tx2, ty2));
            AddVertex(Vector3f((x1 - 0.5) * mSize, mHeight * generator(x1, y2), -(y2 - 0.5) * mSize), Vector2f(tx1, ty2));
        }
    }
}
