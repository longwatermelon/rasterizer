#pragma once
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>


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

struct matrix3
{
	float m[3][3];
};


mesh read(const std::string& path);

void matmul(point& i, point& o, matrix& m);
std::vector<float> matrix_multiply(std::vector<std::vector<float>> mat, std::vector<float> vec);
point fast_matrix_multiply(matrix3& mat, point& p);

matrix make_projection(float fov, float ratio, float near, float far);

void swap_points(point& p1, point& p2);
void interpolate(float x0, float y0, float iz0, float x1, float y1, float iz1, std::array<float, 1000>& arr, std::array<float, 1000>& retz);