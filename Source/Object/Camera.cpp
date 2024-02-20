#include "epch.h"
#include "Camera.h"
#include "Utility/Time.h"
#include "Input/Input.h"
#include "Core/Window.h"
#include "Core/Application.h"

#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/euler_angles.hpp"


UCamera::UCamera(float aspectRatio, float zoomLevel)
	:AspectRatio(aspectRatio), ZoomLevel(zoomLevel), ZoomSpeed(250.0f), MouseSensitivity(5.0f), Rotation(0.0f), Position(0.0f), ProjectionMat(1.0f), ViewMat(1.0f), ViewProjectionMat(1.0f)
{
	RecalculateMatrices();

	GetApp()->GetWindow()->OnWindowResized.BindEvent(this, BIND_FUNCTION(UCamera::OnWindowResized));
	UInput::BindScrollEvent(this, BIND_FUNCTION(UCamera::OnMouseScroll));
	UInput::BindRelativeMouseMoveEvent(this, BIND_FUNCTION(UCamera::OnMouseMoved));
}

void UCamera::OnWindowResized(glm::vec2 size)
{
	AspectRatio = size.x / size.y;
	RecalculateMatrices();
}

void UCamera::OnMouseMoved(glm::vec2 offset)
{
	// !TODO: fix higher speed at fullscreen

	if (UInput::IsKeyPressed(Keys::LeftMouseButton))
	{
		Rotation.x -= MouseSensitivity * offset.x * UTime::GetDeltaTime();
		Rotation.y -= MouseSensitivity * offset.y * UTime::GetDeltaTime();
		RecalculateMatrices();
	}
}

void UCamera::OnMouseScroll(float amount)
{
	ZoomLevel -= amount * ZoomSpeed * UTime::GetDeltaTime();
	RecalculateMatrices();
}

void UCamera::RecalculateMatrices()
{
	ProjectionMat = glm::ortho<float>(-AspectRatio * ZoomLevel, AspectRatio * ZoomLevel, -ZoomLevel, ZoomLevel, -1, 1);
	ViewMat = glm::inverse(glm::translate(glm::mat4(1.0f), Position) * glm::eulerAngleYXZ(Rotation.x, Rotation.y, Rotation.z)); //glm::rotate(glm::mat4(1.0f), Rotation, glm::vec3(0, 1, 0))

	ViewProjectionMat = ProjectionMat * ViewMat;
}
