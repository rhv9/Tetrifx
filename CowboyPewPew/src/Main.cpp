#include "pch.h"

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

void error_callback(int error, const char* description)
{
	fprintf(stderr, "GLFW Error: %s\n", description);
}

int main()
{
	std::cout << "It begins now!" << std::endl;
	if (!glfwInit())
	{
		return -1;
	}

	

	glfwSetErrorCallback(error_callback);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	GLFWwindow* window = glfwCreateWindow(800, 600, "Title", NULL, NULL);
	if (!window)
	{
		std::cerr << "Failed to initialize window!" << std::endl;
	}
	glfwMakeContextCurrent(window);

	gladLoadGL();

	while (!glfwWindowShouldClose(window))
	{
		// Keep running
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	
}