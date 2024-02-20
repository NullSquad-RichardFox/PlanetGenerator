#pragma once


class UVertexArray;

class URenderingCommand
{
public:
	// Initializes GLFW
	static void Initialize();

	// Initializes Glad
	static void InitializeContext(void* windowHandle);

	static bool ShouldWindowClose(void* windowHandle);

	// Enables color blending
	static void EnableBlending();

	// Enables rendering using the Z buffer
	static void EnableZDepth();

	// Clears the viewport
	static void Clear();

	// Sets background color
	static void SetClearColor(glm::vec4 inColor);

	static void DrawElements(const std::shared_ptr<UVertexArray>& vertexArray);

	// Sets the size of the viewport
	static void SetViewport(float width, float height);

	static void WireframeOn();
	static void WireframeOff();

};