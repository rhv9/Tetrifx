#include "pch.h"
#include "Game.h"
#include "Input/Input.h"
#include "WindowsWindow.h"


bool Input::IsKeyPressed(uint32_t keyCode)
{
    WindowsWindow* window = (WindowsWindow*)Game::Instance().GetWindow().get();
    int status = glfwGetKey(window->GetNativeWindow(), static_cast<int>(keyCode));
    return status == GLFW_PRESS || status == GLFW_REPEAT;
}

bool Input::IsMouseButtonPressed(uint32_t button)
{
    WindowsWindow* window = (WindowsWindow*)Game::Instance().GetWindow().get();
    int status = glfwGetMouseButton(window->GetNativeWindow(), button);
    return status == GLFW_PRESS;
}

float Input::GetMouseX()
{
    return GetMousePosition().x;
}

float Input::GetMouseY()
{
    return GetMousePosition().y;
}

glm::vec2 Input::GetMousePosition()
{
    WindowsWindow* window = (WindowsWindow*)Game::Instance().GetWindow().get();
    double xpos, ypos;
    glfwGetCursorPos(window->GetNativeWindow(), &xpos, &ypos);
    return { (float)xpos, (float)ypos };
}