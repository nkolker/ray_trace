#include "Matrix4_4.h"
#include <iostream>

//Constructors:
Matrix4_4::Matrix4_4(){
	row0 = _mm_setzero_ps();
	row1 = _mm_setzero_ps();
	row2 = _mm_setzero_ps();
	row3 = _mm_setzero_ps();
}

Matrix4_4::Matrix4_4(const float *r0, const float *r1, const float *r2, const float *r3){
	row0 = _mm_load_ps(r0);
	row1 = _mm_load_ps(r1);
	row2 = _mm_load_ps(r2);
	row3 = _mm_load_ps(r3);
}

Matrix4_4::Matrix4_4(const float *arr){
	row0 = _mm_set_ps(arr[3],  arr[2],  arr[1],  arr[0]);
	row1 = _mm_set_ps(arr[7],  arr[6],  arr[5],  arr[4]);
	row2 = _mm_set_ps(arr[11],  arr[10],  arr[9], arr[8]);
	row3 = _mm_set_ps(arr[15], arr[14], arr[13], arr[12]);
	float fTemp[4];
	_mm_store_ps(fTemp, row0);
	/*for(int i = 0; i < 4; i++){
		std::cerr << fTemp[i] << ", ";
	}
	std::cerr << "\n";*/
	_mm_store_ps(fTemp, row1);
	/*for(int i = 0; i < 4; i++){
		std::cerr << fTemp[i] << ", ";
	}
	std::cerr << "\n";*/
	_mm_store_ps(fTemp, row2);
	/*for(int i = 0; i < 4; i++){
		std::cerr << fTemp[i] << ", ";
	}
	std::cerr << "\n";*/
	_mm_store_ps(fTemp, row3);
	/*for(int i = 0; i < 4; i++){
		std::cerr << fTemp[i] << ", ";
	}
	std::cerr << "\n\n";*/
}

Matrix4_4::Matrix4_4(const Matrix4_4 &m1){
	row0 = m1.row0;
	row1 = m1.row1;
	row2 = m1.row2;
	row3 = m1.row3;
}

//Destructors:
Matrix4_4::~Matrix4_4(){}

//Accessors:
float Matrix4_4::get(const int &column, const int &row){
	if(column < 0 || column > 3 || row < 0 || row > 3){
		std::cerr << "Invalid indices: value must be be 0, 1, 2, or 3!\n";
		return 0;
	}
	float r[] = {0, 0, 0, 0};
	if(row == 0){
		_mm_store_ps(r, row0);
		return r[column];
	}
	else if(row == 1){
		_mm_store_ps(r, row1);
		return r[column];
	}
	else if(row == 2){
		_mm_store_ps(r, row2);
		return r[column];
	}
	else if(row == 3){
		_mm_store_ps(r, row3);
		return r[column];
	}
	return -1;
}

void Matrix4_4::get(float *arr) const{	//assumes length of arr is 16
	static float dataArr[4][4];	//static because only want to allocate/deallocate memory once	
	_mm_store_ps(dataArr[0], row0);
	_mm_store_ps(dataArr[1], row1);
	_mm_store_ps(dataArr[2], row2);
	_mm_store_ps(dataArr[3], row3);
	for(int i = 0; i < 4; i++){
		arr[4 * i]     = dataArr[i][0];
		arr[4 * i + 1] = dataArr[i][1];
		arr[4 * i + 2] = dataArr[i][2];
		arr[4 * i + 3] = dataArr[i][3];
	}
}

void Matrix4_4::print() const{
	float arr[16];
	get(arr);
	for(int i = 0; i < 16; i++){
		std::cerr << arr[i] << (((i+1)%4!=0)?", ":"\n");
	}
}

//Mutators:
void Matrix4_4::set(const int &column, const int &row, const float &val){
	if(column < 0 || column > 3 || row < 0 || row > 3){
		std::cerr << "Invalid indices: value must be be 0, 1, 2, or 3!\n";
		return;
	}
	static float dataArr[4];	//static because only want to allocate/deallocate memory once
	if(column == 0){
		_mm_store_ps(dataArr, row0);
		dataArr[column] = val;
		row0 = _mm_load_ps(dataArr);
	}
	else if(column == 1){
		_mm_store_ps(dataArr, row1);
		dataArr[column] = val;
		row1 = _mm_load_ps(dataArr);
	}
	else if(column == 2){
		_mm_store_ps(dataArr, row2);
		dataArr[column] = val;
		row2 = _mm_load_ps(dataArr);
	}
	else if(column == 3){
		_mm_store_ps(dataArr, row3);
		dataArr[column] = val;
		row3 = _mm_load_ps(dataArr);
	}
}

void Matrix4_4::set(const float *arr){
	static float temp[4];	//static because only want to allocate/deallocate memory once
	for(int i = 0; i < 4; i++){
		temp[0] = arr[4 * i];
		temp[1] = arr[4 * i + 1];
		temp[2] = arr[4 * i + 2];
		temp[3] = arr[4 * i + 3];
		if(i == 0) 	row0 = _mm_load_ps(temp);
		else if(i == 1) row1 = _mm_load_ps(temp);
		else if(i == 2) row2 = _mm_load_ps(temp);
		else if(i == 3) row3 = _mm_load_ps(temp);
	}
}

//Static functions
void Matrix4_4::identity(Matrix4_4 &returnVal){
	static float r0[] = {1, 0, 0, 0};	//static because only want to allocate/deallocate memory once
	static float r1[] = {0, 1, 0, 0};	//static because only want to allocate/deallocate memory once
	static float r2[] = {0, 0, 1, 0};	//static because only want to allocate/deallocate memory once
	static float r3[] = {0, 0, 0, 1};	//static because only want to allocate/deallocate memory once
	returnVal = Matrix4_4(r0, r1, r2, r3);
}

void Matrix4_4::push(const Matrix4_4 &m1){}

void Matrix4_4::pop(Matrix4_4 &m1){}

//Matrix math functions:
void Matrix4_4::multiply(Matrix4_4 &returnVal, const Matrix4_4 &m2){
	static __m128 temp1_0, temp1_1, temp1_2, temp1_3, temp2_0, temp2_1, temp2_2, temp2_3 __attribute__ ((aligned(16)));	//static because only want to allocate/deallocate memory once
	temp1_0 = row0;
	temp1_1 = row1;
	temp1_2 = row2;
	temp1_3 = row3;
	temp2_0 = m2.row0;
	temp2_1 = m2.row1;
	temp2_2 = m2.row2;
	temp2_3 = m2.row3;
	_MM_TRANSPOSE4_PS(temp1_0, temp1_1, temp1_2, temp1_3);
	_MM_TRANSPOSE4_PS(temp2_0, temp2_1, temp2_2, temp2_3);

	//returnVal column 0:
	returnVal.row0 = _mm_mul_ps(temp1_0, _mm_set1_ps(_mm_cvtss_f32(temp2_0)));
	returnVal.row0 = _mm_add_ps(returnVal.row0, _mm_mul_ps(temp1_1, _mm_set1_ps(_mm_cvtss_f32(_mm_shuffle_ps(temp2_0, temp2_0, 				MOV_Y_TO_X)))));
	returnVal.row0 = _mm_add_ps(returnVal.row0, _mm_mul_ps(temp1_2, _mm_set1_ps(_mm_cvtss_f32(_mm_shuffle_ps(temp2_0, temp2_0, 				MOV_Z_TO_X)))));
	returnVal.row0 = _mm_add_ps(returnVal.row0, _mm_mul_ps(temp1_3, _mm_set1_ps(_mm_cvtss_f32(_mm_shuffle_ps(temp2_0, temp2_0, 				MOV_W_TO_X)))));
	//returnVal column 1:
	returnVal.row1 = _mm_mul_ps(temp1_0, _mm_set1_ps(_mm_cvtss_f32(temp2_1)));
	returnVal.row1 = _mm_add_ps(returnVal.row1, _mm_mul_ps(temp1_1, _mm_set1_ps(_mm_cvtss_f32(_mm_shuffle_ps(temp2_1, temp2_1, 				MOV_Y_TO_X)))));
	returnVal.row1 = _mm_add_ps(returnVal.row1, _mm_mul_ps(temp1_2, _mm_set1_ps(_mm_cvtss_f32(_mm_shuffle_ps(temp2_1, temp2_1, 				MOV_Z_TO_X)))));
	returnVal.row1 = _mm_add_ps(returnVal.row1, _mm_mul_ps(temp1_3, _mm_set1_ps(_mm_cvtss_f32(_mm_shuffle_ps(temp2_1, temp2_1, 				MOV_W_TO_X)))));
	//returnVal column 2:
	returnVal.row2 = _mm_mul_ps(temp1_0, _mm_set1_ps(_mm_cvtss_f32(temp2_2)));
	returnVal.row2 = _mm_add_ps(returnVal.row2, _mm_mul_ps(temp1_1, _mm_set1_ps(_mm_cvtss_f32(_mm_shuffle_ps(temp2_2, temp2_2, 				MOV_Y_TO_X)))));
	returnVal.row2 = _mm_add_ps(returnVal.row2, _mm_mul_ps(temp1_2, _mm_set1_ps(_mm_cvtss_f32(_mm_shuffle_ps(temp2_2, temp2_2, 				MOV_Z_TO_X)))));
	returnVal.row2 = _mm_add_ps(returnVal.row2, _mm_mul_ps(temp1_3, _mm_set1_ps(_mm_cvtss_f32(_mm_shuffle_ps(temp2_2, temp2_2, 				MOV_W_TO_X)))));
	//returnVal column 3:
	returnVal.row3 = _mm_mul_ps(temp1_0, _mm_set1_ps(_mm_cvtss_f32(temp2_3)));
	returnVal.row3 = _mm_add_ps(returnVal.row3, _mm_mul_ps(temp1_1, _mm_set1_ps(_mm_cvtss_f32(_mm_shuffle_ps(temp2_3, temp2_3, 				MOV_Y_TO_X)))));
	returnVal.row3 = _mm_add_ps(returnVal.row3, _mm_mul_ps(temp1_2, _mm_set1_ps(_mm_cvtss_f32(_mm_shuffle_ps(temp2_3, temp2_3, 				MOV_Z_TO_X)))));
	returnVal.row3 = _mm_add_ps(returnVal.row3, _mm_mul_ps(temp1_3, _mm_set1_ps(_mm_cvtss_f32(_mm_shuffle_ps(temp2_3, temp2_3, 				MOV_W_TO_X)))));
	_MM_TRANSPOSE4_PS(returnVal.row0, returnVal.row1, returnVal.row2, returnVal.row3);
	
}












