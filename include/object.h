#pragma once
#include "projection.h"
#include <SDL.h>

class Graphics;


class Object
{
public:
	Object(float x, float y, float z, float scale, const std::string& path)
		: x(x), y(y), z(z), scale(scale)
	{
		m = read(path);
	}

	void project(Graphics& gfx, matrix& mproj, int sw, int sh);

public:
	float x, y, z;
	float scale;

	mesh m;
};