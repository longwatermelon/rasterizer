#include "../include/graphics.h"
#include <array>


Graphics::Graphics(int w, int h)
	: screen_w(w), screen_h(h)
{
	SDL_Init(SDL_INIT_EVERYTHING);

	window = SDL_CreateWindow("sample text", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screen_w, screen_h, SDL_WINDOW_SHOWN);
	rend = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
}


bool Graphics::mainloop(SDL_Event& evt)
{
	while (SDL_PollEvent(&evt))
	{
		switch (evt.type)
		{
		case SDL_QUIT: return false;
		}
	}

	return true;
}


void Graphics::draw_triangle(point& p1, point& p2, point& p3)
{
	SDL_RenderDrawLine(rend, p1.x, p1.y, p2.x, p2.y);
	SDL_RenderDrawLine(rend, p2.x, p2.y, p3.x, p3.y);
	SDL_RenderDrawLine(rend, p3.x, p3.y, p1.x, p1.y);
}


void Graphics::draw_filled_triangle(point p0, point p1, point p2, const point& color, std::array<float, 1000>& xl, std::array<float, 1000>& xr)
{
	// sort points from low to high y
	if (p1.y < p0.y) swap_points(p1, p0);
	if (p2.y < p0.y) swap_points(p2, p0);
	if (p2.y < p1.y) swap_points(p2, p1);

	interpolate(p0.x, p0.y, p1.x, p1.y, xl);
	interpolate(p1.x, p1.y, p2.x, p2.y, xl);
	interpolate(p0.x, p0.y, p2.x, p2.y, xr);

	if (p2.y > 1000) p2.y = 1000;
	if (p0.y < 0) p0.y = 0;

	for (int y = (int)p0.y; y < (int)p2.y; ++y)
	{
		int minx = std::min(xl[y], xr[y]);
		int maxx = std::max(xl[y], xr[y]);

		for (int i = minx; i < maxx; ++i)
		{
			SDL_RenderDrawPoint(rend, i, y);
		}

		//SDL_RenderDrawLine(rend, xl[y], y, xr[y], y);
	}
}