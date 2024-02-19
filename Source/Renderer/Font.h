#pragma once


#undef INFINITE
#include "msdf-atlas-gen/msdf-atlas-gen.h"

class UTexture;

class UFont
{
public:
	UFont(const std::string& filepath);
	~UFont();

	void GetCharTextCoords(char c, glm::vec2& texCoordMin, glm::vec2& texCoordMax);
	void GetCharSize(char c, float scale, glm::vec2& sizeMin, glm::vec2& sizeMax);

	float GetAdvance(char c, char nextC, float scale);

	inline const std::shared_ptr<UTexture>& GetTexture() const { return FontTexture; }

private:
	std::shared_ptr<UTexture> FontTexture;
	std::shared_ptr<msdf_atlas::FontGeometry> FontGeometry;
	std::vector<msdf_atlas::GlyphGeometry> Glyphs;
};