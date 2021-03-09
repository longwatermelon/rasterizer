#pragma once
#include "projection.h"
#include <SDL.h>


class Graphics
{
public:
	SDL_Window* window;
	SDL_Renderer* rend;
	int screen_w, screen_h;

	Graphics(int w = 1000, int h = 1000);

	bool mainloop(SDL_Event& evt);

	void render() { SDL_RenderPresent(rend); }
	void clear() { SDL_RenderClear(rend); }

	void draw_triangle(point& p1, point& p2, point& p3);
};