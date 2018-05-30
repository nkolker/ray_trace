#ifndef RENDER_H
#define RENDER_H

#include "Camera.h"
#include "Ray.h"

Ray* generatePrimaryRays(size_t &arrSize, Camera &cam);

#endif
