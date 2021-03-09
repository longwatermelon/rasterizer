#pragma once
#include <vector>


struct point
{
	float x, y, z;
};

struct triangle
{
	int indexes[3];
};

struct mesh
{
	std::vector<point> points;
	std::vector<triangle> tris;
};

struct matrix
{
	float m[4][4];
};


void matmul(point& i, point& o, matrix& m);

matrix make_projection(float fov, float ratio, float near, float far);