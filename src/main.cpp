#include "../include/projection.h"
#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <SDL.h>


//struct point
//{
//	float x, y, z;
//};
//
//struct triangle
//{
//	int indexes[3];
//};
//
//struct mesh
//{
//	std::vector<point> points;
//	std::vector<triangle> tris;
//};
//
//struct matrix
//{
//	float m[4][4];
//};


mesh read(const std::string& path)
{
	std::fstream f(path);

	std::stringstream ss;
	std::string line;

	for (int i = 0; i < 5; ++i) std::getline(f, line);

	int point_num = -1;
	std::stringstream(line) >> point_num;

	double minx = 1e10, miny = 1e10, minz = 1e10, maxx = -1e10, maxy = -1e10, maxz = -1e10;

	std::vector<point> points;
	for (int i = 0; i < point_num; ++i)
	{
		std::getline(f, line);
		
		std::stringstream ss(line);

		double arr[3];
		for (int j = 0; j < 3; ++j)
		{
			double num;
			ss >> num;
			
			arr[j] = num;
		}

		if (arr[0] < minx) minx = arr[0];
		if (arr[0] > maxx) maxx = arr[0];

		if (arr[1] < miny) miny = arr[1];
		if (arr[1] > maxy) maxy = arr[1];

		if (arr[2] < minz) minz = arr[2];
		if (arr[2] > maxz) maxz = arr[2];

		points.push_back({ (float)arr[0], (float)arr[1], (float)arr[2] });
	}

	for (int i = 0; i < 3; ++i) std::getline(f, line);

	int tri_num = -1;
	std::stringstream(line) >> tri_num;

	std::vector<triangle> tris;
	for (int i = 0; i < tri_num; ++i)
	{
		std::getline(f, line);

		std::stringstream ss(line);

		triangle temp;
		for (int j = 0; j < 3; ++j)
		{
			int num;
			ss >> num;

			temp.indexes[j] = num - 1;
		}

		tris.push_back(temp);
	}

	f.close();

	return { points, tris };
}


//matrix make_projection(float fov, float ratio, float near, float far)
//{
//	float fovrad = 1.0f / tanf(fov * 0.5f / 180.0f * 3.1415f);
//	matrix mat = {{
//		{ratio * fovrad, 0, 0, 0},
//		{0, fovrad, 0, 0},
//		{0, 0, far / (far - near), 1.0f},
//		{0, 0, (-far * near) / (far - near), 0}
//	}};
//
//	return mat;
//}
//
//
//void matmul(point& i, point& o, matrix& m)
//{
//	o.x = i.x * m.m[0][0] + i.y * m.m[1][0] + i.z * m.m[2][0] + m.m[3][0];
//	o.y = i.x * m.m[0][1] + i.y * m.m[1][1] + i.z * m.m[2][1] + m.m[3][1];
//	o.z = i.x * m.m[0][2] + i.y * m.m[1][2] + i.z * m.m[2][2] + m.m[3][2];
//	float w = i.x * m.m[0][3] + i.y * m.m[1][3] + i.z * m.m[2][3] + m.m[3][3];
//
//	if (w != 0.0f)
//	{
//		o.x /= w;
//		o.y /= w;
//		o.z /= w;
//	}
//}


int main(int argc, char** argv)
{
	bool running = true;
	mesh cube = read(R"(C:\Users\qianh\Downloads\meshfiles\cube.facet)");

	SDL_Init(SDL_INIT_EVERYTHING);

	int screen_w = 1000, screen_h = 1000;
	SDL_Window* window = SDL_CreateWindow("sample text", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screen_w, screen_h, SDL_WINDOW_SHOWN);
	SDL_Renderer* rend = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);


	matrix mproj = make_projection(90, screen_w / screen_h, 1.0f, 1000.0f);


	SDL_Event evt;

	while (running)
	{
		while (SDL_PollEvent(&evt))
		{
			switch (evt.type)
			{
			case SDL_QUIT: running = false; break;
			}
		}

		SDL_RenderClear(rend);

		SDL_SetRenderDrawColor(rend, 255, 255, 255, 255);

		for (auto& t : cube.tris)
		{
			point origpoint[3], projpoint[3];

			for (int i = 0; i < 3; ++i)
			{
				origpoint[i] = cube.points[t.indexes[i]];
				origpoint[i].x -= 0.5f;
				origpoint[i].y -= 0.5f;
				origpoint[i].z += 3.0f;
				matmul(origpoint[i], projpoint[i], mproj);
			}

			for (int i = 0; i < 3; ++i)
			{
				projpoint[i].x += 1.0f;
				projpoint[i].y += 1.0f;
				projpoint[i].x *=  0.5f * screen_w;
				projpoint[i].y *=  0.5f * screen_h;
			}

			SDL_RenderDrawLine(rend, projpoint[0].x, projpoint[0].y, projpoint[1].x, projpoint[1].y);
			SDL_RenderDrawLine(rend, projpoint[1].x, projpoint[1].y, projpoint[2].x, projpoint[2].y);
			SDL_RenderDrawLine(rend, projpoint[2].x, projpoint[2].y, projpoint[0].x, projpoint[0].y);
		}

		SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);

		SDL_RenderPresent(rend);
	}

	SDL_Quit();

	return 0;
}