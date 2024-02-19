#include "epch.h"
#include "Buffer.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"


// ------------------
//  !FBufferElement
// ------------------

FBufferElement::FBufferElement(EShaderDataType type, const std::string& name, bool bNormalized)
{
	Name = name;
	Type = type;
	Offset = 0;
	this->bNormalized = bNormalized;

	switch (Type)
	{
	case EShaderDataType::None:		Size = 0; break;
	case EShaderDataType::Float:	Size = 4; break;
	case EShaderDataType::Float2:	Size = 8; break;
	case EShaderDataType::Float3:	Size = 12; break;
	case EShaderDataType::Float4:	Size = 16; break;
	case EShaderDataType::Mat3:		Size = 36; break;
	case EShaderDataType::Mat4:		Size = 64; break;
	case EShaderDataType::Int:		Size = 4; break;
	case EShaderDataType::Int2:		Size = 8; break;
	case EShaderDataType::Int3:		Size = 12; break;
	case EShaderDataType::Int4:		Size = 16; break;
	case EShaderDataType::Bool:		Size = 1; break;
	}
}


// -----------------
//  !FBufferLayout
// -----------------


FBufferLayout::FBufferLayout()
{
	Stride = 0;
	Elements = {};
}

FBufferLayout::FBufferLayout(const std::initializer_list<FBufferElement>& elements)
{
	Elements = elements;
	Stride = 0;

	CalculateOffsetAndStride();
}

void FBufferLayout::CalculateOffsetAndStride()
{
	uint32_t offset = 0;
	for (auto& element : Elements)
	{
		element.Offset = offset;
		offset += element.Size;
		Stride += element.Size;
	}
}


// -----------------
//  !UVertexBuffer
// -----------------


UVertexBuffer::UVertexBuffer(uint32_t size)
{
	glCreateBuffers(1, &BufferID);
	glBindBuffer(GL_ARRAY_BUFFER, BufferID);
	glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
}

UVertexBuffer::UVertexBuffer(float* vertices, uint32_t size)
{
	glCreateBuffers(1, &BufferID);
	glBindBuffer(GL_ARRAY_BUFFER, BufferID);
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

UVertexBuffer::~UVertexBuffer()
{
	glDeleteBuffers(1, &BufferID);
}

void UVertexBuffer::Bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, BufferID);
}

void UVertexBuffer::Unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}


// ----------------
//  !UIndexBuffer
// ----------------


UIndexBuffer::UIndexBuffer(uint32_t* indices, uint32_t count)
{
	Count = count;

	glCreateBuffers(1, &BufferID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, BufferID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
}

UIndexBuffer::~UIndexBuffer()
{
	glDeleteBuffers(1, &BufferID);
}

void UIndexBuffer::Bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, BufferID);
}

void UIndexBuffer::Unbind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
