#ifndef VECTOR4_H
#define VECTOR4_H

#include "xmmintrin.h"
#include "Matrix4_4.h"

#define SHUFFLE_CW  201
#define SHUFFLE_CCW 210
#define MOV_W_TO_X  3
#define MOV_Z_TO_X  2
#define MOV_Y_TO_X  1

class Vector4{

public:

//Packed single precision floating point data:
	__m128 data __attribute__ ((aligned(16)));

//Constructors:
	Vector4();

	Vector4(float x, float y, float z, float w);

	Vector4(const float *vect);

	Vector4(const Vector4 &vect);

//Destructor:
	~Vector4();

//Accessors:
	float getX() const;

	float getY() const;

	float getZ() const;

	float getW() const;

	void getElements(float *elements) const;

	void print() const;

//Mutators:
	void setX(const float &x);

	void setY(const float &y);

	void setZ(const float &z);

	void setW(const float &w);

	void set(const float *elements);

//Vector math functions:
	void multiply(Vector4 &returnVal, const float &scalar) const;

	void pointwiseMultiply(Vector4 &returnVal, const Vector4 &v2);

	float dotProd(const Vector4 &v2) const;

	void crossProd(Vector4 &returnVal, const Vector4 &v2);

	float magSq() const;

	void normalizeV(Vector4 &returnVal);

	void normalizeP(Vector4 &returnVal);

	void normalizeV();

	void normalizeP();

	void add(Vector4 &returnVal, const Vector4 &v2) const;

	void subtract(Vector4 &returnVal, const Vector4 &v2) const;

	void transform(Vector4 &returnVal, const Matrix4_4 &m1);

};

#endif
