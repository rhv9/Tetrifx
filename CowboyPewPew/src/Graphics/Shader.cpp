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


Ref<Shader> Shader::CreateFromFile(const std::string& vertexSourcePath, const std::string& fragmentSourcePath)
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

    return CreateRef<Shader>(shaderProgram);
}


void Shader::Use()
{
	glUseProgram(m_Program);
}

Shader::~Shader()
{
    glDeleteProgram(m_Program);
}