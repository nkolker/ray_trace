#include "Ray.h"

//constructors
	Ray::Ray(){
		rayType = RAY_PRIMARY;
		origin    = Vector4(0.0F, 0.0F, 0.0F, 1.0F);
		direction = Vector4(0.0F, 0.0F,-1.0F, 0.0F);
	}

	Ray::Ray(Vector4 start, Vector4 end, int type){
		rayType = type;
		origin = start;
		end.subtract(direction, start);
		direction.normalizeV(direction);
	}
//Destructor
	Ray::~Ray(){

	}

//Accessors
	Vector4 Ray::getOrigin(){
		return Vector4(origin);
	}
	Vector4 Ray::getDirection(){
		return Vector4(direction);
	}
	int Ray::getRayType(){
		return rayType;
	}

//Mutators
	void Ray::setOrigin(const Vector4 &o){
		origin = Vector4(o);
	}
	void Ray::setDirection(const Vector4 &d){
		direction = Vector4(d);
	}
	void Ray::setRayType(const int &t){
		rayType = t;
	}

//Other
	void Ray::print(){
		std::cerr << "Ray origin = ";
		origin.print();
		std::cerr << "Ray direction = ";
		direction.print();
		std::cerr << "Ray type: " << rayType << "\n";
	}
