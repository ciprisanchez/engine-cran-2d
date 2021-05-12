#ifndef __CRAN_MATH_VECTOR2_H__
#define __CRAN_MATH_VECTOR2_H__

#include "crPrerequisites.h"
extern "C"{
    #include "commons.h"
}

namespace Cran {
	namespace Math {
		class Vector2{
			public:
				Vector2();
				Vector2(CRfloat p_x, CRfloat p_y);
				~Vector2();
				
				// *** Methods
				void zero();
                void setValues(CRfloat p_x, CRfloat p_y);
				
				// *** Operators overload
                Vector2 & operator=(const Vector2 &p_vector2);
				Vector2 & operator-(const Cran::Math::Vector2 &p_vector2);
				CRbool operator==(const Cran::Math::Vector2 &p_vector2) const;

				CRfloat _x;
				CRfloat _y;
		};
	}
}
#endif
