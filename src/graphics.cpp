#include "../include/graphics.h"
#include <array>


Graphics::Graphics(int w, int h)
	: screen_w(w), screen_h(h)
{
	SDL_Init(SDL_INIT_EVERYTHING);

	window = SDL_CreateWindow("sample text", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screen_w, screen_h, SDL_WINDOW_SHOWN);
	rend = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	screen = new SDL_Color[1000 * 1000];
	depths = new float[1000 * 1000];
}


void Graphics::draw_triangle(point& p1, point& p2, point& p3)
{
	SDL_RenderDrawLine(rend, p1.x, p1.y, p2.x, p2.y);
	SDL_RenderDrawLine(rend, p2.x, p2.y, p3.x, p3.y);
	SDL_RenderDrawLine(rend, p3.x, p3.y, p1.x, p1.y);
}


void Graphics::draw_filled_triangle(point p0, point p1, point p2, point op0, point op1, point op2, const point& color, std::array<float, 1000>& xl, std::array<float, 1000>& xr, std::array<float, 1000>& izl, std::array<float, 1000>& izr)
{
	// sort points from low to high y
	if (p1.y < p0.y)
	{
		swap_points(p1, p0);
		swap_points(op1, op0);
	}
	if (p2.y < p0.y)
	{
		swap_points(p2, p0);
		swap_points(op2, op0);
	}
	if (p2.y < p1.y)
	{
		swap_points(p2, p1);
		swap_points(op2, op1);
	}

	//float max{ -1e10 };

	interpolate(p0.x, p0.y, 1.f / op0.z, p1.x, p1.y, 1.f / op1.z, xl, izl);
	/*for (int i = 0; i < 1000; ++i)
	{
		if (max < izl[i]) max = izl[i];
	}
	std::cout << "izl: " << max << "\n";*/
	interpolate(p1.x, p1.y, 1.f / op1.z, p2.x, p2.y, 1.f / op2.z, xl, izl);
	/*max = -1e10;
	for (int i = 0; i < 1000; ++i)
	{
		if (max < izl[i]) max = izl[i];
	}
	std::cout << "izl: " << max << "\n";*/
	interpolate(p0.x, p0.y, 1.f / op0.z, p2.x, p2.y, 1.f / op2.z, xr, izr);
	//max = -1e10;
	//for (int i = 0; i < 1000; ++i)
	//{
	//	if (max < izr[i]) max = izr[i];
	//}
	//std::cout << "izr: " << max << "\n";
	

	if (p2.y > 1000) p2.y = 1000;
	if (p0.y < 0) p0.y = 0;

	for (int y = (int)p0.y; y < (int)p2.y; ++y)
	{
		int minx = std::min(xl[y], xr[y]);
		int maxx = std::max(xl[y], xr[y]);

		for (int i = minx; i < maxx; ++i)
		{
			//SDL_RenderDrawPoint(rend, i, y);
			float iz = izl[y] + (i - xl[y]) * ((izr[y] - izl[y]) / (xr[y] - xl[y]));

			if (iz > depths[y * 1000 + i])
			{
				screen[y * 1000 + i] = { (Uint8) color.x, (Uint8) color.y, (Uint8) color.z };
				depths[y * 1000 + i] = iz;
			}
		}
	}
}