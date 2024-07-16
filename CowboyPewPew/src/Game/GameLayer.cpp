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

#include "Components/Collision.h"

static entt::registry registry;
static entt::entity player;

static std::shared_ptr<Level> level;

static Ref<Shader> collisionShader;

GameLayer::GameLayer() {}

void GameLayer::OnBegin()
{
    level = std::make_shared<Level>();
    SpriteCollection::init();

    collisionShader = CreateRef<Shader>("assets/shaders/TextureCoordReplaceColour.glsl");

    // camera
    cameraController = std::make_shared<FreeRoamEntityCameraController>(1920.0f / 1080.0f, 70.0f);
    ((FreeRoamEntityCameraController*)cameraController.get())->SetEntity(&registry, player);
    cameraController->SetZoomLevel(75);

    // Do entities
    player = registry.create();
    TransformComponent& tc = registry.emplace<TransformComponent>(player);
    tc.position.z = 0.2f;
    registry.emplace<VisualComponent>(player, SpriteCollection::player_head);
    registry.emplace<CollisionBox>(player, glm::vec3{ 0 }, glm::vec2{ 16.0f, 16.0f });

    for (int i = 0; i < 10; i++)
    {
        entt::entity entity = registry.create();
    
        registry.emplace<TransformComponent>(entity, glm::vec3 { Math::Random::linearInt(0, 16 * 10), Math::Random::linearInt(0, 16 * 10), 0.05f } );
        registry.emplace<VisualComponent>(entity, SpriteCollection::fire);
    }

    // Add collision shape

    {
        //entt::entity e1 = registry.create();
        //registry.emplace<TransformComponent>(e1, glm::vec3{ 24.0f, 24.0f, 0.4f });
        //registry.emplace<CollisionBox>(e1, glm::vec3{ 0 }, glm::vec2{ 16.0f, 16.0f });

        entt::entity e2 = registry.create();
        registry.emplace<TransformComponent>(e2, glm::vec3 { 32.0f, 32.0f, 0.4f });
        registry.emplace<CollisionBox>(e2, glm::vec3{ 0 }, glm::vec2{ 16.0f, 16.0f });

    }
}

void GameLayer::OnUpdate(Timestep delta)
{
    // Update Entities
    glm::vec3 moveVec{ 0.0f };
    float speed = 32.0f * 3;

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

    auto collisionView = registry.view<TransformComponent, CollisionBox>();

    for (entt::entity entity : collisionView)
    {
        auto [transform, collisionBox] = collisionView.get(entity);
        bool collided = false;

        for (entt::entity otherEntity : collisionView)
        {
            if (entity == otherEntity)
                continue;

            auto [e2Transform, e2Box] = collisionView.get(otherEntity);

            CollisionBox box1 = collisionBox;
            CollisionBox box2 = e2Box;

            box1.position += transform.position;
            box2.position += e2Transform.position;

            if (box1.CollidesWith(&box2))
                collided = true;

        }


        glm::vec3 globalPosition = transform.position + collisionBox.position;
        globalPosition.z = 0.4f;
        collisionShader->Use();
        collisionShader->UniformFloat4("uChangeCol", { 1, 0, 0, 1 });

        if (collided)
            collisionShader->UniformFloat4("uChangeColWith", { 0, 1, 0, 1 });
        else
            collisionShader->UniformFloat4("uChangeColWith", { 1, 0, 0, 1 });

        Renderer::DrawQuadCustomShader(collisionShader, globalPosition, SpriteCollection::squareTileTexture, collisionBox.size);
    }

    Renderer::EndScene();
}

void GameLayer::OnRemove()
{

}