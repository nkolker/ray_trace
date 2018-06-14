#define _USE_MATH_DEFINES

#include "Render.h"
#include <cmath>

int main(int argc, char *argv[]){
	Vector4 camPos = Vector4(0.0F, 0.0F, 0.0F, 1.0F);
	Vector4 camFwd = Vector4(0.0F, 0.0F,-1.0F, 0.0F);
	Vector4 camUp  = Vector4(0.0F, 1.0F, 0.0F, 0.0F);
	Camera cam = Camera(2, 2, 90.0F, camPos, camFwd, camUp);
	Sphere s = Sphere(Vector4(0.0F, 0.0F, -2.0F, 1.0F), 1.0F);
	std::vector<Object3D*> objs;
	objs.push_back(s);
	render(cam, objs);
}

void render(Camera cam, std::vector<Object3D*> objs){
	Ray *camRays;
	size_t arrayLen = 0;
	camRays = generatePrimaryRays(arrayLen, cam);
}

Vector4 castRay(Ray &r, std::vector<Object3D> objs){

}

bool trace(Ray &r, std::vector<Object3D> objs, float tNear, Object3D *o){

}

/*Generates primary rays from the camera. Returns pointer to dynamically allocated Ray array. Takes as arguments 
a reference to a size_t variable that the final size of the Ray array will be stored in, and the camera that is 
being used for the render.*/
Ray* generatePrimaryRays(size_t &arrSize, Camera &cam){
	arrSize = cam.vertResolution * cam.horizResolution;
	Ray* raysArray = new Ray[arrSize];
	float FOV_radians = cam.getVFOV() * M_PI / 180.0F;
	
	float yHeight = 2.0F * std::tan(FOV_radians / 2.0F);
	float xWidth = cam.getAspectRatio() * yHeight;
	//std::cerr << "yHeight = " << yHeight << " and xWidth = " << xWidth << "\n";
	float yStep = -1.0f * yHeight / (float) cam.vertResolution;	//negative because window starts at top left corner
	float xStep = xWidth / (float) cam.horizResolution;
	//std::cerr << "ystep = " << yStep << " and xstep = " << xStep << "\n";
	float yStartOffset = (yHeight / 2.0F) + (yStep / 2.0F);
	float xStartOffset = (-1.0F * xWidth / 2.0F) + (xStep / 2.0F);
	//std::cerr << "yStartOffset = " << yStartOffset << " and xStartOffset = " << xStartOffset << "\n";
	Vector4 temp = Vector4();
	Vector4 startPoint = Vector4();
	cam.position.add(startPoint, cam.forward);
	cam.up.multiply(temp, yStartOffset);
	startPoint.add(startPoint, temp);
	cam.right.multiply(temp, xStartOffset);
	startPoint.add(startPoint, temp);
	Vector4 endPoint = Vector4();
	Vector4 yOffset = Vector4(), xOffset = Vector4();
	for(size_t x = 0; x < cam.horizResolution; x++){	//loop through each column of pixels
		for(size_t y = 0; y < cam.vertResolution; y++){
			cam.right.multiply(xOffset, x * xStep);
			cam.up.multiply(yOffset, y * yStep);
			xOffset.add(xOffset, yOffset);
			startPoint.add(endPoint, xOffset);
			raysArray[x + y * cam.horizResolution] = Ray(cam.position, endPoint, RAY_PRIMARY);
		}
	}
	return raysArray;
}
