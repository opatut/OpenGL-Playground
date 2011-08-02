#include "Shader.hpp"

Shader::Shader(Type type, const char* source, bool load_file) {
    if(type == TYPE_VERTEX && !GLEW_ARB_vertex_shader) {
        std::cerr << "Cannot create vertex shader: not supported by this GLEW version (" << GLEW_VERSION << ")" << std::endl;
        exit(1);
    }

    if(type == TYPE_FRAGMENT && !GLEW_ARB_fragment_shader) {
        std::cerr << "Cannot create fragment shader: not supported by this GLEW version (" << GLEW_VERSION << ")" << std::endl;
        exit(1);
    }

    mType = type;
    if(load_file) {
        mSource = util::LoadFile(source);
    } else {
        mSource = source;
    }

    mShaderHandle = glCreateShaderObjectARB( type == TYPE_VERTEX ? GL_VERTEX_SHADER_ARB : GL_FRAGMENT_SHADER_ARB );
}

bool Shader::Compile() const {
    // do not compile twice
    if(IsCompiled())
        return true;

    // set the source
    const char* source = mSource.c_str();
    glShaderSource(mShaderHandle, 1, &source, NULL);

    // compile the shader
    glCompileShader(mShaderHandle);

    // output Log
    _PrintLog();

    return IsCompiled();
}

GLuint Shader::GetHandle() const {
    return mShaderHandle;
}

bool Shader::IsCompiled() const {
    int compiled;
    glGetShaderiv(mShaderHandle, GL_COMPILE_STATUS, &compiled);
    return compiled== GL_TRUE;
}

void Shader::_PrintLog() const {
    int infologLength = 0;
    int maxLength;

    glGetShaderiv(mShaderHandle, GL_INFO_LOG_LENGTH, &maxLength);

    char infoLog[maxLength];

    glGetShaderInfoLog(mShaderHandle, maxLength, &infologLength, infoLog);

    if (infologLength > 0) {
        std::cout << "GL Shader: " << infoLog << std::endl;
    }
}
