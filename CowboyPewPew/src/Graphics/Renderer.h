#pragma once

class Renderer
{
public:

	static void Init();

	static void StartScene(glm::mat4 camera);

	static void DrawQuad();

	static void EndScene();


};