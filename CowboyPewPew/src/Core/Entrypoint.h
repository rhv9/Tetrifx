
#include "pch.h"
#include "Game.h"

int main()
{
	Game::Instance().Init();
	Game::Instance().PostInit();
	Game::Instance().Start();
}
