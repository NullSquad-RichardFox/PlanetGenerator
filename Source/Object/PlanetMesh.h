#pragma once

#include "Renderer/Buffer.h"


class UPlanetMesh
{
public:
	UPlanetMesh();

	void GenerateSphereMesh(float radius, int rings = 8, int segments = 8);

	inline uint32_t GetVerticesCount() const { return Vertices.size(); }
	inline uint32_t GetIndicesCount() const { return Indices.size(); }

	inline float* GetVerticesData() { return Vertices.data(); }
	inline uint32_t* GetIndicesData() { return Indices.data(); }

	inline const FBufferLayout& GetBufferLayout() { return BufferLayout; }

private:
	std::vector<float> Vertices;
	std::vector<uint32_t> Indices;

	FBufferLayout BufferLayout;
};