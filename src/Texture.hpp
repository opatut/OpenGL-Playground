#ifndef _TEXTURE
#define _TEXTURE

#include "Color.hpp"

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>

class Texture {
public:
    Texture(int width, int height, bool alpha = false);
    ~Texture();
    void Set(int x, int y, Color c);
    Color Get(int x, int y);
    void Generate(Color (*generator)(float, float));
    void Generate(Color (*generator)(int, int));
    GLubyte* GetImage();
    void Update();
    void Bind();
private:
    GLubyte* mImage;
    GLuint mTextureHandle;
    int mWidth;
    int mHeight;
    bool mAlpha;
};

#endif
