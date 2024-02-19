#type vertex
#version 450 core

struct MatData
{
	vec4 Color;
	vec2 TexCoord;
	float TexID;
};

layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec4 aColor;
layout(location = 2) in vec2 aTexCoord;
layout(location = 3) in float aTexID;	

uniform mat4 uViewProjMat;

out MatData vMaterialData;

void main()
{
	vMaterialData.Color = aColor;
	vMaterialData.TexCoord = aTexCoord;
	vMaterialData.TexID = aTexID;
    gl_Position = uViewProjMat * vec4(aPosition, 1.0);
}  	

#type fragment
#version 450 core

struct MatData
{
	vec4 Color;
	vec2 TexCoord;
	float TexID;
};

out vec4 albedo;

layout (binding = 0) uniform sampler2D uTextures[32];
layout (location = 0) in MatData vMaterialData;

float screenPxRange() {
    vec2 unitRange = vec2(2.0)/vec2(textureSize(uTextures[int(vMaterialData.TexID)], 0));
    vec2 screenTexSize = vec2(1.0)/fwidth(vMaterialData.TexCoord);
    return max(0.5*dot(unitRange, screenTexSize), 1.0);
}

float median(float r, float g, float b) {
    return max(min(r, g), min(max(r, g), b));
}

void main()
{    
    vec3 msd = texture(uTextures[int(vMaterialData.TexID)], vMaterialData.TexCoord).rgb;
    float sd = median(msd.x, msd.y, msd.z);
    float screenPxDistance = screenPxRange()*(sd - 0.5);
    float opacity = clamp(screenPxDistance + 0.5, 0.0, 1.0);
    albedo = vec4(vMaterialData.Color.xyz, opacity);
}  