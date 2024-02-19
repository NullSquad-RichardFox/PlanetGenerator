#include "epch.h"
#include "Font.h"
#include "Texture.h"
#include "Utility/Time.h"


#define DEFAULT_ANGLE_THRESHOLD 3.0
#define LCG_MULTIPLIER 6364136223846793005ull
#define LCG_INCREMENT 1442695040888963407ull
#define THREAD_COUNT 8

UFont::UFont(const std::string& filepath)
{
    double sTime = UTime::GetTime();

    msdfgen::FreetypeHandle* ft = msdfgen::initializeFreetype();
    ASSERT(ft, "FreeType failed to load!");

    msdfgen::FontHandle* font = msdfgen::loadFont(ft, filepath.c_str());
    ASSERT(font, "Font file failed to load!");

    double fontScale = 1.0;

    FontGeometry.reset(new msdf_atlas::FontGeometry(&Glyphs));
    int glyphsLoaded = FontGeometry->loadCharset(font, fontScale, msdf_atlas::Charset::ASCII);
    LOG("Loaded glyphs {0} out of {1}", glyphsLoaded, msdf_atlas::Charset::ASCII.size());

    double emSize = 32;
    msdf_atlas::TightAtlasPacker atlasPacker;
    atlasPacker.setPixelRange(2.0);
    atlasPacker.setMiterLimit(1.0);
    atlasPacker.setPadding(0);
    atlasPacker.setScale(emSize);
    int remaining = atlasPacker.pack(Glyphs.data(), (int)Glyphs.size());

    int atlasWidth, atlasHeight;
    atlasPacker.getDimensions(atlasWidth, atlasHeight);
    emSize = atlasPacker.getScale();

    uint64_t coloringSeed = 0;
    msdf_atlas::Workload([&Glyphs = Glyphs, &coloringSeed](int i, int threadNo) -> bool {
        unsigned long long glyphSeed = (LCG_MULTIPLIER * (coloringSeed ^ i) + LCG_INCREMENT) * !!coloringSeed;
        Glyphs[i].edgeColoring(msdfgen::edgeColoringInkTrap, DEFAULT_ANGLE_THRESHOLD, glyphSeed);
        return true;
    }, Glyphs.size()).finish(THREAD_COUNT);

    msdf_atlas::GeneratorAttributes attributes;
    attributes.config.overlapSupport = true;
    attributes.scanlinePass = true;

    msdf_atlas::ImmediateAtlasGenerator<float, 3, msdf_atlas::msdfGenerator, msdf_atlas::BitmapAtlasStorage<uint8_t, 3>> generator(atlasWidth, atlasHeight);
    generator.setAttributes(attributes);
    generator.setThreadCount(8);
    generator.generate(Glyphs.data(), (int)Glyphs.size());

    msdfgen::BitmapConstRef<uint8_t, 3> bitmap = (msdfgen::BitmapConstRef<uint8_t, 3>)generator.atlasStorage();
    FontTexture.reset(new UTexture((void*)bitmap.pixels, bitmap.width, bitmap.height, 3));

    msdfgen::destroyFont(font);
    msdfgen::deinitializeFreetype(ft);

    LOG("Font loaded in {}s", UTime::GetTime() - sTime);
}

UFont::~UFont()
{
}

void UFont::GetCharTextCoords(char c, glm::vec2& texCoordMin, glm::vec2& texCoordMax)
{
	if (!FontGeometry || !FontTexture) return;

	double l, b, r, t;
	FontGeometry->getGlyph(c)->getQuadAtlasBounds(l, b, r, t);
	texCoordMin = glm::vec2(l / FontTexture->GetWidth(), b / FontTexture->GetHeight());
	texCoordMax = glm::vec2(r / FontTexture->GetWidth(), t / FontTexture->GetHeight());
}

void UFont::GetCharSize(char c, float scale, glm::vec2& sizeMin, glm::vec2& sizeMax)
{
	if (!FontGeometry) return;

	double l, b, r, t;
	double fsScale = (double)scale / (FontGeometry->getMetrics().ascenderY - FontGeometry->getMetrics().descenderY);

	FontGeometry->getGlyph(c)->getQuadAtlasBounds(l, b, r, t);
	sizeMin = glm::vec2(l * fsScale, b * fsScale);
	sizeMax = glm::vec2(r * fsScale, t * fsScale);
}

float UFont::GetAdvance(char c, char nextC, float scale)
{
	if (!FontGeometry) return 0.0f;

	double adv;
	double diff = FontGeometry->getMetrics().ascenderY - FontGeometry->getMetrics().descenderY;
	double fsScale = (double)scale / diff;
	FontGeometry->getAdvance(adv, c, nextC);
	return (float)adv * fsScale;
}
