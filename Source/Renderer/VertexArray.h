#pragma once

#include "Buffer.h"


class UVertexArray
{
public:
	UVertexArray();
	~UVertexArray();

	void Bind() const;
	void Unbind() const;

	void AddVertexBuffer(const std::shared_ptr<UVertexBuffer>& vertexBuffer);
	void SetIndexBuffer(const std::shared_ptr<UIndexBuffer>& indexBuffer);
	inline const std::shared_ptr<UIndexBuffer>& GetIndexBuffer() const { return IndexBuffer; }

private:
	std::shared_ptr<UIndexBuffer> IndexBuffer;
	std::shared_ptr<UVertexBuffer> VertexBuffer;

	uint32_t ArrayID;
};