#include "epch.h"
#include "RenderingCommand.h"
#include "VertexArray.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"


void URenderingCommand::Initialize()
{
	glfwInit();
}

void URenderingCommand::InitializeContext(void* windowHandle)
{
	glfwMakeContextCurrent((GLFWwindow*)windowHandle);
	int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

	ASSERT(status, "Glad failed to load!");
}

bool URenderingCommand::ShouldWindowClose(void* windowHandle)
{
	return glfwWindowShouldClose((GLFWwindow*)windowHandle);
}

void URenderingCommand::EnableBlending()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void URenderingCommand::EnableZDepth()
{
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
}

void URenderingCommand::Clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void URenderingCommand::SetClearColor(glm::vec4 inColor)
{
	glClearColor(inColor.x, inColor.y, inColor.z, inColor.w);
}

void URenderingCommand::DrawElements(const std::shared_ptr<UVertexArray>& vertexArray)
{
	glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, 0);
}

void URenderingCommand::SetViewport(float width, float height)
{
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);
}

void URenderingCommand::WireframeOn()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void URenderingCommand::WireframeOff()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}
