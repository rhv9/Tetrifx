#pragma once


struct TransformComponent
{
	glm::vec3 position;
	
	TransformComponent() = default;
	TransformComponent(const TransformComponent&) = default;
	TransformComponent(const glm::vec3& pos) : position(pos) {}
};

struct VisualComponent
{
	int spriteId;

	VisualComponent() = default;
	VisualComponent(const VisualComponent&) = default;
	VisualComponent(const int spriteId) : spriteId(spriteId) {}
};

