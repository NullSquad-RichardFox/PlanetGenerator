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

void main()
{

	switch(int(vMaterialData.TexID))
	{
		case -1: albedo = vMaterialData.Color; break;
		default: albedo = texture(uTextures[int(vMaterialData.TexID)], vMaterialData.TexCoord); break;
	}
}