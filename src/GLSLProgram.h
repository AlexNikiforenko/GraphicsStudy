#ifndef GLSLPROGRAM_H
#define GLSLPROGRAM_H

#include <string>
#include "../include/glad/glad.h"

class GLSLProgram {
public:
    GLSLProgram();
    ~GLSLProgram();

    void compileShaders(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath);

    void linkShaders();

    void addAttribute(const std::string& attributeName);

    void use();
    void unuse();
private:
    void compileShader(const std::string& filePath, GLuint id);

    int m_numAttributes;

    GLuint m_programID;

    GLuint m_vertexShaderID;
    GLuint m_fragmentShaderID;
};

#endif