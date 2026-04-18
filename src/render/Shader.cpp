
#include <string>
#include <glad/glad.h>

#include "Shader.hh"


Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath) {
    std::string vertexSrc = loadShaderFile(vertexPath);
    std::string fragmentSrc = loadShaderFile(fragmentPath);

    const char* vertexStr = vertexSrc.c_str();
    const char* fragmentStr = fragmentSrc.c_str();


    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(vertexShader, 1, &vertexStr, nullptr);
    glShaderSource(fragmentShader, 1, &fragmentStr, nullptr);

    glCompileShader(vertexShader);
    glCompileShader(fragmentShader);

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    GLint success;
    char infoLog[512];
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        printf("ERRO NO LINK: %s\n", infoLog);
    } else {
        printf("Shader vinculado com sucesso!\n");
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    this->ID = shaderProgram;
}


void Shader::Activate() {
    glUseProgram(this->ID);
}

void Shader::Delete() {
    glDeleteProgram(ID);
}

std::string loadShaderFile(const std::string& path) {
    std::string fullPath = "resources/shaders/" + path;
    std::ifstream file(fullPath);
    
    if (!file.is_open()) {
        printf("ERRO FATAL: Nao foi possivel abrir o arquivo: %s\n", fullPath.c_str());
        throw(errno);
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    
    std::string result = buffer.str();
    printf("Arquivo carregado com sucesso (%d bytes): %s\n", (int)result.length(), fullPath.c_str());
    
    return result;
}