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
    auto [x, y] = GetMousePosition();
    return x;
}

float Input::GetMouseY()
{
    auto [x, y] = GetMousePosition();
    return y;
}

std::pair<float, float> Input::GetMousePosition()
{
    WindowsWindow* window = (WindowsWindow*)Game::Instance().GetWindow().get();
    double xpos, ypos;
    glfwGetCursorPos(window->GetNativeWindow(), &xpos, &ypos);
    return std::pair<float, float>((float)xpos, (float)ypos);
}