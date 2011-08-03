#include "Texture.hpp"

#include <iostream>

Texture::Texture(int width, int height, bool alpha) {
    mWidth = width;
    mHeight = height;
    mAlpha = alpha;

    _ResetImage(true);

    glGenTextures(1, &mTextureHandle);
    Bind();
    Update();

    glEnable(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
}

Texture::~Texture() {
    glDeleteTextures(1, &mTextureHandle);
}

void Texture::SetSize(int width, int height) {
    if(mWidth != width || mHeight != height) {
        mWidth = width;
        mHeight = height;
        _ResetImage(false);
    }
}

void Texture::SetAlpha(bool alpha) {
    if(mAlpha != alpha) {
        mAlpha = alpha;
        _ResetImage(false);
    }
}

void Texture::Set(int x, int y, Color c) {
    if(mAlpha) {
        int i = (y * mWidth + x) * 4;
        mImage[i + 0] = c.R;
        mImage[i + 1] = c.G;
        mImage[i + 2] = c.B;
        mImage[i + 3] = c.A;
    } else {
        int i = (y * mWidth + x) * 3;
        mImage[i + 0] = c.R;
        mImage[i + 1] = c.G;
        mImage[i + 2] = c.B;
    }
}

Color Texture::Get(int x, int y) {
    if(mAlpha) {
        int i = (y * mWidth + x) * 3;
        return Color(mImage[i + 0],
                     mImage[i + 1],
                     mImage[i + 2],
                     mImage[i + 3]);
    } else {
        int i = (y * mWidth + x) * 3;
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

void Texture::Load(const std::string& filename) {
    sf::Image img;
    img.LoadFromFile(filename);
    mAlpha = true;
    mWidth = img.GetWidth();
    mHeight = img.GetHeight();
    // copy image
    _ResetImage(false);

    for(int x = 0; x < mWidth; ++x) {
        for(int y = 0; y < mHeight; ++y) {
            sf::Color c = img.GetPixel(x, y);
            Set(x, y, Color(c.r, c.g, c.b, c.a));
        }
    }
    Update();
}

GLubyte* Texture::GetImage() {
    return mImage;
}

void Texture::Update() {
    Bind();
    glTexImage2D(GL_TEXTURE_2D, 0,
            (mAlpha ? 4 : 3),
            mWidth, mHeight,
            0, (mAlpha ? GL_RGBA : GL_RGB),
            GL_UNSIGNED_BYTE, mImage);
}

void Texture::Bind() {
    glBindTexture(GL_TEXTURE_2D, mTextureHandle);
}

GLuint Texture::GetTextureHandle() const {
    return mTextureHandle;
}

void Texture::_ResetImage(bool set_color) {
    mImage = new GLubyte[ mWidth * mHeight * (mAlpha ? 4 : 3) ];

    if(set_color) {
        for(int i = 0; i < mWidth * mHeight * (mAlpha ? 4 : 3); ++i) {
            mImage[i] = 255;
        }
    }
}
