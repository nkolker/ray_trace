#ifndef CAMERA_H
#define CAMERA_H

#define H_RES_DEFAULT 640
#define V_RES_DEFAULT 480
#define V_FOV_DEFAULT 90.0F

#include "Vector4.h"
#include <iostream>

class Camera{
private:
public:
	size_t vertResolution, horizResolution;
	float vertFOV, aspectRatio;
	Vector4 position, forward, up, right;
//constructors
	Camera();
	Camera(const size_t &hRes, const size_t &vRes, const float &vFOV, const Vector4 &pos, const Vector4 &forward, const Vector4 &up);
//destructor
	~Camera();
//acessors
	size_t getVRes();
	size_t getHRes();
	float getVFOV();
	float getAspectRatio();
	Vector4 getPosition();
	Vector4 getForward();
	Vector4 getUp();
	Vector4 getRight();
//mutators
	void setVRes(const size_t &vRes);
	void setHRes(const size_t &hRes);
	void setVFOV(const float  &vFOV);
	void setPosition(const Vector4 &p);
	void setForward(const Vector4 &f);
	void setUp(const Vector4 &u);
//methods
	void calcAspectRatio();
	void calcRightVec();
};

#endif
