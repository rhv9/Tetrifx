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
#include <Events/Events.h>
#include "Input/InputCode.h"
#include "Input/Input.h"

#include "Graphics/VertexArray.h"
#include "Graphics/Renderer.h"
#include "Graphics/SubTexture.h"

// Define variables
unsigned int vbo, vao, ebo;

Game& Game::Instance()
{
	static Game instance;
	return instance;
}

Game::Game() 
    : camera(-400/20, 400/20, -300/20, 300/20 )
{
}

static glm::vec3 moveVec { 0.0f };

static std::shared_ptr<Texture> spriteSheet;
static std::shared_ptr<SubTexture> grass;
static std::shared_ptr<SubTexture> sword;

void Game::Init()
{
    Log::Init();

    window = std::make_unique<WindowsWindow>(WindowProps { 800 , 600, "Cowboy3i" });

    window->KeyPressedEventHandler += [](KeyPressedEventArg& arg)
        {
            if (arg.Key == Input::KEY_ESCAPE)
                Game::Instance().Shutdown();
            if (arg.Key == Input::KEY_V)
                Game::Instance().GetWindow()->SetVsync(!Game::Instance().GetWindow()->GetVsync());
        };
    window->WindowCloseEventHandler += std::bind(&Game::OnWindowClose, this, std::placeholders::_1);

    Renderer::Init();

    spriteSheet = CreateRef<Texture>("assets/textures/spritesheet.png");
    grass = CreateRef<SubTexture>(spriteSheet, glm::vec2 { 0.0f, 1.0f }, glm::vec2 { 32.0f, 32.0f });
    sword = CreateRef<SubTexture>(spriteSheet, glm::vec2{ 0.0f, 0.0f }, glm::vec2{ 32.0f, 32.0f });

    running = true;
}

void Game::Start()
{
    //emscripten_set_main_loop(this->Loop, 60, GLFW_FALSE);
    // This is the render loop
    while (running)
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

 
    if (!running)
        return false;

    // Calculate FPS logic
    {
        auto timeNow = std::chrono::system_clock::now();
        delta = ((std::chrono::duration<double>)(timeNow - previousTime)).count();
        deltaCummulative += timeNow - previousTime;
        previousTime = timeNow;

        if (deltaCummulative.count() >= 1.0f)
        {
            deltaCummulative--;
            LOG_CORE_INFO("FPS: {}", fps);
            fps = 0;
        }
        fps++;

    }

    //std::this_thread::sleep_for(std::chrono::seconds(1));

    glm::vec3 move{ 0.0f };
    if (Input::IsKeyPressed(Input::KEY_W))
        move.y += 1.0f;
    if (Input::IsKeyPressed(Input::KEY_S))
        move.y -= 1.0f;
    if (Input::IsKeyPressed(Input::KEY_A))
        move.x -= 1.0f;
    if (Input::IsKeyPressed(Input::KEY_D))
        move.x += 1.0f;

    moveVec += move * delta;

    camera.SetPosition({ 0.0f, 0.0f, 0.0f });
    Renderer::StartScene(camera.GetViewProjection());


    //Renderer::DrawQuad(moveVec, { 10.0f, 5.0f });
    //Renderer::DrawQuad({ 0.0f, 0.0f, 0.1f }, {5.0f, 5.0f});
    Renderer::DrawQuad(moveVec, sword, { 12.0f, 12.0f });
    Renderer::DrawQuad({ 0.0f, 0.0f, 0.0f }, grass, { 6.0f, 6.0f });

    Renderer::EndScene();

    window->OnUpdate();

    return true;
}

void Game::Shutdown()
{
    running = false;
}

void Game::OnWindowClose(WindowCloseEventArg arg)
{
    LOG_CORE_INFO("Window Closing...");
    Shutdown();
}
