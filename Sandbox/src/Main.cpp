#include "pch.h"
#include "Game/GameLayer.h"
#include "Core/Layer.h"
#include "Core/LayerStack.h"
#include "Game.h"
#include "Core/Entrypoint.h"

void Game::PostInit()
{
    layerStack.PushLayer(new GameLayer());
}
