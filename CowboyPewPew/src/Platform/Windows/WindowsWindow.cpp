#include <pch.h>
#include "WindowsWindow.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

void glfwErrorCallbackFunction(int error_code, const char* description)
{
	LOG_CORE_CRITICAL("GLFW Error: {}", description);
}

WindowsWindow::WindowsWindow(const WindowProps& windowProps)
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

	glfwSetFramebufferSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
		{
			glViewport(0, 0, width, height);
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

