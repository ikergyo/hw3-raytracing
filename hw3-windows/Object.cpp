#include "Object.h"

const float gEps = 1e-6f;
int sgn(float x) { return x > gEps ? 1 : x < -gEps ? -1 : 0; }

bool Sphere::GetIntersection(const Ray rayIn, float& out_t, vec3& out_n, vec3& out_p) {

	float min_t = 0.000001f;
	float max_t = INFINITY;

	float t = INFINITY;


	vec4 orig_ = vec4(rayIn.origin, 1.0f);
	vec4 dir_ = vec4(rayIn.direction, 0.0f);
	orig_ = inverseTransform * orig_;
	dir_ = inverseTransform * dir_;
	vec3 orig = vec3(orig_.x / orig_.w, orig_.y / orig_.w, orig_.z / orig_.w);
	//vec3 orig = vec3(orig_);
	vec3 dir = normalize(vec3(dir_.x, dir_.y, dir_.z));
	

	float c2 = glm::dot(dir, dir);
	float c1 = 2.0f * glm::dot(dir, orig - center);
	float c0 = glm::dot(orig - center, orig - center) - radius * radius;
	float delta = c1 * c1 - 4.0f * c2 * c0;

	if (delta < -gEps) {
		return false;
	}

	delta = fabs(delta);
	// closest intersection point
	float x = std::min((-c1 - sqrt(delta)) / (2.0f * c2),
		(-c1 + sqrt(delta)) / (2.0f * c2));

	if (x < 1e-3f) {
		if (x > 0) {
			//printf("sphere near zero = %f\n", x);
		}
		return false;
	}

	t = x;
	
	
	vec3 p_Transformed = orig + dir * t;
	vec4 p_Homogeneous = transform * vec4(p_Transformed, 1.0f); //Transforming back
	
	vec3 p = vec3(p_Homogeneous.x / p_Homogeneous.w, p_Homogeneous.y / p_Homogeneous.w, p_Homogeneous.z / p_Homogeneous.w); //dehomogenization
	
	
	vec3 n_Transformed = p_Transformed - center;
	vec4 n_tr = inverseTransposedTransform * vec4(n_Transformed, 0.0f);
	vec3 n = normalize(vec3(n_tr.x, n_tr.y, n_tr.z));

	t = length(p - rayIn.origin);

	out_n = n;
	out_t = t;
	out_p = p;
	return true;
	
}
bool Sphere::solveQuadratic(const float& a, const float& b, const float& c, float& x0, float& x1)
{
	float discr = b * b - 4 * a * c;
	if (discr < 0) return false;
	else if (discr == 0) x0 = x1 = -0.5f * b / a;
	else {
		float tempPosX = -b + sqrt(discr);
		float tempNegX = -b - sqrt(discr);
		float twoA = 2 * a;
		x0 = tempPosX / twoA;
		x1 = tempNegX / twoA;
	}
	if (x0 > x1) std::swap(x0, x1);

	return true;
}

float Sphere::GetDiscriminant(float a, float b, float c) {
	return b * b - 4 * a * c;
}

bool Triangle::GetIntersection(const Ray rayIn, float& out_t, vec3& out_n, vec3& out_p) {
	
	float kEpsilon = 1e-8f;

	Ray ray = rayIn;

	vec3 orig = rayIn.origin;
	vec3 dir = rayIn.direction;

	vec4 A_ = transform * vec4(vertices[0].x, vertices[0].y, vertices[0].z, 1.0f);
	vec4 B_ = transform * vec4(vertices[1].x, vertices[1].y, vertices[1].z, 1.0f);
	vec4 C_ = transform * vec4(vertices[2].x, vertices[2].y, vertices[2].z, 1.0f);
	

	vec3 A = vec3(A_ / A_.w);
	vec3 B = vec3(B_ / B_.w);
	vec3 C = vec3(C_ / C_.w);
	vec3 AB = B - A;
	vec3 AC = C - A;

	vec3 m_Normal = cross(AB, AC);
	float norm_norm = dot(m_Normal, m_Normal);

	float area_full_triangle = length(m_Normal);
	
	vec3 normal = normalize(m_Normal);
	//if these are perpendicular, than the ray parallel with the plane of the triangle
	float dN = dot(m_Normal, dir);
	if (abs(dN) < kEpsilon)
		return false;

	float d = dot(m_Normal, A);
	float t = (d - dot(m_Normal, orig)) / dN;
	//Behind the camera checking
	if (t < 0)
		return false;

	float u;
	float v;

	 vec3 P = orig + (dir * t);

	 vec3 C_C;
	 vec3 AP = P - A;
	 //edge 0
	 C_C = cross(AB, AP);
	 if (dot(m_Normal, C_C) < 0)
		 return false; //P is on the right side

	 //edge1
	 vec3 edge1 = C - B;
	 vec3 BP = P - B;
	 C_C = cross(edge1, BP);
	 if (u = dot(m_Normal, C_C) < 0)
		 return false; //P is on the right side

	 //edge2
	 vec3 edge2 = A - C;
	 vec3 CP = P - C;
	 C_C = cross(edge2, CP);
	 if (v = dot(m_Normal, C_C) < 0)
		 return false; //P is on the right side

	 u /= norm_norm;
	 v /= norm_norm;
	 vec4 trp = transform * vec4(P, 1.0f);
	 out_p = P; //vec3(trp / trp.w);
	 out_n = normal;//normalize(vec3(inverseTransposedTransform * vec4(normal, 0.0f)));

	 //t = length(out_p - rayIn.origin);
	 out_t = t;


	 return true;
}
