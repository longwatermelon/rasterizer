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