#include "Assoc_pch.h"
#include "WindowsInput.h"
#include "Associates/Application.h"

#include <GLFW/glfw3.h>

namespace Associates
{
	Input* Input::s_Instance = new WindowsInput();

	bool WindowsInput::IsKeyPressedImpl(int KeyCode) 
	{
		auto Window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto State = glfwGetKey(Window, KeyCode);

		return State == GLFW_PRESS || State == GLFW_REPEAT;
	}

	bool WindowsInput::IsMouseButtonPressedImpl(int Button)
	{
		auto Window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto State = glfwGetMouseButton(Window, Button);

		return State == GLFW_PRESS;
	}

	float WindowsInput::GetMouseXImpl()
	{
		auto[x, y] = GetMousePositionImpl();
		return x;
	}

	float WindowsInput::GetMouseYImpl()
	{
		auto[x, y] = GetMousePositionImpl();
		return y;
	}

	std::pair<float, float> WindowsInput::GetMousePositionImpl()
	{
		auto Window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		double xPos, yPos;
		glfwGetCursorPos(Window, &xPos, &yPos);

		return { (float)xPos, (float)yPos };
	}
}
