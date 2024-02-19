#pragma once


class UCamera
{
public:
	UCamera(float aspectRatio, float zoomLevel);

	inline void SetZoomSpeed(float zoomSpeed) { ZoomSpeed = zoomSpeed; }
	inline void SetZoomLevel(float zoomLevel) { ZoomLevel = zoomLevel; RecalculateMatrices(); }
	inline void SetRotation(glm::vec3 rotation) { Rotation = rotation; RecalculateMatrices(); }
	inline void SetPosition(const glm::vec3& position) { Position = position; RecalculateMatrices(); }
	inline void SetPosition(glm::vec3&& position) { Position = std::move(position); RecalculateMatrices(); }

	inline float GetZoomSpeed() const { return ZoomSpeed; }
	inline float GetZoomLevel() const { return ZoomLevel; }
	inline glm::vec3 GetRotation() const { return Rotation; }
	inline const glm::vec3& GetPosition() const { return Position; }

	inline const glm::mat4& GetProjectionMatrix() const { return ProjectionMat; }
	inline const glm::mat4& GetViewMatrix() const { return ViewMat; }
	inline const glm::mat4& GetViewProjectionMatrix() const { return ViewProjectionMat; }

private:
	void OnWindowResized(glm::vec2 size);
	void OnMouseMoved(glm::vec2 offset);
	void OnMouseScroll(float amount);

	void RecalculateMatrices();

	glm::mat4 ProjectionMat;
	glm::mat4 ViewMat;
	glm::mat4 ViewProjectionMat;

	float AspectRatio;
	float ZoomLevel;
	float ZoomSpeed;
	float MouseSensitivity;

	glm::vec3 Rotation;
	glm::vec3 Position;
};