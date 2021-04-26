#pragma once
#include "stdax.h"
#include "Ray.h"


using namespace glm;

class Camera
{

public:
	Camera() {};

	Camera(vec3 eye, vec3 lookat, vec3 up, float fov);
	void SetupFovx(float aspectRatio);
	Ray createRay(float i, float j, int width, int height, float aspectRatio);

	vec3 up;
	vec3 frontDirection;
	vec3 horDirection;
	vec3 eye;
	vec3 lookat;
	float fov;

private:
	float fovx;
	float fovy;
};


