#pragma once
#include <Core/Window.h>

#include "Graphics/Shader.h"
#include "Graphics/VertexArray.h"

class Game
{
public:
	static Game& Instance();

	Game();
	void Init();
	void Start();
	void Loop();
	bool Iterate();
	void Shutdown();

	std::unique_ptr<Window>& GetWindow() { return window; }

private:
	void OnWindowClose(WindowCloseEventArg arg);

private:
	std::chrono::system_clock::time_point previousTime = std::chrono::system_clock::now();
	std::chrono::duration<double> delta = std::chrono::system_clock::now() - std::chrono::system_clock::now(); // Change this hack by properly learning you lazy 
	int fps = 0;
	bool running = false;

	std::unique_ptr<Window> window;
	Ref<Shader> shader;
};

