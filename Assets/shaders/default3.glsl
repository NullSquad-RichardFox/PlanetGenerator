#type vertex
#version 450 core

layout(location = 0) in vec3 aPosition;

uniform mat4 uViewProjMat;

void main()
{
	gl_Position = uViewProjMat * vec4(aPosition, 1.0);
}			

#type fragment
#version 450 core

out vec4 albedo;

void main()
{
	albedo = vec4(1.0);
}