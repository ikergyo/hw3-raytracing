#pragma once
#include "stdax.h"
#include "Scene.h"


class FileReader{
public:
	static void matransform (std::stack<mat4> &transfstack, float * values) ;
	static void rightmultiply (const mat4 & M, std::stack<mat4> &transfstack) ;
	static bool readvals (std::stringstream &s, const int numvals, float * values) ;
	static std::unique_ptr<Scene> readfile (const char * filename) ;
};
