#pragma once
#include "projection.h"
#include <array>
#include <SDL.h>


class Graphics
{
public:
	SDL_Window* window;
	SDL_Renderer* rend;
	int screen_w, screen_h;

	SDL_Color* screen;
	float* depths;

	Graphics(int w = 1000, int h = 1000);

	~Graphics()
	{
		delete[] screen;
		delete[] depths;
	}

	void render() { SDL_RenderPresent(rend); }
	void clear() { SDL_RenderClear(rend); }

	void draw_triangle(point& p1, point& p2, point& p3);
	void draw_filled_triangle(point p0, point p1, point p2, point op1, point op2, point op3, const point& color, std::array<float, 1000>& xl, std::array<float, 1000>& xr, std::array<float, 1000>& izl, std::array<float, 1000>& izr);
};