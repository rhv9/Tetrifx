#pragma once

class Level
{
public:
	Level();
	~Level();

	void OnUpdate(Timestep delta, const glm::vec3& moveVec);

private:

	int* world;
	int width, height;

};