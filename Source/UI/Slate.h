#pragma once


class UTexture;
class UFont;

class SSlate
{
public:


private:

};

class STextBox
{
public:


private:
	std::shared_ptr<UFont> Font;
	std::string TextString;
	glm::vec4 Color;
	float FontSize;

	glm::vec2 Position;
	glm::vec2 Scale;
};

class SImage
{
public:


private:
	std::shared_ptr<UTexture> ImageTexture;
	glm::vec4 Color;
	glm::vec2 Position;
	glm::vec2 Scale;

	bool bUseTexture;
};