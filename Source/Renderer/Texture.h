#pragma once


class UTexture
{
public:
	UTexture(const std::string& filepath);
	UTexture(void* data, int width, int height, int format);
	~UTexture();

	void Bind(uint32_t slot = 0U);
	void Unbind();

	inline int GetWidth() const { return Width; }
	inline int GetHeight() const { return Height; }

private:
	uint32_t TextureID;
	int Width;
	int Height;
	int Channels;
};