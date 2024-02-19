#type vertex
#version 450 core

layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec3 aNormal;

uniform mat4 uViewProjMat;

out vec3 vNormal;

void main()
{
	vNormal = aNormal;
	gl_Position = uViewProjMat * vec4(aPosition, 1.0);
}			

#type fragment
#version 450 core

out vec4 albedo;

in vec3 vNormal;

void main()
{
	vec3 lightDir = normalize(vec3(1.0, 1.0, 0.0));
	float diff = dot(lightDir, vNormal);

	albedo = vec4(vec3(1.0) * diff, 1.0);
}