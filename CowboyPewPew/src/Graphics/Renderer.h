#pragma once
#include "Camera.h"

class Renderer
{
public:

	static void Init();

	static void StartScene(const Camera& camera);

	static void DrawQuad(const glm::vec3& position, const glm::vec2& scale = { 1.0f, 1.0f });

	static void EndScene();

};