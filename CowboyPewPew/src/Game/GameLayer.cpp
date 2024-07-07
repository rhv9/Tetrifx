#include "pch.h"
#include "GameLayer.h"

#include "Graphics/Renderer.h"
#include "Graphics/SubTexture.h"

#include "Input/Input.h"

#include "Game/Level/Level.h"
#include "Game/SpriteCollection.h"

#include "entt.hpp"
#include "Scene/Components.h"

#include "Math/Math.h"

#include "Scene/EntityCameraController.h"
#include "Scene/FreeRoamEntityCameraController.h"

static entt::registry registry;
static entt::entity player;

static std::shared_ptr<Level> level;

GameLayer::GameLayer()
{

}

void GameLayer::OnBegin()
{

    level = std::make_shared<Level>();
    SpriteCollection::init();

    player = registry.create();

    cameraController = std::make_shared<FreeRoamEntityCameraController>(1920.0f / 1080.0f, 70.0f);
    ((FreeRoamEntityCameraController*)cameraController.get())->SetEntity(&registry, player);
    cameraController->SetZoomLevel(75);

    LOG_TRACE("Player entity validity: {}", registry.valid(player));
    LOG_TRACE("Player entity current: {}", entt::to_version(player));

    TransformComponent& tc = registry.emplace<TransformComponent>(player);
    tc.position.z = 0.2f;
    registry.emplace<VisualComponent>(player, SpriteCollection::player_head);

    for (int i = 0; i < 10; i++)
    {
        entt::entity entity = registry.create();
    
        registry.emplace<TransformComponent>(entity, glm::vec3 { Math::Random::linearInt(0, 16 * 10), Math::Random::linearInt(0, 16 * 10), 0.05f } );
        registry.emplace<VisualComponent>(entity, SpriteCollection::fire);

        
    }
}

void GameLayer::OnUpdate(Timestep delta)
{
    // Update Entities
    glm::vec3 moveVec{ 0.0f };
    float speed = 32.0f * 10;

    if (Input::IsKeyPressed(Input::KEY_UP))
        moveVec.y += speed;
    if (Input::IsKeyPressed(Input::KEY_DOWN))
        moveVec.y -= speed;
    if (Input::IsKeyPressed(Input::KEY_LEFT))
        moveVec.x -= speed;
    if (Input::IsKeyPressed(Input::KEY_RIGHT))
        moveVec.x += speed;

    TransformComponent& playerTransform = registry.get<TransformComponent>(player);
    playerTransform.position += moveVec * (float) delta;

    cameraController->OnUpdate(delta);

    // Render entities

    Renderer::StartScene(cameraController->GetCamera().GetViewProjection());

    level->OnUpdate(delta);

    // Rendering visual components
    auto view = registry.view<TransformComponent, VisualComponent>();

    for (entt::entity entity : view)
    {
       auto [transform, visual] = view.get(entity);
       Renderer::DrawQuad(transform.position + visual.localTransform, SpriteCollection::get(visual.spriteId), SpriteCollection::Tile_size);
    }

    Renderer::EndScene();
}

void GameLayer::OnRemove()
{

}