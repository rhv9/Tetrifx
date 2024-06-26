#include "pch.h"
#include "GameLayer.h"

#include "Graphics/Renderer.h"
#include "Graphics/SubTexture.h"

#include "Input/Input.h"


static glm::vec3 moveVec{ 0.0f };

static std::shared_ptr<Texture> spriteSheet;
static std::shared_ptr<SubTexture> grass;
static std::shared_ptr<SubTexture> sword;


GameLayer::GameLayer()
    : camera(-400 / 20, 400 / 20, -300 / 20, 300 / 20)
{
}

void GameLayer::OnBegin()
{
    spriteSheet = CreateRef<Texture>("assets/textures/spritesheet.png");
    grass = CreateRef<SubTexture>(spriteSheet, glm::vec2{ 0.0f, 1.0f }, glm::vec2{ 32.0f, 32.0f });
    sword = CreateRef<SubTexture>(spriteSheet, glm::vec2{ 0.0f, 0.0f }, glm::vec2{ 32.0f, 32.0f });
}

void GameLayer::OnUpdate(Timestep delta)
{
    glm::vec3 move{ 0.0f };
    if (Input::IsKeyPressed(Input::KEY_W))
        move.y += 1.0f;
    if (Input::IsKeyPressed(Input::KEY_S))
        move.y -= 1.0f;
    if (Input::IsKeyPressed(Input::KEY_A))
        move.x -= 1.0f;
    if (Input::IsKeyPressed(Input::KEY_D))
        move.x += 1.0f;

    moveVec += move * (float)delta;

    camera.SetPosition({ 0.0f, 0.0f, 0.0f });
    Renderer::StartScene(camera.GetViewProjection());

    //Renderer::DrawQuad(moveVec, { 10.0f, 5.0f });
    //Renderer::DrawQuad({ 0.0f, 0.0f, 0.1f }, {5.0f, 5.0f});
    Renderer::DrawQuad(moveVec, sword, { 12.0f, 12.0f });
    Renderer::DrawQuad({ 0.0f, 0.0f, 0.0f }, grass, { 6.0f, 6.0f });

    Renderer::EndScene();
}

void GameLayer::OnRemove()
{

}