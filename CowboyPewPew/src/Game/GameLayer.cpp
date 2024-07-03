#include "pch.h"
#include "GameLayer.h"

#include "Graphics/Renderer.h"
#include "Graphics/SubTexture.h"

#include "Input/Input.h"

#include "Game/Level/Level.h"
#include "Game/SpriteCollection.h"

#include "entt.hpp"

static entt::registry registry;

static std::shared_ptr<Level> level;
GameLayer::GameLayer()
    : freeCameraController(1920.0f/1080.0f, 70.0f)
{
}

void GameLayer::OnBegin()
{
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