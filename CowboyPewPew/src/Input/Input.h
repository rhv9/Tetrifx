#pragma once

#include <GLFW/glfw3.h>

namespace Input
{
	bool IsKeyPressed(uint32_t keyCode);
	bool IsMouseButtonPressed(uint32_t button);
	float GetMouseX();
	float GetMouseY();
	std::pair<float, float> GetMousePosition();
}