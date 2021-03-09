#pragma once
#include "projection.h"
#include <SDL.h>


class Camera
{
public:
	float x, y, z;
	float ha = 0.0f, va = 0.0f;

	point vec = { 0, 0, 0 };
	float dha = 0.0f, dva = 0.0f;

	Camera(float x, float y, float z)
		: x(x), y(y), z(z) {}


	void move()
	{
		x += vec.x;
		y += vec.y;
		z += vec.z;

		ha += dha;
		va += dva;
	}
};