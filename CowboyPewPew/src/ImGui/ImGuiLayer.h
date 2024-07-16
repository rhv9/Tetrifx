#pragma once
#include "Core/Layer.h"

class ImGuiLayer : public Layer
{
public:
	ImGuiLayer();

	virtual void OnBegin() override;
	virtual void OnUpdate(Timestep delta)override;
	virtual void OnRemove() override;

	void BeginRender();
	void EndRender();
};