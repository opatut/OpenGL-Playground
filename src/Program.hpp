#ifndef _PROGRAM
#define _PROGRAM

#include "Shader.hpp"
#include "Texture.hpp"
#include "Util.hpp"


#include <GL/glew.h>

#include <iostream>
#include <string>

class Program {
public:
    Program();

    void AddShader(const Shader& shader);
    bool Link();

    void Activate();
    void Deactivate();

    bool IsLinked() const;

    void SetTexture(Texture& texture, const char* name);
    void SetFloat(float v, const char* name);

private:
    void _PrintLog();

    GLuint mProgramHandle;
    GLuint mTextureUnit;

};



#endif
