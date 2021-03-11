#include "../include/object.h"
#include "../include/graphics.h"
#include <array>


void Object::project(Graphics& gfx, matrix& mproj, matrix3& roty, matrix3& rotx, Camera& cam, int sw, int sh)
{
	std::vector<point> projpoints(m.points.size());
	std::vector<point> origpoints(m.points.size());

	for (int i = 0; i < m.points.size(); ++i)
	{
		auto& p = m.points[i];

		point origp, projp;

		origp = p;

		// adjust for position
		origp.x += this->x + cam.x;
		origp.y += this->y + cam.y;
		origp.z += this->z + cam.z;

		// rotation
		origp = fast_matrix_multiply(roty, origp);
		origp = fast_matrix_multiply(rotx, origp);

		origpoints[i] = origp;

		// projection
		matmul(origp, projp, mproj);

		// center and scale
		projp.x += 1.0f;
		projp.y += 1.0f;

		projp.x *= 0.5f * sw;
		projp.y *= 0.5f * sh;

		projpoints[i] = projp;
	}

	for (int i = 0; i < 1000 * 1000; ++i)
	{
		gfx.screen[i] = { 0, 0, 0 };
		gfx.depths[i] = 0;
	}
	
	for (auto& t : m.tris)
	{
		if (origpoints[t.indexes[0]].z > 1.0f && origpoints[t.indexes[1]].z > 1.0f && origpoints[t.indexes[2]].z > 1.0f)
		{
			//SDL_SetRenderDrawColor(gfx.rend, r(rng), g(rng), b(rng), 255);
			gfx.draw_filled_triangle(projpoints[t.indexes[0]], projpoints[t.indexes[1]], projpoints[t.indexes[2]],
				origpoints[t.indexes[0]], origpoints[t.indexes[1]], origpoints[t.indexes[2]],
				{ (float) ((t.indexes[0] * 100) % 105 + 150), (float)( (t.indexes[1] * 100) % 105 + 150), (float) ((t.indexes[2] * 100) % 105 + 150) }, xl, xr, izl, izr);
			//SDL_SetRenderDrawColor(gfx.rend, 255, 0, 0, 255);
			//gfx.draw_triangle(projpoints[t.indexes[0]], projpoints[t.indexes[1]], projpoints[t.indexes[2]]);
		}
	}

	/*float max{ -1e10 }, min{ 1e10 };
	for (int i = 0; i < 1000 * 1000; ++i)
	{
		if (max < gfx.depths[i]) max = gfx.depths[i];
		if (min > gfx.depths[i]) min = gfx.depths[i];
	}

	std::cout << min << " | " << max << "\n";*/
	for (int y = 0; y < 1000; ++y)
	{
		for (int x = 0; x < 1000; ++x)
		{
			SDL_SetRenderDrawColor(gfx.rend, gfx.screen[y * 1000 + x].r, gfx.screen[y * 1000 + x].g, gfx.screen[y * 1000 + x].b, 255);
			SDL_RenderDrawPoint(gfx.rend, x, y);
		}
	}
}