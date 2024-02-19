#pragma once

#include "Key.h"


class UInput
{
public:
	static void BindKeyEvent(FKey key, void* bindObj, std::function<void()> callback);
	static void BindScrollEvent(void* bindObj, std::function<void(float)> callback);
	static void BindMouseMoveEvent(void* bindObj, std::function<void(glm::vec2)> callback);
	static void BindRelativeMouseMoveEvent(void* bindObj, std::function<void(glm::vec2)> callback);

	static bool IsKeyPressed(FKey key);
	static glm::vec2 GetMousePosition();
	static float GetMouseX();
	static float GetMouseY();
};