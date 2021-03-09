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

/*for (auto& t : cube.m.tris)
		{
			point origpoints[3], projpoints[3];

			for (int i = 0; i < 3; ++i)
			{
				origpoints[i] = cube.m.points[t.indexes[i]];
				origpoints[i].x -= 0.5f;
				origpoints[i].y -= 0.5f;
				origpoints[i].z += 3.0f;
				matmul(origpoints[i], projpoints[i], mproj);
			}

			for (int i = 0; i < 3; ++i)
			{
				projpoints[i].x += 1.0f;
				projpoints[i].y += 1.0f;
				projpoints[i].x *=  0.5f * screen_w;
				projpoints[i].y *=  0.5f * screen_h;
			}

			gfx.draw_triangle(projpoints[0], projpoints[1], projpoints[2]);
		}*/