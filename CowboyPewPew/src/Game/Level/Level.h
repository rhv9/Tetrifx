#pragma once

class Level
{
	Level();

	void OnUpdate(Timestep delta);

private:

	int* world;
	int width, height;

};