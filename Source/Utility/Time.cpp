#include "epch.h"
#include "Time.h"

#include "GLFW/glfw3.h"


float UTime::sDeltaTime = 0;

UTime::UTime()
{
	TimeLastFrame = (float)glfwGetTime();
}

void UTime::OnUpdate()
{
	float currTime = (float)glfwGetTime();
	sDeltaTime = currTime - TimeLastFrame;
	TimeLastFrame = currTime;
}

double UTime::GetTime()
{
	return glfwGetTime();
}