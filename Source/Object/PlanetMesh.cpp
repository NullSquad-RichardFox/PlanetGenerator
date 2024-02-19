#include "epch.h"
#include "PlanetMesh.h"


#define M_PI 3.14159265358979323846 

void UPlanetMesh::GenerateSphereMesh(float radius, int rings, int segments)
{
    Vertices.clear();
    Indices.clear();

    Vertices.reserve(size_t(3) * rings * segments);
    Indices.reserve(0);

	float segmentStep = M_PI / segments;
	float ringStep = 2 * M_PI / rings;

	for (int i = 0; i <= segments; i++)
	{
		float segAngle = M_PI / 2 - i * segmentStep;
		float xz = radius * cosf(segAngle);
		float y = radius * sinf(segAngle);

		for (int j = 0; j <= rings; j++)
		{
			float ringAngle = j * ringStep;

			Vertices.push_back(xz * cosf(ringAngle));
			Vertices.push_back(y);
			Vertices.push_back(xz * sinf(ringAngle));
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
