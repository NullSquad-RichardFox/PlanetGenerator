#include "epch.h"
#include "Input.h"
#include "Core/Application.h"
#include "Core/Window.h"

#include "GLFW/glfw3.h"


void UInput::BindKeyEvent(FKey key, void* bindObj, std::function<void()> callback)
{
	GetApp()->GetWindow()->OnKeyInput.BindEvent(key, bindObj, callback);
}

void UInput::BindScrollEvent(void* bindObj, std::function<void(float)> callback)
{
	GetApp()->GetWindow()->OnScrollInput.BindEvent(bindObj, callback);
}

void UInput::BindMouseMoveEvent(void* bindObj, std::function<void(glm::vec2)> callback)
{
	GetApp()->GetWindow()->OnMouseMoved.BindEvent(bindObj, callback);
}

void UInput::BindRelativeMouseMoveEvent(void* bindObj, std::function<void(glm::vec2)> callback)
{
	GetApp()->GetWindow()->OnMouseOffset.BindEvent(bindObj, callback);
}

bool UInput::IsKeyPressed(FKey key)
{
	int keyVal = (int)(Keys::EKeyType)key;
	GLFWwindow* window = static_cast<GLFWwindow*>(GetApp()->GetWindow()->GetNativeWindow());

	if (keyVal >= 400)
	{
		int state = glfwGetMouseButton(window, keyVal - 400);
		return state == GLFW_PRESS;
	}
	else
	{
		int state = glfwGetKey(window, keyVal);
		return state == GLFW_PRESS;
	}
}

glm::vec2 UInput::GetMousePosition()
{
	GLFWwindow* window = static_cast<GLFWwindow*>(GetApp()->GetWindow()->GetNativeWindow());
	double xPos, yPos;
	glfwGetCursorPos(window, &xPos, &yPos);

	return { (float)xPos, (float)yPos };
}

float UInput::GetMouseX()
{
	GLFWwindow* window = static_cast<GLFWwindow*>(GetApp()->GetWindow()->GetNativeWindow());
	double xPos, yPos;
	glfwGetCursorPos(window, &xPos, &yPos);

	return (float)xPos;
}

float UInput::GetMouseY()
{
	GLFWwindow* window = static_cast<GLFWwindow*>(GetApp()->GetWindow()->GetNativeWindow());
	double xPos, yPos;
	glfwGetCursorPos(window, &xPos, &yPos);

	return (float)yPos;
}