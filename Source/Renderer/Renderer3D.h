#pragma once

#include "Object/PlanetMesh.h"

class UShader;
class UCamera;

class URenderer3D
{
public:
	URenderer3D();

	void Render();
	void RenderSphere();

	void SetPlanetData(int rings, int segments);

private:
	std::shared_ptr<UShader> Shader;
	std::shared_ptr<UCamera> Camera;

	UPlanetMesh Planet;
};