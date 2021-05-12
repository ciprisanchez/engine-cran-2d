#ifndef __CRAN_MATH_MATRIX4_H__
#define __CRAN_MATH_MATRIX4_H__

#include "crPrerequisites.h"
#include "math/crMath.h"
extern "C"{
#include "commons.h"
}

namespace Cran {
	namespace Math {
        
        class Matrix4{
        public:
            Matrix4();
			~Matrix4();
			
			// *** Methods
			void zero();
			void identity();
			void translate(CRfloat p_x, CRfloat p_y, CRfloat p_z);
			void scale(CRfloat p_x, CRfloat p_y, CRfloat p_z);
			void rotate(CRfloat p_angle, CRfloat p_x, CRfloat p_y, CRfloat p_z);
			//
			float* toArray16f(float *p_fm);
			
			// *** Operators overload
			Matrix4 & operator=(const Matrix4 &p_matrix);
            Matrix4 & operator*(const Matrix4 &p_factor);
			CRbool operator==(const Matrix4 &p_matrix) const;
			CRbool operator!=(const Matrix4 &p_matrix) const;
            
		public:
			CRfloat _m11; CRfloat _m12; CRfloat _m13; CRfloat _m14; 
			CRfloat _m21; CRfloat _m22; CRfloat _m23; CRfloat _m24; 
			CRfloat _m31; CRfloat _m32; CRfloat _m33; CRfloat _m34; 
			CRfloat _m41; CRfloat _m42; CRfloat _m43; CRfloat _m44; 
        };
        
	}
}
#endif
