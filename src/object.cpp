#include "../include/object.h"
#include "../include/graphics.h"


void Object::project(Graphics& gfx, matrix& mproj, int sw, int sh)
{
	for (auto& t : m.tris)
	{
		point origps[3], projps[3];

		for (int i = 0; i < 3; ++i)
		{
			origps[i] = m.points[t.indexes[i]];

			// adjust for position
			origps[i].x += x;
			origps[i].y += y;
			origps[i].z += z;

			origps[i].x *= scale;
			origps[i].y *= scale;

			matmul(origps[i], projps[i], mproj);

			// center and scale
			projps[i].x += 1.0f;
			projps[i].y += 1.0f;

			projps[i].x *= 0.5f * sw;
			projps[i].y *= 0.5f * sh;
		}

		gfx.draw_triangle(projps[0], projps[1], projps[2]);
	}
}