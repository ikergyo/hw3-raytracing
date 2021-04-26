// Transform.cpp: implementation of the Transform class.

#include "Transform.h"

mat3 Transform::rotate(const float degrees, const vec3& axis) 
{
    float radDeg = glm::radians(degrees);
    float cosRad = cos(radDeg);
    mat3 aat = glm::outerProduct(axis, axis);

    return (mat3(1) * cosRad) + (aat * (1 - cosRad)) + (mat3(0, axis.z, -axis.y, -axis.z, 0, axis.x, axis.y, -axis.x, 0) * sin(radDeg));
}
//Rotate left and right
void Transform::left(float degrees, vec3& eye, vec3& up) 
{
    up = upvector(up, eye);
    eye = rotate(degrees, up) * eye;
}
//Rotate up and down
void Transform::up(float degrees, vec3& eye, vec3& up) 
{

    vec3 rotation_axis = glm::normalize(glm::cross(eye, up));
    mat3 rotation_matrix = rotate(degrees, rotation_axis);

    eye = rotation_matrix * eye;
    up = glm::normalize(rotation_matrix * up);
}

mat4 Transform::lookAt(const vec3 &eye, const vec3 &center, const vec3 &up) 
{
    vec3 a = eye - center;
    vec3 b = up;

    vec3 w = normalize(a);
    vec3 u = normalize(glm::cross(b, w));
    vec3 v = cross(w, u);

    mat4 lookAtMatrix = mat4(
        u.x, v.x, w.x, 0.0f,
        u.y, v.y, w.y, 0.0f,
        u.z, v.z, w.z, 0.0f,
        -dot(u, eye), -dot(v, eye), -dot(w, eye), 1.0f
    );
    return lookAtMatrix;
}

mat4 Transform::perspective(float fovy, float aspect, float zNear, float zFar)
{
    mat4 ret = mat4(
    1/(aspect * tan(glm::radians(fovy/2))), 0.0f, 0.0f, 0.0f,
    0.0f, 1/tan(glm::radians(fovy/2)), 0.0f, 0.0f,
    0.0f, 0.0f, -(zFar + zNear)/(zFar - zNear), -1.0f,
    0.0f, 0.0f, -(2 * zFar * zNear) / (zFar - zNear), 0.0f
    );
    return ret;
}

mat4 Transform::scale(const float &sx, const float &sy, const float &sz) 
{
    mat4 ret = mat4(
        sx, 0.0f, 0.0f, 0.0f,
        0.0f, sy, 0.0f, 0.0f,
        0.0f, 0.0f, sz, 0.0f, 
        0.0f, 0.0f, 0.0f, 1.0f
    );
    return ret;
}

mat4 Transform::translate(const float &tx, const float &ty, const float &tz) 
{
    mat4 ret = mat4(
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        tx, ty, tz, 1
    );

    return ret;
}


vec3 Transform::upvector(const vec3 &up, const vec3 & zvec) 
{
    vec3 x = glm::cross(up,zvec); 
    vec3 y = glm::cross(zvec,x); 
    vec3 ret = glm::normalize(y); 
    return ret; 
}


Transform::Transform()
{

}

Transform::~Transform()
{

}
