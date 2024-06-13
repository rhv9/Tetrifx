#pragma once


class Game
{
public:
	static Game& Instance();

	Game();
	bool TryInit();
	void Start();
	void Loop();
	bool Iterate();

private:
	std::chrono::system_clock::time_point previousTime = std::chrono::system_clock::now();
	std::chrono::duration<double> delta;
	int fps = 0;
};

