#include "Vector4.h"
#include <iostream>
#include <cmath>

/*int main(){
	float arr[] = {1, 0, 0, 0};
	Vector4 v1(arr);
	Vector4 v2(0, 1, 0, 0);
	Vector4 v3;
	v1.add(v3, v2);
	Vector4 v4;
	v1.crossProd(v4, v2);
	float dotProduct = v1.dotProd(v2);
	std::cerr << "v1 + v2 = ";
	float temp[] = {0.0, 0.0, 0.0, 0.0};
	_mm_store_ps(temp, v3.data);
	for(int i = 0; i < 4; i++){
		std::cerr << temp[i] << ", ";
	}
	std::cerr << '\n';
	std::cerr << "v1 x v2 = ";
	//float temp[4] = {0.0, 0.0, 0.0, 0.0};
	_mm_store_ps(temp, v4.data);
	for(int i = 0; i < 4; i++){
		std::cerr << temp[i] << ", ";
	}
	std::cerr << '\n';
	std::cerr << "v1 * v2 = " << dotProduct << '\n';
	Vector4 v5(8, 8, 8, 4);
	Vector4 v6;
	v5.normalizeP(v6);
	std::cerr << "v5 normalized = ";
	_mm_store_ps(temp, v6.data);
	for(int i = 0; i < 4; i++){
		std::cout << temp[i] << ", ";
	}
	std::cout << '\n';
	Vector4 v7(10, 10, 10, 0);
	Vector4 v8;
	v7.normalizeV(v8);
	std::cerr << "v7 normalized = ";
	_mm_store_ps(temp, v8.data);
	for(int i = 0; i < 4; i++){
		std::cout << temp[i] << ", ";
	}
	std::cout << '\n';
	Vector4 v9;
	v1.subtract(v9, v2);
	std::cerr << "v1 - v2 = ";
	_mm_store_ps(temp, v9.data);
	for(int i = 0; i < 4; i++){
		std::cout << temp[i] << ", ";
	}
	std::cout << '\n';
	float matrix1[] =  { 1.0,  2.0,  3.0,  4.0,
						 5.0,  6.0,  7.0,  8.0,
						 9.0, 10.0, 11.0, 12.0,
						13.0, 14.0, 15.0, 16.0};
	Matrix4_4 m1(matrix1);
	Matrix4_4 m2, m3;
	Matrix4_4::identity(m2);
	m1.multiply(m3, m2);
	std::cerr << "m1 * m2 = ";
	float vals[16];
	m3.get(vals);
	for(int i = 0; i < 16; i++){
		std::cerr << vals[i] << " ";
	}
	std::cerr << '\n';
	Vector4 v10, v11;
	v11 = Vector4(100, 100, 0.0, 1.0);
	float row0[] = {0.005, 0.0, 0.0, -1.5};
	float row1[] = {0.0, -0.005, 0.0, 1.0};
	float row2[] = {0.0, 0.0, 1.0, -1.0};
	float row3[] = {0.0, 0.0, 0.0, 1.0};
	Matrix4_4 m4(row0, row1, row2, row3);
	v11.normalizeP();
	v11.transform(v11, m4);

	_mm_store_ps(temp, v11.data);
	for(int i = 0; i < 4; i++){
		std::cout << temp[i] << ", ";
	}
	std::cout << '\n';
	return 0;
}*/

//Constructors:
Vector4::Vector4(){
	data = _mm_set_ps(0.0, 0.0, 0.0, 0.0);
}

Vector4::Vector4(float x, float y, float z, float w){
	data = _mm_set_ps(w, z, y, x);
}

Vector4::Vector4(const float *vect){
	data = _mm_load_ps(vect);
}

Vector4::Vector4(const Vector4 &vect){
	data = vect.data;
}

//Destructor:
Vector4::~Vector4(){

}

//Accessors:
float Vector4::getX() const{
	float elements[4];
	_mm_store_ps(elements, data);
	return elements[0];
}

float Vector4::getY() const{
	float elements[4];
	_mm_store_ps(elements, data);
	return elements[1];
}

float Vector4::getZ() const{
	float elements[4];
	_mm_store_ps(elements, data);
	return elements[2];
}

float Vector4::getW() const{
	float elements[4];
	_mm_store_ps(elements, data);
	return elements[3];
}

void Vector4::getElements(float *elements) const{
	_mm_store_ps(elements, data);
}

void Vector4::print() const{
	float temp[4];
	getElements(temp);
	for(int i = 0; i < 4; i++){
		std::cerr << temp[i] << (((i+1)%4!=0)?", ":"\n");
	}
}

//Mutators:
void Vector4::setX(const float &x){
	float elements[4];
	getElements(elements);
	elements[0] = x;
	set(elements);
}

void Vector4::setY(const float &y){
	float elements[4];
	getElements(elements);
	elements[1] = y;
	set(elements);
}

void Vector4::setZ(const float &z){
	float elements[4];
	getElements(elements);
	elements[2] = z;
	set(elements);
}

void Vector4::setW(const float &w){
	float elements[4];
	getElements(elements);
	elements[3] = w;
	set(elements);
}

void Vector4::set(const float *elements){
	data = _mm_load_ps(elements);
}

//Vector math functions
void Vector4::multiply(Vector4 &returnVal, const float &scalar) const{
	returnVal.data = _mm_mul_ps(data, _mm_set1_ps(scalar));
}

void Vector4::pointwiseMultiply(Vector4 &returnVal, const Vector4 &v2){
	returnVal.data = _mm_mul_ps(data, v2.data);
}

float Vector4::dotProd(const Vector4 &v2) const{
	static __m128 temp __attribute__ ((aligned(16)));	//static because only want to allocate/deallocate memory once
	temp = _mm_mul_ps(data, v2.data);
	temp = _mm_add_ps(_mm_add_ps(_mm_shuffle_ps(temp, temp, SHUFFLE_CW), temp), _mm_shuffle_ps(temp, temp, SHUFFLE_CCW));
	return _mm_cvtss_f32(temp);
}

void Vector4::crossProd(Vector4 &returnVal, const Vector4 &v2){
	//assume initialized with w, z, y, x
	returnVal.data = _mm_sub_ps(_mm_mul_ps(_mm_shuffle_ps(data, data, SHUFFLE_CW), _mm_shuffle_ps(v2.data, v2.data, SHUFFLE_CCW)), _mm_mul_ps(_mm_shuffle_ps(v2.data, v2.data, SHUFFLE_CW), 		_mm_shuffle_ps(data, data, SHUFFLE_CCW)));
}

float Vector4::magSq() const{
	static __m128 temp __attribute__ ((aligned(16)));	//static because only want to allocate/deallocate memory once
	temp = _mm_mul_ps(data, data);
	temp = _mm_add_ps(_mm_add_ps(_mm_shuffle_ps(temp, temp, SHUFFLE_CW), temp), _mm_shuffle_ps(temp, temp, SHUFFLE_CCW));
	return _mm_cvtss_f32(temp);
}

void Vector4::normalizeV(Vector4 &returnVal){
	returnVal.data = _mm_div_ps(data, _mm_set1_ps(std::sqrt(magSq())));
}

void Vector4::normalizeP(Vector4 &returnVal){
	returnVal.data = _mm_div_ps(data, _mm_set1_ps(_mm_cvtss_f32(_mm_shuffle_ps(data, data, MOV_W_TO_X))));
}

void Vector4::normalizeV(){
	data = _mm_div_ps(data, _mm_set1_ps(std::sqrt(magSq())));
}

void Vector4::normalizeP(){
	data = _mm_div_ps(data, _mm_set1_ps(_mm_cvtss_f32(_mm_shuffle_ps(data, data, MOV_W_TO_X))));
}

void Vector4::add(Vector4 &returnVal, const Vector4 &v2) const{
	returnVal.data = _mm_add_ps(data, v2.data);
}

void Vector4::subtract(Vector4 &returnVal, const Vector4 &v2) const{
	returnVal.data = _mm_sub_ps(data, v2.data);
}

void Vector4::transform(Vector4 &returnVal, const Matrix4_4 &m1){
	static __m128 temp0, temp1, temp2, temp3, tempdata __attribute__ ((aligned(16)));	//static because only want to allocate/deallocate memory once
	temp0 = m1.row0;
	temp1 = m1.row1;
	temp2 = m1.row2;
	temp3 = m1.row3;
	
	_MM_TRANSPOSE4_PS(temp0, temp1, temp2, temp3);
	
	tempdata = _mm_mul_ps(temp0, _mm_set1_ps(_mm_cvtss_f32(data)));
	
	tempdata = _mm_add_ps(tempdata, _mm_mul_ps(temp1, _mm_set1_ps(_mm_cvtss_f32(_mm_shuffle_ps(data, data, MOV_Y_TO_X)))));
	
	tempdata = _mm_add_ps(tempdata, _mm_mul_ps(temp2, _mm_set1_ps(_mm_cvtss_f32(_mm_shuffle_ps(data, data, MOV_Z_TO_X)))));
	
	tempdata = _mm_add_ps(tempdata, _mm_mul_ps(temp3, _mm_set1_ps(_mm_cvtss_f32(_mm_shuffle_ps(data, data, MOV_W_TO_X)))));
	
	returnVal.data = tempdata;
}








