#pragma once


class UPlanetMesh
{
public:
	void GenerateSphereMesh(float radius, int rings = 8, int segments = 8);

	inline uint32_t GetVerticesCount() const { return Vertices.size(); }
	inline uint32_t GetIndicesCount() const { return Indices.size(); }

	inline float* GetVerticesData() { return Vertices.data(); }
	inline uint32_t* GetIndicesData() { return Indices.data(); }

private:
	std::vector<float> Vertices;
	std::vector<uint32_t> Indices;
};