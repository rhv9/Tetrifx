#include <pch.h>
#include "WindowsWindow.h"
#include "Events/Event.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

void glfwErrorCallbackFunction(int error_code, const char* description)
{
	LOG_CORE_CRITICAL("GLFW Error: {}", description);
}

WindowsWindow::WindowsWindow(const WindowProps& windowProps) : Data(KeyPressedEventHandler, KeyReleasedEventHandler, MouseButtonPressedEventHandler, MouseButtonReleasedEventHandler, MouseMoveEventHandler, WindowCloseEventHandler, WindowResizeEventHandler)
{
	Init(windowProps);
}

void WindowsWindow::Init(const WindowProps& windowProps)
{

	// Temporary
#ifdef EMSCRIPTEN
	std::cout << "EMSCRIPTEN mode!" << std::endl;
	glfwInitHint(GLFW_PLATFORM, GLFW_PLATFORM_EMSCRIPTEN);
#endif

	Data.Width = windowProps.Width;
	Data.Height = windowProps.Height;
	Data.Title = windowProps.Title;

	LOG_CORE_INFO("Creating Window: Width={} Height={} Title={}", Data.Width, Data.Height, Data.Title);

	glfwSetErrorCallback(glfwErrorCallbackFunction);

	int success = glfwInit();
	ASSERT(success, "Failed to initialize Windows window: glfwInit");
	
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	LOG_CORE_INFO("GLFW Version: {} | Platform: {}", glfwGetVersionString(), glfwGetPlatform());

	// Construct the window
	m_Window = glfwCreateWindow(Data.Width, Data.Height, Data.Title.c_str(), nullptr, nullptr);

	ASSERT(m_Window, "Failed to create GLFW window");

	glfwMakeContextCurrent(m_Window);

	glfwSetWindowUserPointer(m_Window, &Data);

	glfwSetFramebufferSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
		{
			glViewport(0, 0, width, height);
		});

	glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			WindowData* windowData = (WindowData*)glfwGetWindowUserPointer(window);
			switch (action)
			{
			case GLFW_PRESS:
			{
				KeyPressedEventArg keyPressedEventArg{ key, mods };
				windowData->KeyPressedEventHandler.Invoke(keyPressedEventArg);
				break;
			}
			case GLFW_RELEASE:
			{

				break;
			}
			case GLFW_REPEAT:
			{
				// TODO: Do not need it now
				break;
			}
			}
		});

	glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
		{
			WindowData* windowData = (WindowData*)glfwGetWindowUserPointer(window);
			switch (action)
			{
			case GLFW_PRESS:
			{
				MouseButtonPressedEventArg mouseButtonPressed{ button, mods };
				windowData->MouseButtonPressedEventHandler.Invoke(mouseButtonPressed);
			}
			case GLFW_RELEASE:
			{
				MouseButtonReleasedEventArg mouseButtonReleased{ button, mods };
				windowData->MouseButtonReleasedEventHandler.Invoke(mouseButtonReleased);
			}
			default:
				break;
			}
		});

	glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xpos, double ypos)
		{
			WindowData* windowData = (WindowData*)glfwGetWindowUserPointer(window);

			MouseMoveEventArg mouseMoveEventArg{ (float)xpos, (float)ypos };
			windowData->MouseMoveEventHandler.Invoke(mouseMoveEventArg);
		});

	glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
		{
			WindowData* windowData = (WindowData*)glfwGetWindowUserPointer(window);

			WindowCloseEventArg windowCloseEventArg;
			windowData->WindowCloseEventHandler.Invoke(windowCloseEventArg);
		});

	glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
		{
			WindowData* windowData = (WindowData*)glfwGetWindowUserPointer(window);

			WindowResizeEventArg windowResizeEventArg{ width, height };
			windowData->WindowResizeEventHandler.Invoke(windowResizeEventArg);
		});



	// TODO: This should not be here
	success = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	ASSERT(success, "Failed to initialize GLAD");
}

void WindowsWindow::OnUpdate()
{
	glfwPollEvents();
	glfwSwapBuffers(m_Window);
}


WindowsWindow::~WindowsWindow()
{
	glfwDestroyWindow(m_Window);
}

uint32_t WindowsWindow::GetWidth() const
{
	return Data.Width;
}

uint32_t WindowsWindow::GetHeight() const
{
	return Data.Height;
}

void WindowsWindow::Shutdown()
{
	glfwTerminate();
}

