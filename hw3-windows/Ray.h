#pragma once
#include "glm\glm.hpp"

using namespace glm;
class Ray
{
public:
	Ray(vec3 origin, vec3 direction)
	{

		this->origin = origin;
		this->direction = normalize(direction);
	}

	void transformRay(const mat4& matrix) {
		this->origin = matrix * vec4(origin, 1.0f);
		this->direction = matrix * vec4(direction, 0.0f);
	}
public:
	vec3 origin;
	vec3 direction;
	float t;

};

