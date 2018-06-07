#include "Sphere.h"

Sphere::Sphere(){
	position = Vector4(0.0F, 0.0F, 0.0F, 1.0F);
	radius = 1.0F;
	color = Vector4(1.0F, 1.0F, 1.0F, 1.0F);
}

Sphere::Sphere(Vector4 &center, float &radius){
	position = Vector4(center);
	radius = radius;
	color = Vector4(1.0F, 1.0F, 1.0F, 1.0F);
}

Sphere::Sphere(Vector4 &center, float &radius, Vector4 &color){
	position = Vector4(center);
	radius = radius;
	color = Vector4(color);
}

Sphere::~Sphere(){

}

bool Sphere::intersect(Ray &r){
	
}
