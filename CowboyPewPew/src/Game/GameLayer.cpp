#include "pch.h"
#include "GameLayer.h"

#include "Graphics/Renderer.h"
#include "Graphics/SubTexture.h"

#include "Input/Input.h"

#include "Game/Level/Level.h"
#include "Game/SpriteCollection.h"

static glm::vec3 moveVec{ 0.0f };

static std::shared_ptr<Texture> spriteSheet;
static std::shared_ptr<SubTexture> grass;
static std::shared_ptr<SubTexture> sword;


static std::shared_ptr<Level> level;
GameLayer::GameLayer()
    : freeCameraController(1920.0f/1080.0f, 70.0f)
{
}

void GameLayer::OnBegin()
{
    spriteSheet = CreateRef<Texture>("assets/textures/spritesheet.png");
    grass = CreateRef<SubTexture>(spriteSheet, glm::vec2{ 0.0f, 1.0f }, glm::vec2{ 32.0f, 32.0f });
    sword = CreateRef<SubTexture>(spriteSheet, glm::vec2{ 0.0f, 0.0f }, glm::vec2{ 32.0f, 32.0f });

    level = std::make_shared<Level>();
    SpriteCollection::init();
}

void GameLayer::OnUpdate(Timestep delta)
{
    freeCameraController.OnUpdate(delta);

    Renderer::StartScene(freeCameraController.GetCamera().GetViewProjection());

    level->OnUpdate(delta, { freeCameraController.GetPosition(), 0.0f });

    Renderer::EndScene();
}

void GameLayer::OnRemove()
{

}