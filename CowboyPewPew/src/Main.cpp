#include "pch.h"
#include "Game.h"

int main()
{
	Game::Instance();

	if (!Game::Instance().TryInit())
	{
		std::cerr << "Failed to initialize Game::TryInit()" << std::endl;
		return -1;
	}

	Game::Instance().Start();

}

