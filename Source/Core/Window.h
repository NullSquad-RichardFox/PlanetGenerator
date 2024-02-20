#pragma once

#include "Utility/Event.h"
#include "Input/Key.h"


struct GLFWwindow;

struct FWindowProps
{
	float Width;
	float Height;
	std::string Title;
};

DECLARE_EVENT_DELEGATE_OneParam(KeyInputEvent, FKey);
DECLARE_EVENT_DELEGATE_OneRet(MouseMovedEvent, glm::vec2);
DECLARE_EVENT_DELEGATE_OneRet(MouseOffsetEvent, glm::vec2);
DECLARE_EVENT_DELEGATE_OneRet(ScrollInputEvent, float);

DECLARE_EVENT_DELEGATE_OneRet(WindowResizeEvent, glm::vec2);

class UWindow
{
public:
	UWindow(const FWindowProps& props);

	void OnUpdate(float deltaTime);

	// Returns GLFW window pointer
	inline void* GetNativeWindow() const { return WindowHandle.get(); }

	// Returns true if the window is still opened
	inline bool IsRunning() const { return Data.bRunning; }

	inline int GetWidth() const { return Data.Width; }
	inline int GetHeight() const { return Data.Height; }

	// Activates if a key or mouse button has been pressed
	DKeyInputEventHandle OnKeyInput;
	DMouseMovedEventHandle OnMouseMoved;
	DMouseOffsetEventHandle OnMouseOffset;
	DScrollInputEventHandle OnScrollInput;

	DWindowResizeEventHandle OnWindowResized;

private:
	enum class EWindowEventType
	{
		KeyInput,
		MouseMoved,
		Scroll,
		Resize
	};

	// Events
	class FWindowEvent
	{
	public:
		virtual EWindowEventType GetType() const = 0;
	};
	class FKeyWindowEvent : public FWindowEvent
	{
	public:
		FKeyWindowEvent(Keys::EKeyType key, ETriggerEvent triggerEvent, FModifierKeys modKeys)
			:Key(key, triggerEvent, modKeys) {}

		static EWindowEventType GetStaticType() { return EWindowEventType::KeyInput; }
		virtual EWindowEventType GetType() const override { return GetStaticType(); }

		FKey Key;
	};
	class FScrollWindowEvent : public FWindowEvent
	{
	public:
		FScrollWindowEvent(float value)
			:value(value) {}

		static EWindowEventType GetStaticType() { return EWindowEventType::Scroll; }
		virtual EWindowEventType GetType() const override { return GetStaticType(); }

		float value;
	};
	class FMouseMovedWindowEvent : public FWindowEvent
	{
	public:
		FMouseMovedWindowEvent()
			{}

		static EWindowEventType GetStaticType() { return EWindowEventType::MouseMoved; }
		virtual EWindowEventType GetType() const override { return GetStaticType(); }
	};
	class FWindowResizeEvent : public FWindowEvent
	{
	public:
		FWindowResizeEvent(float xPos, float yPos)
			:Pos(xPos, yPos) {}

		static EWindowEventType GetStaticType() { return EWindowEventType::Resize; }
		virtual EWindowEventType GetType() const override { return GetStaticType(); }

		glm::vec2 Pos;
	};

	struct FWindowData
	{
		int Width;
		int Height;

		double CursorPosX;
		double CursorPosY;

		double CursorOffsetX;
		double CursorOffsetY;

		bool bRunning;

		std::function<void(FWindowEvent&)> EventHandle;
	};

private:
	void ProcessEvent(FWindowEvent& e);

	std::unordered_map<Keys::EKeyType, FKey> PressedKeys;
	std::shared_ptr<GLFWwindow> WindowHandle;
	FWindowData Data;
};