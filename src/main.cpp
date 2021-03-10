#include "../include/projection.h"
#include "../include/graphics.h"
#include "../include/object.h"
#include "../include/camera.h"
#include <SDL.h>
#include <Windows.h>


int main(int argc, char** argv)
{
	bool running = true;

	int screen_w = 1000, screen_h = 1000;
	Graphics gfx(1000, 1000);

	matrix mproj = make_projection(90, screen_w / screen_h, 1.0f, 1000.0f);
	

	std::vector<Object> objects;
	objects.push_back(Object(0.0f, 0.0f, 15.0f, "meshfiles/spirala.facet"));

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

		if (GetAsyncKeyState('W') < 0)
		{
			cam.z += -0.1f * cosf(cam.ha);
			cam.x += -0.1f * sinf(cam.ha);
		}

		if (GetAsyncKeyState('S') < 0)
		{
			cam.z += 0.1f * cosf(cam.ha);
			cam.x += 0.1f * sinf(cam.ha);
		}

		if (GetAsyncKeyState('A') < 0)
		{
			cam.z += 0.1f * cosf(cam.ha + (3.1415 / 2));
			cam.x += 0.1f * sinf(cam.ha + (3.1415 / 2));
		}

		if (GetAsyncKeyState('D') < 0)
		{
			cam.z -= 0.1f * cosf(cam.ha + (3.1415 / 2));
			cam.x -= 0.1f * sinf(cam.ha + (3.1415 / 2));
		}

		if (GetAsyncKeyState(VK_SPACE) < 0)
			cam.y += 0.1f;

		if (GetAsyncKeyState(VK_SHIFT) < 0)
			cam.y -= 0.1f;

		if (GetAsyncKeyState(VK_LEFT) < 0)
			cam.ha -= 0.05f;

		if (GetAsyncKeyState(VK_RIGHT) < 0)
			cam.ha += 0.05f;

		if (GetAsyncKeyState(VK_UP) < 0)
			cam.va -= 0.05f;

		if (GetAsyncKeyState(VK_DOWN) < 0)
			cam.va += 0.05f;

		while (SDL_PollEvent(&evt))
		{
			if (evt.type == SDL_QUIT) running = false;
		}

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