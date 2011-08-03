#include "Program.hpp"

Program::Program() {
    mProgramHandle = glCreateProgramObjectARB();
    mTextureUnit = 1;
}

void Program::AddShader(const Shader& shader) {
    // make sure the shader is compiled
    if(!shader.IsCompiled()) {
        if(!shader.Compile()) {
            std::cerr << "Failed to add shader: compilation failed" << std::endl;
            return;
        }
    }

    glAttachShader(mProgramHandle, shader.GetHandle());
}

bool Program::Link() {
    if(IsLinked())
        return true;

    glLinkProgramARB(mProgramHandle);
    _PrintLog();

    return IsLinked();
}

void Program::Activate() {
    if(!IsLinked()) {
        if(!Link()) {
            std::cerr << "Cannot activate program: linking failed" << std::endl;
            return;
        }
    }

    glUseProgramObjectARB(mProgramHandle);
}

void Program::Deactivate() {
    glUseProgram(0);
}

bool Program::IsLinked() const {
    int linked;
    glGetProgramiv(mProgramHandle, GL_LINK_STATUS, &linked);
    return linked == GL_TRUE;
}

void Program::SetTexture(Texture& texture, const char* name) {
    Activate();

    int location = glGetUniformLocationARB(mProgramHandle, name + '\0');
    if(location == -1) {
        std::cerr << "Could not locate texture " << name << " in shader program." << std::endl;
        exit(1);
    } else {
        std::cout << "Found texture " << name << " at location: " << location << std::endl;
        glActiveTextureARB(GL_TEXTURE0_ARB);
        texture.Bind();
        glUniform1i(location, 0);
        mTextureUnit++;
    }
}

void Program::SetFloat(float v, const char* name) {
    glUniform1f(glGetUniformLocationARB(mProgramHandle, name), v);
}

void Program::_PrintLog() {
    int infologLength = 0;
    int maxLength;

    glGetProgramiv(mProgramHandle, GL_INFO_LOG_LENGTH, &maxLength);
    char infoLog[maxLength];

    glGetProgramInfoLog(mProgramHandle, maxLength, &infologLength, infoLog);

    if (infologLength > 0) {
        std::cout << "GL Program: " << infoLog << std::endl;
    }
}
