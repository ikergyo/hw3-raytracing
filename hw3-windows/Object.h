#pragma once
#include "glm\glm.hpp"
#include "Ray.h"
#include "stdax.h"

using namespace glm;
enum class Shape { sphere, triangle };

struct Vertex
{
	Vertex() = default;
	Vertex(float x, float y, float z) : x(x), y(y), z(z){}
	float x, y, z;
};
class Object
{
public: 
	Object() = default;
	virtual ~Object() {

	}
	virtual bool GetIntersection(const Ray rayIn, float& out_t, vec3& out_n, vec3& out_p) = 0;

public:
	Shape type;
	float ambient[3] = { 0, 0, 0 };
	float diffuse[3] = { 0, 0, 0 };
	float specular[3] = { 0, 0, 0 };
	float emission[3] = { 0, 0, 0};
	float shininess = 0;
	//float shininess;
	mat4 transform;
	mat4 inverseTransform;
	mat4 inverseTransposedTransform;
	mat4 transposedInverseTransform;
};

class Sphere : public Object {

public:
	Sphere(vec3 center, float radius) : center(center), radius(radius) {
		type = Shape::sphere;
	}
	bool GetIntersection(const Ray rayIn, float& out_t, vec3& out_n, vec3& out_p);
	vec3 center;
	float radius;
	bool solveQuadratic(const float& a, const float& b, const float& c, float& x0, float& x1);


private:
	float GetDiscriminant(float a, float b, float c);
};

class Triangle : public Object {

public: 
	
	Triangle(Vertex v1, Vertex v2, Vertex v3) : vertices{ v1, v2, v3 } {
		type = Shape::triangle;
	}
	bool GetIntersection(const Ray rayIn, float& out_t, vec3& out_n, vec3& out_p);

	Vertex vertices[3];
};



