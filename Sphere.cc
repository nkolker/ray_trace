#include "Sphere.h"
#include "Defines.h"

Sphere::Sphere(){
	position = Vector4(0.0F, 0.0F, 0.0F, 1.0F);
	radius = 1.0F;
	radius2 = radius * radius;
	color = Vector4(1.0F, 1.0F, 1.0F, 1.0F);
	t = T_FAR;
}

Sphere::Sphere(Vector4 &center, float &radius){
	position = Vector4(center);
	radius = radius;
	radius2 = radius * radius;
	color = Vector4(1.0F, 1.0F, 1.0F, 1.0F);
	t = T_FAR;
}

Sphere::Sphere(Vector4 &center, float &radius, Vector4 &color){
	position = Vector4(center);
	radius = radius;
	color = Vector4(color);
	t = T_FAR;
}

Sphere::~Sphere(){

}

bool Sphere::intersect(Ray &r){
	float t0 = T_FAR, t1 = T_FAR;
	Vector4 l = Vector4();
	r.origin.subtract(l, position);
	float a = r.direction.dotProd(r.direction); 
	float b = 2.0F * r.direction.dotProd(L); 
	float c = L.dotProd(L) - radius2;
	if(!solveQuadratic(a, b, c, t0, t1)){
		return false;
	}
	if(t0 > t1){
		float temp = t1;
		t1 = t0;
		t0 = temp;
	}
	if(t0 < 0.0F){
		t0 = t1;
		if(t0 < 0.0F){
			return false;
		}
	}
	t = t0;
	return true;
}

void Sphere::setRadius(const float &r){
	radius = r;
	radius2 = r * r;
}

void Sphere::setPosition(const Vector4 &p){
	position = Vector4(p);
}

void Sphere::setColor(const Vector4 &c){
	color = Vector4(c);
}

bool solveQuadratic(const float &a, const float &b, const float &c, float &x0, float &x1){
	float discriminant = b * b - 4.0F * a * c;
	if(discriminant < 0.0F){
		return false;
	}
	else if(discriminant == 0.0F){
		x0 = - 0.5 * b / a;
		x1 = x0;
	}
	else { 
		float q = (b > 0) ? -0.5 * (b + sqrt(discriminant)) : -0.5 * (b - sqrt(discriminant)); 
		x0 = q / a; 
		x1 = c / q;
	}
	if (x0 > x1) std::swap(x0, x1); 
	return true;
}
