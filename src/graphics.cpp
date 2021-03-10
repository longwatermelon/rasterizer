#include "../include/graphics.h"

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


void Graphics::draw_filled_triangle(point p0, point p1, point p2, const point& color)
{
	// sort points from low to high y
	if (p1.y < p0.y) swap_points(p1, p0);
	if (p2.y < p0.y) swap_points(p2, p0);
	if (p2.y < p1.y) swap_points(p2, p1);

	std::vector<float> x01 = interpolate(p0.x, p0.y, p1.x, p1.y);
	std::vector<float> x12 = interpolate(p1.x, p1.y, p2.x, p2.y);
	std::vector<float> x02 = interpolate(p0.x, p0.y, p2.x, p2.y);

	if (x02.empty()) return;

	x01.insert(x01.end(), x12.begin(), x12.end());

	for (int y = static_cast<int>(p0.y); y < static_cast<int>(p2.y); ++y)
	{
		int index = y - static_cast<int>(p0.y);
		SDL_RenderDrawLine(rend, x01[index], y, x02[index], y);
	}
}