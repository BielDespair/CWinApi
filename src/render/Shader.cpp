

#include "Shader.hh"
#include <glm/gtc/type_ptr.hpp>


Shader::Shader(const std::string &vertexPath, const std::string &fragmentPath, bool hasTexture)
{
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


    if (hasTexture) {
        this->Activate();
        this->useTextureID = glGetUniformLocation(ID, "useTexture");
        glUniform1i(useTextureID, GL_FALSE);
    }
    else {
        this->useTextureID = 0;
    }
}

void Shader::Activate() {
    glUseProgram(this->ID);
}

void Shader::SetMat4(GLuint id, const glm::mat4 &m) {
    glUniformMatrix4fv(id, 1, GL_FALSE, glm::value_ptr(m));
}

void Shader::SetVec3(GLuint id, const Vec3 &v) {
    glUniform3f(id, v.x, v.y, v.z);
}

void Shader::SetInt(GLuint id, int v) {

}

void Shader::SetBool(GLuint id, bool v) {
    glUniform1i(id, (int)v);
}

void Shader::texUnit(const char* uniform, GLuint unit) {
    GLuint texUni = glGetUniformLocation(this->ID, uniform);
    this->Activate();
    glUniform1i(texUni, unit);
}
void Shader::EnableTextures() {
    // Textures already enabled
    if (texturesEnabled) return;
    glUniform1i(useTextureID, GL_TRUE);
    texturesEnabled = true;
}

void Shader::DisableTextures() {
    // Textures already disabled
    if (!texturesEnabled) return;
    glUniform1i(useTextureID, GL_FALSE);
    texturesEnabled = false;
}

void Shader::Delete() {
    glDeleteProgram(ID);
}

std::string loadShaderFile(const std::string& path) {
    std::string fullPath = "assets/shaders/" + path;
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