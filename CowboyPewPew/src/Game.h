#pragma once
#include <Core/Window.h>

class Game
{
public:
	static Game& Instance();

	Game();
	void Init();
	void Start();
	void Loop();
	bool Iterate();

private:
	std::chrono::system_clock::time_point m_PreviousTime = std::chrono::system_clock::now();
	std::chrono::duration<double> m_Delta = std::chrono::system_clock::now() - std::chrono::system_clock::now(); // Change this hack by properly learning you lazy 
	int m_Fps = 0;
	bool m_Running = false;

	Scope<Window> m_Window;
};

