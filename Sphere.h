#ifndef SPHERE_H
#define SPHERE_H

#include "Object3D.h"
#include "Vector4.h"

class Sphere:public Object3D{

private:

public:
Vector4 position;
float radius;
Vector4 color;
Sphere();
Sphere(Vector4 &center, float &radius);
Sphere(Vector4 &center, float &radius, Vector4 &color);
~Sphere();
bool intersect(Ray &r);

};

#endif
