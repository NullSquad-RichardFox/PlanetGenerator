#include "epch.h"
#include "VertexArray.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"


uint32_t GetShaderDataTypeComponentCount(EShaderDataType type)
{
	switch (type)
	{
	case EShaderDataType::None:		return 0;
	case EShaderDataType::Float:		return 1;
	case EShaderDataType::Float2:	return 2;
	case EShaderDataType::Float3:	return 3;
	case EShaderDataType::Float4:	return 4;
	case EShaderDataType::Mat3:		return 9;
	case EShaderDataType::Mat4:		return 16;
	case EShaderDataType::Int:		return 1;
	case EShaderDataType::Int2:		return 2;
	case EShaderDataType::Int3:		return 3;
	case EShaderDataType::Int4:		return 4;
	case EShaderDataType::Bool:		return 1;
	}

	ASSERT(false, "Unknown EShaderDataType");
	return 0;
}

GLenum GetShaderDataTypeToOpenGLBaseType(EShaderDataType type)
{
	switch (type)
	{
	case EShaderDataType::None:		return GL_FALSE;

	case EShaderDataType::Float:
	case EShaderDataType::Float2:
	case EShaderDataType::Float3:
	case EShaderDataType::Float4:
	case EShaderDataType::Mat3:
	case EShaderDataType::Mat4:		return GL_FLOAT;

	case EShaderDataType::Int:
	case EShaderDataType::Int2:
	case EShaderDataType::Int3:
	case EShaderDataType::Int4:      return GL_INT;

	case EShaderDataType::Bool:		return GL_INT;
	}

	ASSERT(false, "Unknown EShaderDataType");
	return 0;
}


// ------------------
//  !UVertexArray
// ------------------


UVertexArray::UVertexArray()
{
	glCreateVertexArrays(1, &ArrayID);
}

UVertexArray::~UVertexArray()
{
	glDeleteVertexArrays(1, &ArrayID);
}

void UVertexArray::Bind() const
{
	glBindVertexArray(ArrayID);

	if (IndexBuffer) IndexBuffer->Bind();
	if (VertexBuffer) VertexBuffer->Bind();
}

void UVertexArray::Unbind() const
{
	glBindVertexArray(0);

	if (IndexBuffer) IndexBuffer->Unbind();
	if (VertexBuffer) VertexBuffer->Unbind();
}

void UVertexArray::AddVertexBuffer(const std::shared_ptr<UVertexBuffer>& vertexBuffer)
{
	glBindVertexArray(ArrayID);
	vertexBuffer->Bind();

	ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Vertex Buffer has no layout!");

	uint32_t index = 0;
	for (auto& element : vertexBuffer->GetLayout())
	{
		glEnableVertexAttribArray(index);
		glVertexAttribPointer(
			index,
			GetShaderDataTypeComponentCount(element.Type),
			GetShaderDataTypeToOpenGLBaseType(element.Type),
			element.bNormalized ? GL_TRUE : GL_FALSE,
			vertexBuffer->GetLayout().GetStride(),
			(const void*)element.Offset
		);
		index++;
	}

	VertexBuffer = vertexBuffer;
}

void UVertexArray::SetIndexBuffer(const std::shared_ptr<UIndexBuffer>& indexBuffer)
{
	glBindVertexArray(ArrayID);
	indexBuffer->Bind();

	IndexBuffer = indexBuffer;
}
