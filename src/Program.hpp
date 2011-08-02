#ifndef _PROGRAM
#define _PROGRAM

#include "Shader.hpp"
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

private:
    void _PrintLog();

    GLuint mProgramHandle;

};



#endif
