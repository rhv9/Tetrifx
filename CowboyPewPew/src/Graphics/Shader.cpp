#include "pch.h"
#include "Shader.h"

#include "Core/Platform.h"


GLuint CreateShader(GLenum shaderType, const char* shaderSource)
{
    GLuint shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &shaderSource, NULL);
    glCompileShader(shader);
    // check for shader compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        std::string stringShaderType;
        switch (shaderType)
        {
        case GL_VERTEX_SHADER:
            stringShaderType = "Vertex";
            break;
        case GL_FRAGMENT_SHADER:
            stringShaderType = "Fragment";
            break;
        default:
            LOG_CORE_WARN("Shader Warning: Creating shaderType that is not expected.");
        }

        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        LOG_CORE_ERROR("Error: {} Shader failed to compile. Info Log: \n{}", stringShaderType, infoLog);
    }

    return shader;
}

Shader::Shader(const std::string& vertexSourcePath, const std::string& fragmentSourcePath)
{
    std::string vertexSource = Platform::File::ReadFileAsString(vertexSourcePath.c_str());
    std::string fragmentSource = Platform::File::ReadFileAsString(fragmentSourcePath.c_str());

    GLuint vertexShader = CreateShader(GL_VERTEX_SHADER, vertexSource.c_str());
    GLuint fragmentShader = CreateShader(GL_FRAGMENT_SHADER, fragmentSource.c_str());

    int success;
    char infoLog[512];
    // link shaders
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    // check for linking errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        LOG_CORE_ERROR("Error: Program failed to link with shaders: {} {}, Info Log: \n{}", vertexSourcePath, fragmentSourcePath, infoLog);
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    m_Program = shaderProgram;
}


void Shader::Use()
{
	glUseProgram(m_Program);
}

Shader::~Shader()
{
    glDeleteProgram(m_Program);
}

void Shader::UniformInt(const std::string& name, const int val) const
{
    int location = glGetUniformLocation(m_Program, name.c_str());
    glUniform1i(location, val);
}

void Shader::UniformIntArray(const std::string& name, int* values, uint32_t count) const
{
    int location = glGetUniformLocation(m_Program, name.c_str());
    glUniform1iv(location, count, values);
}

void Shader::UniformFloat(const std::string& name, const float val) const
{
    int location = glGetUniformLocation(m_Program, name.c_str());
    glUniform1f(location, val);
}

void Shader::UniformFloat2(const std::string& name, const glm::vec2& vector) const
{
    int location = glGetUniformLocation(m_Program, name.c_str());
    glUniform2f(location, vector.x, vector.y);
}

void Shader::UniformFloat3(const std::string& name, const glm::vec3& vector) const
{
    int location = glGetUniformLocation(m_Program, name.c_str());
    glUniform3f(location, vector.x, vector.y, vector.z);
}

void Shader::UniformFloat4(const std::string& name, const glm::vec4& vector) const
{
    int location = glGetUniformLocation(m_Program, name.c_str());
    glUniform4f(location, vector.x, vector.y, vector.z, vector.w);
}

void Shader::UniformMat3(const std::string& name, const glm::mat3& matrix) const
{
    int location = glGetUniformLocation(m_Program, name.c_str());
    glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}

void Shader::UniformMat4(const std::string& name, const glm::mat4& matrix) const
{
    int location = glGetUniformLocation(m_Program, name.c_str());
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}
