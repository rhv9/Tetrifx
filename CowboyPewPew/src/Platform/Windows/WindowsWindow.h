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

		EventHandler<KeyPressedEventArg>& KeyPressedEventHandler;
		EventHandler<KeyReleasedEventArg>& KeyReleasedEventHandler;
		EventHandler<MouseButtonPressedEventArg>& MouseButtonPressedEventHandler;
		EventHandler<MouseButtonReleasedEventArg>& MouseButtonReleasedEventHandler;
		EventHandler<MouseMoveEventArg>& MouseMoveEventHandler;
		EventHandler<WindowCloseEventArg>& WindowCloseEventHandler;
		EventHandler<WindowResizeEventArg>& WindowResizeEventHandler;

		WindowData(EventHandler<KeyPressedEventArg>& keyPressedEventHandler,
			EventHandler<KeyReleasedEventArg>& keyReleasedEventHandler,
			EventHandler<MouseButtonPressedEventArg>& mouseButtonPressedEventHandler,
			EventHandler<MouseButtonReleasedEventArg>& mouseButtonReleasedEventHandler,
			EventHandler<MouseMoveEventArg>& mouseMoveEventHandler,
			EventHandler<WindowCloseEventArg>& windowCloseEventHandler,
			EventHandler<WindowResizeEventArg>& windowResizeEventHandler) 
				: KeyPressedEventHandler(keyPressedEventHandler),
				  KeyReleasedEventHandler(keyReleasedEventHandler),
				  MouseButtonPressedEventHandler(mouseButtonPressedEventHandler),
				  MouseButtonReleasedEventHandler(mouseButtonReleasedEventHandler),
				  MouseMoveEventHandler(mouseMoveEventHandler),
				  WindowCloseEventHandler(windowCloseEventHandler),
				  WindowResizeEventHandler(windowResizeEventHandler) {}
	};

	GLFWwindow* m_Window;
	WindowData Data;
};