#include "../include/projection.h"
#include "../include/graphics.h"
#include "../include/object.h"
#include "../include/camera.h"
#include <SDL.h>


int main(int argc, char** argv)
{
	bool running = true;

	int screen_w = 1000, screen_h = 1000;
	Graphics gfx(1000, 1000);

	matrix mproj = make_projection(90, screen_w / screen_h, 1.0f, 1000.0f);
	


	std::vector<Object> objects;

	//objects.push_back(Object(0.0f, 0.0f, 15.0f, "meshfiles/sphere.facet"));
	objects.push_back(Object(0.0f, 0.0f, 15.0f, "meshfiles/donut.facet"));

	Camera cam(0.0f, 0.0f, 0.0f);

	SDL_Event evt;

	while (running)
	{
		gfx.clear();

		matrix3 roty = { {
		{cosf(cam.ha), 0, sinf(cam.ha)},
		{0, 1, 0},
		{-sinf(cam.ha), 0, cosf(cam.ha)}
		} };

		matrix3 rotx = { {
			{1, 0, 0},
			{0, cosf(cam.va), sinf(cam.va)},
			{0, -sinf(cam.va), cosf(cam.va)}
		} };

		while (SDL_PollEvent(&evt))
		{
			if (evt.type == SDL_KEYDOWN)
			{
				switch (evt.key.keysym.sym)
				{
				case SDLK_w: cam.vec.z = -0.1f; break;
				case SDLK_s: cam.vec.z = 0.1f; break;
				case SDLK_d: cam.vec.x = -0.1f; break;
				case SDLK_a: cam.vec.x = 0.1f; break;
				case SDLK_SPACE: cam.vec.y = 0.1f; break;
				case SDLK_LSHIFT: cam.vec.y = -0.1f; break;
				case SDLK_RIGHT: cam.dha = 0.05f; break;
				case SDLK_LEFT: cam.dha = -0.05f; break;
				case SDLK_UP: cam.dva = -0.05f; break;
				case SDLK_DOWN: cam.dva = 0.05f; break;
				}
			}

			if (evt.type == SDL_KEYUP)
			{
				switch (evt.key.keysym.sym)
				{
				case SDLK_w:
				case SDLK_s: cam.vec.z = 0.0f; break;
				case SDLK_d:
				case SDLK_a: cam.vec.x = 0.0f; break;
				case SDLK_SPACE:
				case SDLK_LSHIFT: cam.vec.y = 0.0f; break;
				case SDLK_RIGHT:
				case SDLK_LEFT: cam.dha = 0.0f; break;
				case SDLK_UP:
				case SDLK_DOWN: cam.dva = 0.0f; break;
				}
			}

			if (evt.type == SDL_QUIT) running = false;
		}

		cam.move();

		SDL_SetRenderDrawColor(gfx.rend, 255, 255, 255, 255);

		for (auto& obj : objects)
		{
			obj.project(gfx, mproj, roty, rotx, cam, screen_w, screen_h);
		}

		SDL_SetRenderDrawColor(gfx.rend, 0, 0, 0, 255);

		gfx.render();
	}

	SDL_Quit();

	return 0;
}