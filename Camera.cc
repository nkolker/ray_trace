#include "Camera.h"

//constructors
	Camera::Camera(){
		horizResolution = H_RES_DEFAULT;
		vertResolution  = V_RES_DEFAULT;
		vertFOV = V_FOV_DEFAULT;
		position = Vector4(0.0F, 0.0F, 0.0F, 1.0F);
		forward  = Vector4(0.0F, 0.0F,-1.0F, 0.0F);
		up	    = Vector4(0.0F, 1.0F, 0.0F, 0.0F);
		forward.crossProd(right, up);
		right.normalizeV(right);
	}

	Camera::Camera(const size_t &hRes, const size_t &vRes, const float &vFOV, const Vector4 &pos, const Vector4 &f, const Vector4 &u){
		horizResolution = hRes;
		vertResolution  = vRes;
		aspectRatio = ((float) horizResolution) / ((float) vertResolution);
		if(vFOV < 180.0F && vFOV > 0.0F){
			vertFOV = vFOV;
		}
		else{
			std::cerr << "Camera FOV is invalid! Must be between 0 and 180 degrees! Setting FOV to default...";
			vertFOV = V_FOV_DEFAULT;
		}
		position = Vector4(pos);
		position.normalizeP(position);
		forward = Vector4(f);
		forward.normalizeV(forward);
		up = Vector4(u);
		up.normalizeV(up);
		calcRightVec();		
	}

//destructor
	Camera::~Camera(){

	}

//acessors
	size_t Camera::getVRes(){
		return vertResolution;
	}
	size_t Camera::getHRes(){
		return horizResolution;
	}
	float Camera::getVFOV(){
		return vertFOV;
	}
	float Camera::getAspectRatio(){
		return aspectRatio;
	}
	Vector4 Camera::getPosition(){
		return Vector4(position);
	}
	Vector4 Camera::getForward(){
		return Vector4(forward);
	}
	Vector4 Camera::getUp(){
		return Vector4(up);
	}
	Vector4 Camera::getRight(){
		return Vector4(right);
	}
//mutators
	void Camera::setVRes(const size_t &vRes){
		vertResolution = vRes;
		calcAspectRatio();
	}
	void Camera::setHRes(const size_t &hRes){
		horizResolution = hRes;
		calcAspectRatio();
	}
	void Camera::setVFOV(const float &degrees){
		vertFOV = degrees;
	}
	void Camera::setPosition(const Vector4 &pos){
		position = Vector4(pos);
	}
	void Camera::setForward(const Vector4 &f){
		forward = Vector4(f);
		forward.normalizeV(forward);
		calcRightVec();
	}
	void Camera::setUp(const Vector4 &u){
		up = Vector4(u);
		up.normalizeV(up);
		calcRightVec();
	}
//methods
	void Camera::calcAspectRatio(){
		aspectRatio = ((float) horizResolution) / ((float) vertResolution);
	}
	void Camera::calcRightVec(){
		forward.crossProd(right, up);
		right.normalizeV(right);
		right.crossProd(up, forward);
		up.normalizeV(up);
	}
