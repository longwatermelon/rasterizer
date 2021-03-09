#include "../include/projection.h"
#include "../include/graphics.h"
#include "../include/object.h"
#include <SDL.h>


int main(int argc, char** argv)
{
	bool running = true;

	int screen_w = 1000, screen_h = 1000;
	Graphics gfx(1000, 1000);

	matrix mproj = make_projection(90, screen_w / screen_h, 1.0f, 1000.0f);

	
	std::vector<Object> objects;

	objects.push_back(Object(0.0f, 0.0f, 15.0f, 1.0f, "meshfiles/sphere.facet"));
	objects.push_back(Object(0.0f, 0.0f, 15.0f, 2.0f, "meshfiles/donut.facet"));


	SDL_Event evt;

	while (gfx.mainloop(evt))
	{
		gfx.clear();

		SDL_SetRenderDrawColor(gfx.rend, 255, 255, 255, 255);

		for (auto& obj : objects)
		{
			obj.project(gfx, mproj, screen_w, screen_h);
		}

		SDL_SetRenderDrawColor(gfx.rend, 0, 0, 0, 255);

		gfx.render();
	}

	SDL_Quit();

	return 0;
}