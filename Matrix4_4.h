#ifndef MATRIX4_4_H
#define MATRIX4_4_H

#include "xmmintrin.h"
#include <iostream>

#define SHUFFLE_CW  201
#define SHUFFLE_CCW 210
#define MOV_W_TO_X  3
#define MOV_Z_TO_X  2
#define MOV_Y_TO_X  1

class Matrix4_4{

private:

public:

	__m128 row0, row1, row2, row3 __attribute__ ((aligned(16)));

//Constructors:
	Matrix4_4();

	Matrix4_4(const float *r0, const float *r1, const float *r2, const float *r3);

	Matrix4_4(const float *arr);

	Matrix4_4(const Matrix4_4 &m1);

//Destructors:
	~Matrix4_4();

//Accessors:
	float get(const int &column, const int &row);

	void get(float *arr) const;

	void print() const;

//Mutators:
	void set(const int &column, const int &row, const float &val);

	void set(const float *arr);

//Static functions
	static void identity(Matrix4_4 &returnVal);

	static void push(const Matrix4_4 &m1);

	static void pop(Matrix4_4 &m1);

//Matrix math functions:
	void multiply(Matrix4_4 &returnVal, const Matrix4_4 &m2);

};

#endif
