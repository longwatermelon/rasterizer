#include "../include/projection.h"
#include "../include/graphics.h"
#include <SDL.h>


int main(int argc, char** argv)
{
	bool running = true;
	mesh cube = read(R"(C:\Users\qianh\Downloads\meshfiles\cube.facet)");

	int screen_w = 1000, screen_h = 1000;
	Graphics gfx(1000, 1000);

	matrix mproj = make_projection(90, screen_w / screen_h, 1.0f, 1000.0f);

	SDL_Event evt;
	while (gfx.mainloop(evt))
	{
		gfx.clear();

		SDL_SetRenderDrawColor(gfx.rend, 255, 255, 255, 255);

		for (auto& t : cube.tris)
		{
			point origpoints[3], projpoints[3];

			for (int i = 0; i < 3; ++i)
			{
				origpoints[i] = cube.points[t.indexes[i]];
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
		}

		SDL_SetRenderDrawColor(gfx.rend, 0, 0, 0, 255);

		gfx.render();
	}

	SDL_Quit();

	return 0;
}