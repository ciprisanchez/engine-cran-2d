#ifndef __CRAN_MATH_RECTANGLE_H__
#define __CRAN_MATH_RECTANGLE_H__

#include "crPrerequisites.h"
extern "C"{
    #include "commons.h"
}
#include "math/crVector2.h"

namespace Cran {
    namespace Math {
    class Rectangle{
        public:
            Rectangle();
			Rectangle(CRfloat p_x1, CRfloat p_y1, CRfloat p_x2, CRfloat p_y2);
			~Rectangle();
			
            // *** Methods
            void setValues(CRfloat p_x1, CRfloat p_y1, CRfloat p_x2, CRfloat p_y2);
            CRbool isInside(Vector2 *p_vector);
        
			// *** Operators overload
			Rectangle & operator=(const Rectangle &p_rectangle);
			CRbool operator==(const Rectangle &p_rectangle) const;
			CRbool operator!=(const Rectangle &p_rectangle) const;
			CRbool operator>(const Rectangle &p_rectangle) const;
			CRbool operator<(const Rectangle &p_rectangle) const;
			CRbool operator>=(const Rectangle &p_rectangle) const;
			CRbool operator<=(const Rectangle &p_rectangle) const;

			CRfloat _x1;
			CRfloat _x2;
			CRfloat _y1;
			CRfloat _y2;
	};
    }
}
#endif
