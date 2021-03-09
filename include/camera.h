#pragma once
#include "projection.h"
#include <SDL.h>


class Camera
{
public:
	float x, y, z;
	point vec = { 0, 0, 0 };

	Camera(float x, float y, float z)
		: x(x), y(y), z(z) {}


	void move()
	{
		x += vec.x;
		y += vec.y;
		z += vec.z;
	}
};