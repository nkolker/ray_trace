#ifndef OBJECT3D_H
#define OBJECT3D_H

#include "Ray.h"

class Object3D{

private:

public:

virtual bool intersect(Ray *r);
virtual ~Object3D();
Object3D();

};

#endif
