#pragma once
#include "Core/Layer.h"

class GameLayer : public Layer
{
public:
	GameLayer() = default;

	virtual void OnBegin();
	virtual void OnUpdate(Timestep delta);


};