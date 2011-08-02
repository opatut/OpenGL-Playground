#include "Texture.hpp"

Texture::Texture(int width, int height, bool alpha) {
    mWidth = width;
    mHeight = height;
    mAlpha = alpha;
    mImage = new GLubyte[ width * height * (mAlpha ? 4 : 3) ];

    glGenTextures(1, &mTextureHandle);
    Bind();
    Update();
}

Texture::~Texture() {
    glDeleteTextures(1, &mTextureHandle);
}

void Texture::Set(int x, int y, Color c) {
    if(mAlpha) {
        int i = (x * mWidth + y) * 4;
        mImage[i + 0] = c.R;
        mImage[i + 1] = c.G;
        mImage[i + 2] = c.B;
        mImage[i + 4] = c.A;
    } else {
        int i = (x * mWidth + y) * 3;
        mImage[i + 0] = c.R;
        mImage[i + 1] = c.G;
        mImage[i + 2] = c.B;
    }
}

Color Texture::Get(int x, int y) {
    if(mAlpha) {
        int i = (x * mWidth + y) * 3;
        return Color(mImage[i + 0],
                     mImage[i + 1],
                     mImage[i + 2],
                     mImage[i + 3]);
    } else {
        int i = (x * mWidth + y) * 3;
        return Color(mImage[i + 0],
                     mImage[i + 1],
                     mImage[i + 2]);
    }
}

void Texture::Generate(Color (*generator)(float, float)) {
    for(int x = 0; x < mWidth; ++x) {
        for(int y = 0; y < mHeight; ++y) {
            Set(x, y, generator(x * 1.f / mWidth, y * 1.f / mHeight));
        }
    }
    Update();
}

void Texture::Generate(Color (*generator)(int, int)) {
    for(int x = 0; x < mWidth; ++x) {
        for(int y = 0; y < mHeight; ++y) {
            Set(x, y, generator(x, y));
        }
    }
    Update();
}

GLubyte* Texture::GetImage() {
    return mImage;
}

void Texture::Update() {
    glTexImage2D(GL_TEXTURE_2D, 0,
            (mAlpha ? 4 : 3),
            mWidth, mHeight,
            0, (mAlpha ? GL_RGBA : GL_RGB),
            GL_UNSIGNED_BYTE, mImage);
}

void Texture::Bind() {
    glBindTexture(GL_TEXTURE_2D, mTextureHandle);
}
