#pragma once
#include "projection.h"
#include "camera.h"
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

	void project(Graphics& gfx, matrix& mproj, matrix3& roty, Camera& cam, int sw, int sh);

public:
	float x, y, z;

	mesh m;
};