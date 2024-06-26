#pragma once
#include "Core/Layer.h"
#include "Graphics/Camera.h"

class GameLayer : public Layer
{
public:
	GameLayer();

	virtual void OnBegin();
	virtual void OnUpdate(Timestep delta);
	virtual void OnRemove();

private:
	OrthographicCamera camera;
};