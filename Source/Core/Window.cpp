#include "epch.h"
#include "Window.h"
#include "Application.h"
#include "Renderer/RenderingCommand.h"

#include "GLFW/glfw3.h"


UWindow::UWindow(const FWindowProps& props)
{
	Data.Width = (int)props.Width;
	Data.Height = (int)props.Height;
	Data.bRunning = true;
	Data.EventHandle = BIND_FUNCTION(UWindow::ProcessEvent);

	WindowHandle.reset(glfwCreateWindow(Data.Width, Data.Height, props.Title.c_str(), nullptr, nullptr));

	URenderingCommand::InitializeContext(WindowHandle.get());
	URenderingCommand::EnableBlending();
	URenderingCommand::EnableZDepth();

	glfwSetWindowUserPointer(WindowHandle.get(), &Data);

	// Window events
	glfwSetWindowCloseCallback(WindowHandle.get(), [](GLFWwindow* window) {
		FWindowData* data = (FWindowData*)glfwGetWindowUserPointer(window);

		data->bRunning = false;
		GetApp()->WindowClosed();

		// Destroys glfw window
		glfwDestroyWindow(window); 
	});

	glfwSetWindowSizeCallback(WindowHandle.get(), [](GLFWwindow* window, int width, int height) {
		FWindowData* data = (FWindowData*)glfwGetWindowUserPointer(window);

		data->Width = width;
		data->Height = height;

		FWindowResizeEvent e = FWindowResizeEvent((float)width, (float)height);
		data->EventHandle(e);

		URenderingCommand::SetViewport((float)width, (float)height);
	});


	// Key input
	glfwSetKeyCallback(WindowHandle.get(), [](GLFWwindow* window, int key, int scancode, int action, int mods) {
		FWindowData* data = (FWindowData*)glfwGetWindowUserPointer(window);

		FKeyWindowEvent e = FKeyWindowEvent(Keys::EKeyType(key), ETriggerEvent(action), FModifierKeys(mods));
		data->EventHandle(e);
	});

	glfwSetMouseButtonCallback(WindowHandle.get(), [](GLFWwindow* window, int button, int action, int mods) {
		FWindowData* data = (FWindowData*)glfwGetWindowUserPointer(window);

		// offset for mouse buttons is 400
		FKeyWindowEvent e = FKeyWindowEvent(Keys::EKeyType(button + 400), ETriggerEvent(action), FModifierKeys(mods));
		data->EventHandle(e);
	});


	// Typing input
	glfwSetCharCallback(WindowHandle.get(), [](GLFWwindow* window, unsigned int codepoint) {
		FWindowData* data = (FWindowData*)glfwGetWindowUserPointer(window);
	});


	// Mouse movement
	glfwSetCursorPosCallback(WindowHandle.get(), [](GLFWwindow* window, double xpos, double ypos) {
		FWindowData* data = (FWindowData*)glfwGetWindowUserPointer(window);

		data->CursorOffsetX = xpos - data->CursorPosX;
		data->CursorOffsetY = ypos - data->CursorPosY;

		data->CursorPosX = xpos;
		data->CursorPosY = ypos;

		FMouseMovedWindowEvent e = FMouseMovedWindowEvent();
		data->EventHandle(e);
	});


	// Scrolling input
	glfwSetScrollCallback(WindowHandle.get(), [](GLFWwindow* window, double xoffset, double yoffset) {
		FWindowData* data = (FWindowData*)glfwGetWindowUserPointer(window);
	
		FScrollWindowEvent e = FScrollWindowEvent((float)yoffset);
		data->EventHandle(e);
	});
}

void UWindow::OnUpdate(float deltaTime)
{
	glfwPollEvents();
	glfwSwapBuffers(WindowHandle.get());

	for (const auto& [type, key] : PressedKeys)
		OnKeyInput.Broadcast(key);
}

void UWindow::ProcessEvent(FWindowEvent& e)
{
	switch (e.GetType())
	{
	case EWindowEventType::KeyInput:
	{
		FKeyWindowEvent& keyEvent = static_cast<FKeyWindowEvent&>(e);
		bool bIsPresent = false;
		for (const auto& [uuid, event] : OnKeyInput.GetBoundEvents())
		{
			if (event.Comparison._Myfirst._Val == keyEvent.Key)
			{
				bIsPresent = true;
				break;
			}
		}

		if (!bIsPresent) break;

		if (keyEvent.Key.GetTriggerEvent() == ETriggerEvent::Pressed)
		{
			PressedKeys.emplace(keyEvent.Key, keyEvent.Key);
			OnKeyInput.Broadcast(keyEvent.Key);
		}
		else if (keyEvent.Key.GetTriggerEvent() == ETriggerEvent::Released)
		{
			PressedKeys.erase((Keys::EKeyType)keyEvent.Key);
			OnKeyInput.Broadcast(keyEvent.Key);
		}
	}
	break;

	case EWindowEventType::MouseMoved:
	{
		FMouseMovedWindowEvent& mouseEvent = static_cast<FMouseMovedWindowEvent&>(e);
		OnMouseMoved.Broadcast(glm::vec2(Data.CursorPosX, Data.CursorPosY));
		OnMouseOffset.Broadcast(glm::vec2(Data.CursorOffsetX, Data.CursorOffsetY));
	}
	break;

	case EWindowEventType::Scroll:
	{
		FScrollWindowEvent& scrollEvent = static_cast<FScrollWindowEvent&>(e);
		OnScrollInput.Broadcast(scrollEvent.value);
	}
	break;

	case EWindowEventType::Resize:
	{
		FWindowResizeEvent& resizeEvent = static_cast<FWindowResizeEvent&>(e);
		OnWindowResized.Broadcast(resizeEvent.Pos);
	}
	break;
	}
}
