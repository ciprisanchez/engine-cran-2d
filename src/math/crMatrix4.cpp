#include "math/crMatrix4.h"

using namespace Cran::Math;

Matrix4::Matrix4()
{
}

Matrix4::~Matrix4()
{
}

void Matrix4::zero()
{
	_m11 = 0; _m12 = 0; _m13 = 0; _m14 = 0; 
	_m21 = 0; _m22 = 0; _m23 = 0; _m24 = 0; 
	_m31 = 0; _m32 = 0; _m33 = 0; _m34 = 0; 
	_m41 = 0; _m42 = 0; _m43 = 0; _m44 = 0;
}

void Matrix4::identity()
{
	_m11 = 1; _m12 = 0; _m13 = 0; _m14 = 0; 
	_m21 = 0; _m22 = 1; _m23 = 0; _m24 = 0; 
	_m31 = 0; _m32 = 0; _m33 = 1; _m34 = 0; 
	_m41 = 0; _m42 = 0; _m43 = 0; _m44 = 1;
}

void Matrix4::translate(CRfloat p_x, CRfloat p_y, CRfloat p_z)
{
    /*
	_m11 = 1; 	_m12 = 0; 	_m13 = 0; 	_m14 = p_x; 
	_m21 = 0; 	_m22 = 1; 	_m23 = 0; 	_m24 = p_y; 
	_m31 = 0; 	_m32 = 0; 	_m33 = 1; 	_m34 = p_z; 
	_m41 = 0;	_m42 = 0;	_m43 = 0;	_m44 = 1;
     */
    
    _m11 = 1; 	_m12 = 0; 	_m13 = 0; 	_m14 = 0; 
	_m21 = 0; 	_m22 = 1; 	_m23 = 0; 	_m24 = 0; 
	_m31 = 0; 	_m32 = 0; 	_m33 = 1; 	_m34 = 0; 
	_m41 = p_x;	_m42 = p_y;	_m43 = p_z;	_m44 = 1;
}

void Matrix4::scale(CRfloat p_x, CRfloat p_y, CRfloat p_z)
{
	_m11 = p_x;	_m12 = 0;	_m13 = 0;	_m14 = 0; 
	_m21 = 0;	_m22 = p_y;	_m23 = 0;	_m24 = 0; 
	_m31 = 0;	_m32 = 0;	_m33 = p_z;	_m34 = 0; 
	_m41 = 0;	_m42 = 0;	_m43 = 0;	_m44 = 1;
}

void Matrix4::rotate(CRfloat p_angle, CRfloat p_x, CRfloat p_y, CRfloat p_z)
{
    //
	// OPENGL Kronos implementation
	//
	// *** Convert degrees to radians
	//float angle = p_angle * PI_OVER_180;
	// *** Calc matrix rotation
	//m[0] = 1+(1-cos_result)*(p_x*p_x-1);          m[4] = p_z*sin(angle)+(1-cos(angle))*p_x*p_y;  m[8] = -p_y*sin(angle)+(1-cos(angle))*p_x*p_z; m[12] = 0;
	//m[1] = -p_z*sin(angle)+(1-cos(angle))*p_x*p_y;m[5] = 1+(1-cos(angle))*(p_y*p_y-1);           m[9] = p_x*sin(angle)+(1-cos(angle))*p_y*p_z;  m[13] = 0;
	//m[2] = p_y*sin(angle)+(1-cos(angle))*p_x*p_z; m[6] = -p_x*sin(angle)+(1-cos(angle))*p_y*p_z; m[10] = 1+(1-cos(angle))*(p_z*p_z-1);          m[14] = 0;
	//m[3] = 0;                                     m[7] = 0;                                      m[11] = 0;                                     m[15] = 1;
	
	//
	// More simple implementation and ¿optime?
	//
	float radians = (float)(p_angle * CR_PI_OVER_180);
	float cos_result = (float)(cos(radians));
	float sin_result = (float)(sin(radians));
	//
	//
	if (p_x != 0){
		_m11 = 1;	_m12 = 0;			_m13 = 0;			_m14 = 0;
		_m21 = 0;	_m22 = cos_result;	_m23 = sin_result;	_m24 = 0;
		_m31 = 0;	_m32 = -sin_result;	_m33 = cos_result;	_m34 = 0; 
		_m41 = 0;	_m42 = 0;			_m43 = 0;			_m44 = 1;
	}
	//
	if (p_y != 0){
		_m11 = cos_result;	_m12 = 0;	_m13 = sin_result; 	_m14 = 0;
		_m21 = 0;			_m22 = 1;	_m23 = 0;			_m24 = 0;
		_m31 = -sin_result;	_m32 = 0;	_m33 = cos_result;	_m34 = 0; 
		_m41 = 0;			_m42 = 0;	_m43 = 0;			_m44 = 1; 
	}
	//
	if (p_z != 0){
		_m11 = cos_result;	_m12 = -sin_result;	_m13 = 0;   _m14 = 0;
		_m21 = sin_result;	_m22 = cos_result;	_m23 = 0;   _m24 = 0;
		_m31 = 0;			_m32 = 0;			_m33 = 1;   _m34 = 0; 
		_m41 = 0;			_m42 = 0;			_m43 = 0;   _m44 = 1; 
	}
	//
}

Matrix4 & Matrix4::operator=(const Matrix4 &p_matrix)
{
    _m11 = p_matrix._m11;
	_m12 = p_matrix._m12;
	_m13 = p_matrix._m13;
	_m14 = p_matrix._m14;
	//
	_m21 = p_matrix._m21;
	_m22 = p_matrix._m22;
	_m23 = p_matrix._m23;
	_m24 = p_matrix._m24;
	//
	_m31 = p_matrix._m31;
	_m32 = p_matrix._m32;
	_m33 = p_matrix._m33;
	_m34 = p_matrix._m34;
	//
	_m41 = p_matrix._m41;
	_m42 = p_matrix._m42;
	_m43 = p_matrix._m43;
	_m44 = p_matrix._m44;
    //
    return *this;
}

Matrix4 & Matrix4::operator*(const Matrix4 &p_factor)
{
    Matrix4* matrix = new Matrix4();
	//
	matrix->_m11 = (_m11 * p_factor._m11) + (_m12 * p_factor._m21) + (_m13 * p_factor._m31) + (_m14 * p_factor._m41);
	matrix->_m12 = (_m11 * p_factor._m12) + (_m12 * p_factor._m22) + (_m13 * p_factor._m32) + (_m14 * p_factor._m42);
	matrix->_m13 = (_m11 * p_factor._m13) + (_m12 * p_factor._m23) + (_m13 * p_factor._m33) + (_m14 * p_factor._m43);
	matrix->_m14 = (_m11 * p_factor._m14) + (_m12 * p_factor._m24) + (_m13 * p_factor._m34) + (_m14 * p_factor._m44);
	//
	matrix->_m21 = (_m21 * p_factor._m11) + (_m22 * p_factor._m21) + (_m23 * p_factor._m31) + (_m24 * p_factor._m41);
	matrix->_m22 = (_m21 * p_factor._m12) + (_m22 * p_factor._m22) + (_m23 * p_factor._m32) + (_m24 * p_factor._m42);
	matrix->_m23 = (_m21 * p_factor._m13) + (_m22 * p_factor._m23) + (_m23 * p_factor._m33) + (_m24 * p_factor._m43);
	matrix->_m24 = (_m21 * p_factor._m14) + (_m22 * p_factor._m24) + (_m23 * p_factor._m34) + (_m24 * p_factor._m44);
	//
	matrix->_m31 = (_m31 * p_factor._m11) + (_m32 * p_factor._m21) + (_m33 * p_factor._m31) + (_m34 * p_factor._m41);
	matrix->_m32 = (_m31 * p_factor._m12) + (_m32 * p_factor._m22) + (_m33 * p_factor._m32) + (_m34 * p_factor._m42);
	matrix->_m33 = (_m31 * p_factor._m13) + (_m32 * p_factor._m23) + (_m33 * p_factor._m33) + (_m34 * p_factor._m43);
	matrix->_m34 = (_m31 * p_factor._m14) + (_m32 * p_factor._m24) + (_m33 * p_factor._m34) + (_m34 * p_factor._m44);
	//
	matrix->_m41 = (_m41 * p_factor._m11) + (_m42 * p_factor._m21) + (_m43 * p_factor._m31) + (_m44 * p_factor._m41);
	matrix->_m42 = (_m41 * p_factor._m12) + (_m42 * p_factor._m22) + (_m43 * p_factor._m32) + (_m44 * p_factor._m42);
	matrix->_m43 = (_m41 * p_factor._m13) + (_m42 * p_factor._m23) + (_m43 * p_factor._m33) + (_m44 * p_factor._m43);
	matrix->_m44 = (_m41 * p_factor._m14) + (_m42 * p_factor._m24) + (_m43 * p_factor._m34) + (_m44 * p_factor._m44);

    this->operator=(*matrix);   //*this = *matrix;
    //
    delete matrix;
    //
	return *this;
}

float* Matrix4::toArray16f(float *p_floatPointer)
{
	p_floatPointer = ( float * ) calloc( 1, sizeof(float)*16 );
	//
	p_floatPointer[0] = _m11;
	p_floatPointer[1] = _m12;
	p_floatPointer[2] = _m13;
	p_floatPointer[3] = _m14;
	p_floatPointer[4] = _m21;
	p_floatPointer[5] = _m22;
	p_floatPointer[6] = _m23;
	p_floatPointer[7] = _m24;
	p_floatPointer[8] = _m31;
	p_floatPointer[9] = _m32;
	p_floatPointer[10] = _m33;
	p_floatPointer[11] = _m34;
	p_floatPointer[12] = _m41;
	p_floatPointer[13] = _m42;
	p_floatPointer[14] = _m43;
	p_floatPointer[15] = _m44;
	//
	return p_floatPointer;
}
