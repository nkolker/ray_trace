#ifndef RENDER_H
#define RENDER_H

#include "Camera.h"
#include "Ray.h"

Ray* generatePrimaryRays(size_t &arrSize, Camera &cam);
void render(Camera cam, std::vector<Object3D*> objs);
Vector4 castRay(Ray &r, std::vector<Object3D> objs);
bool trace(Ray &r, std::vector<Object3D> objs, float tNear, Object3D *o);

#endif
