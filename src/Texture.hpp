#ifndef _TEXTURE
#define _TEXTURE

#include "Color.hpp"

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include <SFML/Graphics/Image.hpp>

class Texture {
public:
    Texture(int width = 0, int height = 0, bool alpha = false);
    ~Texture();
    void SetSize(int width, int height);
    void SetAlpha(bool alpha);
    void Set(int x, int y, Color c);
    Color Get(int x, int y);
    void Generate(Color (*generator)(float, float));
    void Generate(Color (*generator)(int, int));
    void Load(const std::string& filename);
    GLubyte* GetImage();
    void Update();
    void Bind();
    GLuint GetTextureHandle() const;
private:
    void _ResetImage(bool set_color = false);
    GLubyte* mImage;
    GLuint mTextureHandle;
    int mWidth;
    int mHeight;
    bool mAlpha;
};

#endif
