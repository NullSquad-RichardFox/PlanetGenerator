#include "epch.h"
#include "PlanetMesh.h"


#define M_PI 3.14159265358979323846 

UPlanetMesh::UPlanetMesh()
{
    BufferLayout = {
        { EShaderDataType::Float3, "aPosition" },
        { EShaderDataType::Float3, "aNormal" }
    };
}

void UPlanetMesh::GenerateSphereMesh(float radius, int rings, int segments)
{
    Vertices.clear();
    Indices.clear();

    Vertices.reserve(size_t(BufferLayout.GetSize()) * rings * segments);
    Indices.reserve(0);

	float segmentStep = M_PI / segments;
	float ringStep = 2 * M_PI / rings;
    float invRadius = 1 / radius;

	for (int i = 0; i <= segments; i++)
	{
		float segAngle = M_PI / 2 - i * segmentStep;
		float xz = radius * cosf(segAngle);
		float y = radius * sinf(segAngle);

		for (int j = 0; j <= rings; j++)
		{
			float ringAngle = j * ringStep;
            float x = xz * cosf(ringAngle);
            float z = xz * sinf(ringAngle);

            // vertices
			Vertices.push_back(x);
			Vertices.push_back(y);
			Vertices.push_back(z);

            // normals
            Vertices.push_back(x * invRadius);
            Vertices.push_back(y * invRadius);
            Vertices.push_back(z * invRadius);
		}
	}

    uint32_t k1, k2;
    for (int i = 0; i < segments; ++i)
    {
        k1 = i * (rings + 1);
        k2 = k1 + rings + 1;

        for (int j = 0; j < rings; ++j, ++k1, ++k2)
        {
            if (i != 0)
            {
                Indices.push_back(k1);
                Indices.push_back(k2);
                Indices.push_back(k1 + 1);
            }

            if (i != (segments - 1))
            {
                Indices.push_back(k1 + 1);
                Indices.push_back(k2);
                Indices.push_back(k2 + 1);
            }
        }
    }
}
