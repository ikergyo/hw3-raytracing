#pragma once
#include "stdax.h"
#include "Object.h"
#include "Light.h"
#include "Camera.h"
#include "Transform.h" 
#include "Object.h"

static enum { view, translate, scale } transop;

class Scene
{
public:
	Scene() {
	}
	~Scene() {
		for (int i = 0; i < numobjects; i++)
		{
			delete objects[i];
		}
		delete[] lights;
	}

public:
	int width=640;
	int height=460;
	float aspectRatio;
	vec3 attenuation = vec3(1, 0, 0);

	std::string output_filename = "output.png";

	int maxdepth = 5; //Bouncing limit
	int currentdepth = 0;
	//Light
	const static int numLights = 10;
	Light* lights = new Light[numLights];
	int numused;                     // How many lights are used 

	//Camera
	Camera mainCamera;


	// For multiple objects, read from a file.  
	const static int maxobjects = 100000;
	int numobjects;
	//Object* objects = new Object[maxobjects];
	Object* objects[maxobjects];
};

