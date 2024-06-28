#include "pch.h"
#include "Level.h"

Level::Level()
{
	width = 4;
	height = 4;
	world = new int[width * height];

	for (int i = 0; i < width * height; i++)
	{
		world[i] = i % 2;
	}
}

Level::~Level()
{
	delete world;
}

void Level::OnUpdate(Timestep delta)
{
	
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			int tile = world[y * width + x];
			switch (tile)
			{
			case 0:

				break;
			case 1:

				break;
			default:
				LOG_CORE_ERROR("HOW IS THIS RUNNING???");
			}
		}

	}

}