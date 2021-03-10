#include "../include/projection.h"


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


matrix make_projection(float fov, float ratio, float near, float far)
{
	float fovrad = 1.0f / tanf(fov * 0.5f / 180.0f * 3.1415f);
	matrix mat = { {
		{ratio * fovrad, 0, 0, 0},
		{0, fovrad, 0, 0},
		{0, 0, far / (far - near), 1.0f},
		{0, 0, (-far * near) / (far - near), 0}
	} };

	return mat;
}


void swap_points(point& p1, point& p2)
{
	point temp = p1;
	p1 = p2;
	p2 = temp;
}


std::vector<float> interpolate(float x0, float y0, float x1, float y1)
{
	std::vector<float> ret;

	float slope = (x1 - x0) / (y1 - y0);

	for (float y = y0; y < y1; ++y)
	{
		float x = x0 + (slope * (y - y0));
		ret.push_back(x);
	}

	return ret;
}


void matmul(point& i, point& o, matrix& m)
{
	o.x = i.x * m.m[0][0] + i.y * m.m[1][0] + i.z * m.m[2][0] + m.m[3][0];
	o.y = i.x * m.m[0][1] + i.y * m.m[1][1] + i.z * m.m[2][1] + m.m[3][1];
	o.z = i.x * m.m[0][2] + i.y * m.m[1][2] + i.z * m.m[2][2] + m.m[3][2];
	float w = i.x * m.m[0][3] + i.y * m.m[1][3] + i.z * m.m[2][3] + m.m[3][3];

	if (w != 0.0f)
	{
		o.x /= w;
		o.y /= w;
		o.z /= w;
	}
}


std::vector<float> matrix_multiply(std::vector<std::vector<float>> mat, std::vector<float> vec)
{
	std::vector<float> ret(mat.size());

	for (int y = 0; y < mat.size(); ++y)
	{
		ret[y] = 0.0f;
		for (int x = 0; x < mat[0].size(); ++x)
		{
			ret[y] += mat[y][x] * vec[x];
		}
	}

	return ret;
}


point fast_matrix_multiply(matrix3& mat, point& p)
{
	point ret;

	ret.x = p.x * mat.m[0][0] + p.y * mat.m[1][0] + p.z * mat.m[2][0];
	ret.y = p.x * mat.m[0][1] + p.y * mat.m[1][1] + p.z * mat.m[2][1];
	ret.z = p.x * mat.m[0][2] + p.y * mat.m[1][2] + p.z * mat.m[2][2];

	return ret;
}