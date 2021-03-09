#pragma once
#include "projection.h"
#include <SDL.h>

class Graphics;


class Object
{
public:
	Object(float x, float y, float z, const std::string& path)
		: x(x), y(y), z(z), mpath(path)
	{
		m = read(path);
	}

	void project(Graphics& gfx, matrix& mproj, int sw, int sh);

public:
	std::string mpath;

	float x, y, z;
	mesh m;
};