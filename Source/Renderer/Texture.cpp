#include "epch.h"
#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"
#include "glad/glad.h"


UTexture::UTexture(const std::string& filepath)
	:TextureID(0), Width(0), Height(0), Channels(0)
{
	stbi_set_flip_vertically_on_load(1);

	unsigned char* textureData = stbi_load(filepath.c_str(), &Width, &Height, &Channels, 4);
	ASSERT(textureData, "ITexture failed to load!");

	glCreateTextures(GL_TEXTURE_2D, 1, &TextureID);
	glTextureStorage2D(TextureID, 1, GL_RGBA8, Width, Height);

	glTextureParameteri(TextureID, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTextureParameteri(TextureID, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTextureParameteri(TextureID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTextureParameteri(TextureID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTextureSubImage2D(TextureID, 0, 0, 0, Width, Height, GL_RGBA, GL_UNSIGNED_BYTE, textureData);

	stbi_image_free(textureData);
}

UTexture::UTexture(void* data, int width, int height, int format)
	:TextureID(0), Width(width), Height(height), Channels(format)
{
	glCreateTextures(GL_TEXTURE_2D, 1, &TextureID);
	glTextureStorage2D(TextureID, 1, format == 4 ? GL_RGBA8 : GL_RGB8, Width, Height);

	glTextureParameteri(TextureID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTextureParameteri(TextureID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTextureParameteri(TextureID, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTextureParameteri(TextureID, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTextureSubImage2D(TextureID, 0, 0, 0, Width, Height, format == 4 ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, data);
}

UTexture::~UTexture()
{
	glDeleteTextures(1, &TextureID);
}

void UTexture::Bind(uint32_t slot)
{
	glBindTextureUnit(slot, TextureID);
}

void UTexture::Unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}
