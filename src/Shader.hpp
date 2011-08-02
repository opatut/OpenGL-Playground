#ifndef _SHADER
#define _SHADER

#include "Util.hpp"

#include <GL/glew.h>

#include <iostream>
#include <string>

class Shader {
public:
    enum Type {
        TYPE_VERTEX,
        TYPE_FRAGMENT
    };

    Shader(Type type, const char* source, bool load_file = false);
    bool Compile() const;

    GLuint GetHandle() const;
    bool IsCompiled() const;

private:
    void _PrintLog() const;

    GLuint mShaderHandle;
    Type mType;
    std::string mSource;
};



#endif
