#pragma once
#include "projection.h"
#include "camera.h"
#include <array>
#include <SDL.h>


class Graphics;


class Object
{
public:
	Object(float x, float y, float z, const std::string& path)
		: x(x), y(y), z(z)
	{
		m = read(path);
	}

	void project(Graphics& gfx, matrix& mproj, matrix3& roty, matrix3& rotx, Camera& cam, int sw, int sh);

public:
	float x, y, z;
	std::array<float, 1000> xl{ 0 }, xr{ 0 };

	mesh m;
};