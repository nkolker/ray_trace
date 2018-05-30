#ifndef RAY_H
#define RAY_H

#define RAY_PRIMARY 0


#include "Vector4.h"
#include "Matrix4_4.h"

class Ray{

private:

public:
	Vector4 origin, direction;
	int rayType;

//Constructors
	Ray();
	Ray(Vector4 start, Vector4 end, int type);

//Destructor
	~Ray();

//Accessors
	Vector4 getOrigin();
	Vector4 getDirection();
	int getRayType();

//Mutators
	void setOrigin(const Vector4 &o);
	void setDirection(const Vector4 &d);
	void setRayType(const int &t);

//Math Methods

//Other
	void print();

//Static Functions

};

#endif
