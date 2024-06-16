#pragma once
#include <Core/Window.h>

struct GLFWwindow {};

class WindowsWindow : public Window
{
public:
	virtual ~WindowsWindow();

	WindowsWindow(const WindowProps& windowProps);

	virtual void Shutdown();

	virtual void OnUpdate();

	virtual uint32_t GetWidth() const;
	virtual uint32_t GetHeight() const;

private:
	void Init(const WindowProps& windowProps);

private:
	struct WindowData
	{
		uint32_t Width, Height;
		std::string Title;

		Window* WindowObj;

		WindowData(Window* window) : WindowObj(window) {}
	};

	GLFWwindow* m_Window;
	WindowData Data;
};