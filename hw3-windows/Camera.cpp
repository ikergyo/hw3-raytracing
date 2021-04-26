#include "Camera.h"
//j is the horizontal pixel, i is the vertical pixel

Camera::Camera(vec3 eye, vec3 lookat, vec3 up, float fov) {
	this->eye = eye;

	//lookat = center
	this->lookat = lookat;

	this->frontDirection = glm::normalize(eye - lookat);

	this->horDirection = glm::normalize(glm::cross(up, frontDirection));

	this->up = glm::normalize(glm::cross(frontDirection, horDirection));
	//this->up = up;
	this->fov = fov;
	fovy = fov;
}

Ray Camera::createRay(float i, float j, int width, int height, float aspectRatio)
{
	//To use the edge of the pixel, not the center of the pixel
	float iF = i + 0.5f;
	float jF = j + 0.5f;

	float halfW = (float)width / 2.0f;
	float halfH = (float)height / 2.0f;

	
	float alpha = fovx * ((jF - halfW) / halfW);
	float beta = tan(radians(fovy) / 2) * ((halfH - iF) / halfH);


	vec3 rayDirection = glm::normalize(-frontDirection + horDirection * alpha  + up * beta);
	Ray ray(eye, rayDirection);

	return ray;
}
void Camera::SetupFovx(float aspectRatio) {
	fovx = tan(radians(fovy) / 2.0f) * aspectRatio;
}