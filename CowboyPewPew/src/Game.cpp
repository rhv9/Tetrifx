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
    m_Shader = Shader::CreateFromFile("assets/shaders/vertex.glsl", "assets/shaders/fragment.glsl");

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
    m_Shader->Use();
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

    m_Window->OnUpdate();

    return true;
}
