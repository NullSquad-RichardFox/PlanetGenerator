#include "epch.h"
#include "Renderer3d.h"
#include "Shader.h"
#include "VertexArray.h"
#include "RenderingCommand.h"
#include "Object/Camera.h"
#include "Core/Application.h"
#include "Core/Window.h"


URenderer3D::URenderer3D()
{
	Shader.reset(new UShader("Assets/shaders/default3.glsl"));
	Camera.reset(new UCamera(GetApp()->GetWindow()->GetWidth() / GetApp()->GetWindow()->GetHeight(), 2.0f));

	//URenderingCommand::WireframeOn();

	Planet.GenerateSphereMesh(1.0f, 16, 16);
}

void URenderer3D::Render()
{
	URenderingCommand::Clear();
	URenderingCommand::SetClearColor(glm::vec4(0.1, 0.1, 0.1, 1.0));

	std::vector<float> vertices = {
		-0.5, -0.5, -0.5,
		-0.5, -0.5,  0.5,
		-0.5,  0.5, -0.5,
		-0.5,  0.5,  0.5,
		 0.5, -0.5, -0.5,
		 0.5, -0.5,  0.5,
		 0.5,  0.5, -0.5,
		 0.5,  0.5,  0.5
	};

	std::vector<uint32_t> indices = {
		0, 2, 4, 4, 6, 2,
		0, 1, 4, 4, 5, 1,
		2, 3, 0, 0, 1, 3,
		2, 3, 6, 6, 7, 3,
		6, 7, 4, 4, 5, 7,
		1, 3, 5, 5, 7, 3
	};

	FBufferLayout layout = {
		{ EShaderDataType::Float3, "aPosition" }
	};

	std::shared_ptr<UVertexArray> vArray = std::make_shared<UVertexArray>();
    std::shared_ptr<UVertexBuffer> vBuffer = std::make_shared<UVertexBuffer>(vertices.data(), sizeof(float) * (uint32_t)vertices.size());
    std::shared_ptr<UIndexBuffer> iBuffer = std::make_shared<UIndexBuffer>(indices.data(), (uint32_t)indices.size());

	vBuffer->SetLayout(layout);

	vArray->AddVertexBuffer(vBuffer);
	vArray->SetIndexBuffer(iBuffer);

	Shader->Bind();

	glm::mat4 viewProjMat = Camera->GetViewProjectionMatrix();

	Shader->SetMat4("uViewProjMat", viewProjMat);

	URenderingCommand::DrawElements(vArray);
}

void URenderer3D::RenderSphere()
{
    URenderingCommand::Clear();
    URenderingCommand::SetClearColor(glm::vec4(0.1, 0.1, 0.1, 1.0));

    std::shared_ptr<UVertexArray> vArray;
    std::shared_ptr<UVertexBuffer> vBuffer;
    std::shared_ptr<UIndexBuffer> iBuffer;

    vArray.reset(new UVertexArray());
    vBuffer.reset(new UVertexBuffer(Planet.GetVerticesData(), sizeof(float) * Planet.GetVerticesCount()));
    iBuffer.reset(new UIndexBuffer(Planet.GetIndicesData(), Planet.GetIndicesCount()));

    vBuffer->SetLayout(Planet.GetBufferLayout());

    vArray->AddVertexBuffer(vBuffer);
    vArray->SetIndexBuffer(iBuffer);

    Shader->Bind();

    glm::mat4 viewProjMat = Camera->GetViewProjectionMatrix();

    Shader->SetMat4("uViewProjMat", viewProjMat);

    URenderingCommand::DrawElements(vArray);
}

void URenderer3D::SetPlanetData(int rings, int segments)
{
	Planet.GenerateSphereMesh(1.0f, rings, segments);
}
