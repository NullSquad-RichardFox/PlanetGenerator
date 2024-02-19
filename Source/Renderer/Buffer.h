#pragma once


enum class EShaderDataType
{
	None,
	Float,
	Float2,
	Float3,
	Float4,
	Mat3,
	Mat4,
	Int,
	Int2,
	Int3,
	Int4,
	Bool
};

struct FBufferElement
{
	std::string Name;
	EShaderDataType Type;
	uint32_t Size;
	uint32_t Offset;
	bool bNormalized;

	FBufferElement(EShaderDataType type, const std::string& name, bool bNormalized = false);
};

struct FBufferLayout
{
public:
	FBufferLayout();
	FBufferLayout(const std::initializer_list<FBufferElement>& elements);

	inline const std::vector<FBufferElement>& GetElements() const { return Elements; }
	inline const uint32_t GetStride() const { return Stride; }

	inline std::vector<FBufferElement>::iterator begin() { return Elements.begin(); }
	inline std::vector<FBufferElement>::iterator end() { return Elements.end(); }
	inline std::vector<FBufferElement>::const_iterator begin() const { return Elements.begin(); }
	inline std::vector<FBufferElement>::const_iterator end() const { return Elements.end(); }

private:
	void CalculateOffsetAndStride();

	std::vector<FBufferElement> Elements;
	uint32_t Stride;
};

class UVertexBuffer
{
public:
	UVertexBuffer(uint32_t size);
	UVertexBuffer(float* vertices, uint32_t size);
	~UVertexBuffer();

	void Bind() const;
	void Unbind() const;

	inline void SetLayout(const FBufferLayout& layout) { Layout = layout; }
	inline const FBufferLayout& GetLayout() const { return Layout; }

private:
	FBufferLayout Layout;
	uint32_t BufferID;
};

class UIndexBuffer
{
public:
	UIndexBuffer(uint32_t* indices, uint32_t count);
	~UIndexBuffer();

	void Bind() const;
	void Unbind() const;

	inline uint32_t GetCount() const { return Count; }

private:
	uint32_t BufferID;
	uint32_t Count;
};