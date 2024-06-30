#pragma once

#include "Events/Events.h"
#include "Graphics/Camera.h"

struct OrthographicCameraBounds
{
	float Left, Right;
	float Bottom, Top;

	float GetWidth() { return Right - Left; }
	float GetHeight() { return Top - Bottom; }
};

class FreeCameraController
{
public:
	FreeCameraController(const float aspectRatio, const float zoomLevel = 1.0f);

	void SetPosition(const glm::vec2& pos);

	void SetAspectRatio(const float aspectRatio) { this->aspectRatio = aspectRatio; CalculateView(); }
	void SetRotation(const float rotation) { this->rotation = rotation; CalculateView(); }
	void SetZoomLevel(const float zoomLevel) { this->zoomLevel = zoomLevel; CalculateView(); }

	void OnResize(uint32_t width, uint32_t height);

	const glm::vec2& GetPosition() const { return m_Position; }

	OrthographicCamera& GetCamera() { return camera; }

	void OnUpdate(Timestep ts);

	const OrthographicCameraBounds& GetBounds() const { return bounds; }
private:
	void CalculateView();

	void OnMousePressedCallback(MouseButtonPressedEventArg& e);
	void OnMouseReleasedCallback(MouseButtonReleasedEventArg& e);
	void OnMouseMoveCallback(MouseMoveEventArg& e);
	void OnMouseScrollCallback(MouseScrolledEventArg& e);
	void OnWindowResizeCallback(WindowResizeEventArg& e);


private:
	glm::vec2 m_Position = { 0.0f, 0.0f };
	float zoomLevel, aspectRatio;
	float rotation = 0.0f;
	float cameraSpeed = 1.0f, rotationSpeed = 360.0f;

	OrthographicCameraBounds bounds;
	OrthographicCamera camera;
};
