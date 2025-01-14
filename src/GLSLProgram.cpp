#include "GLSLProgram.h"
#include "Errors.h"
#include <fstream>
#include <vector>

GLSLProgram::GLSLProgram() : m_numAttributes(0), m_programID(0), m_vertexShaderID(0), m_fragmentShaderID(0) {

}

GLSLProgram::~GLSLProgram() {

}

void GLSLProgram::compileShaders(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath) {
    m_vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    if (m_vertexShaderID == 0) {
        fatalError("Vertex shader failed to be created!");
    }

    m_fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
    if (m_fragmentShaderID == 0) {
        fatalError("Fragment shader failed to be created!");
    }

    compileShader(vertexShaderFilePath, m_vertexShaderID);
    compileShader(fragmentShaderFilePath, m_fragmentShaderID);
}

void GLSLProgram::linkShaders() {
    m_programID = glCreateProgram();

    glAttachShader(m_programID, m_vertexShaderID);
    glAttachShader(m_programID, m_fragmentShaderID);

    glLinkProgram(m_programID);

    GLint isLinked = 0;
    glGetProgramiv(m_programID, GL_LINK_STATUS, (int*)&isLinked);
    if (isLinked == GL_FALSE) {
        GLint maxLength = 0;
        glGetProgramiv(m_programID, GL_INFO_LOG_LENGTH, &maxLength);

        std::vector<GLchar> errorLog(maxLength);
        glGetProgramInfoLog(m_programID, maxLength, &maxLength, &errorLog[0]);

        glDeleteProgram(m_programID);

        glDeleteShader(m_vertexShaderID);
        glDeleteShader(m_fragmentShaderID);

        std::printf("%s\n", &errorLog[0]);
        fatalError("Shader failed to link!");
    }
    glDetachShader(m_programID, m_vertexShaderID);
    glDetachShader(m_programID, m_fragmentShaderID);
    glDeleteShader(m_vertexShaderID);
    glDeleteShader(m_fragmentShaderID);
}

void GLSLProgram::addAttribute(const std::string& attributeName) {
    glBindAttribLocation(m_programID, m_numAttributes++, attributeName.c_str());
}

void GLSLProgram::use() {
    glUseProgram(m_programID);
    for (int i = 0; i < m_numAttributes; i++) {
        glEnableVertexAttribArray(i);
    }
}

void GLSLProgram::unuse() {
    glUseProgram(0);
    for (int i = 0; i < m_numAttributes; i++) {
        glDisableVertexAttribArray(i);
    }
}

void GLSLProgram::compileShader(const std::string& filePath, GLuint id) {
    std::ifstream vertexFile(filePath);
    if (vertexFile.fail()) {
        perror(filePath.c_str());
        fatalError("Failed to open " + filePath);
    }

    std::string fileContents = "";
    std::string line;

    while (std::getline(vertexFile, line)) {
        fileContents += line + "\n";
    }

    vertexFile.close();
    const char* contentsPtr = fileContents.c_str();
    glShaderSource(id, 1, &contentsPtr, nullptr);

    glCompileShader(id);

    GLint success = 0;
    glGetShaderiv(id, GL_COMPILE_STATUS, &success);
    if (success == GL_FALSE) {
        GLint maxLength = 0;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLength);

        // The maxLength includes the NULL character
        std::vector<GLchar> errorLog(maxLength);
        glGetShaderInfoLog(id, maxLength, &maxLength, &errorLog[0]);

        glDeleteShader(id);

        std::printf("%s\n", &errorLog[0]);
        fatalError("Shader " + filePath + " failed to compile!");
    }
}