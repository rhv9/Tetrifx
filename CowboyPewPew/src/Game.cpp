#include "pch.h"
#include "Game.h"


//#define EMSCRIPTEN

#ifdef EMSCRIPTEN
#include <GLES3/gl3.h>
#include <GLFW/emscripten_glfw3.h>
#include <emscripten/emscripten.h>

#else
#include <glad/glad.h>
#endif

#include <Platform/Windows/WindowsWindow.h>


// Define variables
unsigned int vbo, vao, ebo;
unsigned int shaderProgram;

GLuint CreateShader(GLenum shaderType, const char* shaderSource)
{
    unsigned int shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &shaderSource, NULL);
    glCompileShader(shader);
    // check for shader compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    return shader;
}

GLuint CreateShaderProgram(const char* vertexShaderSource, const char* fragmentShaderSource)
{
    unsigned int vertexShader = CreateShader(GL_VERTEX_SHADER, vertexShaderSource);
    // fragment shader
    unsigned int fragmentShader = CreateShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

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
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}



Game& Game::Instance()
{
	static Game instance;
	return instance;
}

Game::Game() 
{
}

void Game::Init()
{
    Log::Init();

    m_Window = std::make_unique<WindowsWindow>(WindowProps { 800 , 600, "Cowboy3i" });

    m_Running = true;
}

void Game::Start()
{

#ifndef EMSCRIPTEN
    const char* vertexShaderSource = "#version 330 core\n"
        "layout (location = 0) in vec2 aPos;\n"

        "void main()\n"
        "{\n"
        "   gl_Position = vec4(aPos.x, aPos.y, 0.0, 1.0);\n"
        "}\0";
    const char* fragmentShaderSource = "#version 330 core\n"
        "out vec4 FragColor;\n"
        "void main()\n"
        "{\n"
        "   FragColor = vec4(0.294f, 0.0f, 0.51f, 1.0f);\n"
        "}\n\0";

#else
    const char* vertexShaderSource = R"VST(#version 300 es
precision mediump float;

in vec2 vertexPosition;

void main () {
  gl_Position = vec4(vertexPosition, 0.0, 1.0);
})VST";

    const char* fragmentShaderSource = R"FST(#version 300 es
precision mediump float;

out vec4 triangleColor;

void main() {
  triangleColor = vec4(0.294, 0.0, 0.51, 1.0);
})FST";
#endif

    shaderProgram = CreateShaderProgram(vertexShaderSource, fragmentShaderSource);

    float vertices[] = {
         0.0f, 0.5f,
        -0.5f, -0.5f,
         0.5f, -0.5f,
    };

    unsigned int indices[] = {
        0, 1, 2
    };


    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 18, vertices, GL_STATIC_DRAW);

    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * 3, indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);




    //emscripten_set_main_loop(this->Loop, 60, GLFW_FALSE);

    // This is the render loop
    while (m_Running)
    {
        Iterate();
    }

}

void Game::Loop()
{
#ifdef EMSCRIPTEN
    if (!iter())
    {
        m_Window->Shutdown();
        emscripten_cancel_main_loop();
    }
#endif
}

bool Game::Iterate()
{
 
    if (!m_Running)
        return false;

    // Calculate FPS logic
    {
        auto timeNow = std::chrono::system_clock::now();
        m_Delta += timeNow - m_PreviousTime;
        m_PreviousTime = timeNow;

        if (m_Delta.count() >= 1.0f)
        {
            m_Delta--;
            LOG_CORE_INFO("FPS: {}", m_Fps);
            m_Fps = 0;
        }
        m_Fps++;

    }

    //std::this_thread::sleep_for(std::chrono::seconds(1));

    // Druids are the best
    glClearColor(1.00f, 0.49f, 0.04f, 1.00f);
    glClear(GL_COLOR_BUFFER_BIT);

    glBindVertexArray(vao);
    glUseProgram(shaderProgram);
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

    m_Window->OnUpdate();

    return true;
}
