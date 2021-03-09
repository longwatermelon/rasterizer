#include "../include/object.h"
#include "../include/graphics.h"


void Object::project(Graphics& gfx, matrix& mproj, matrix3& roty, matrix3& rotx, Camera& cam, int sw, int sh)
{
	std::vector<point> projpoints(m.points.size());

	for (int i = 0; i < m.points.size(); ++i)
	{
		auto& p = m.points[i];

		point origp, projp;

		origp = p;

		// adjust for position
		origp.x += x + cam.x;
		origp.y += y + cam.y;
		origp.z += z + cam.z;

		// rotation
		origp = fast_matrix_multiply(roty, origp);
		origp = fast_matrix_multiply(rotx, origp);

		// projection
		matmul(origp, projp, mproj);

		// center and scale
		projp.x += 1.0f;
		projp.y += 1.0f;

		projp.x *= 0.5f * sw;
		projp.y *= 0.5f * sh;

		projpoints[i] = projp;
	}

	for (auto& t : m.tris)
	{
		gfx.draw_triangle(projpoints[t.indexes[0]], projpoints[t.indexes[1]], projpoints[t.indexes[2]]);
	}
}