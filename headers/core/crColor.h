#ifndef __CRAN_COLOR_H__
#define __CRAN_COLOR_H__

#include "crPrerequisites.h"
extern "C"{
    #include "commons.h"
}

class Color{
    
   public:
    Color();
	Color(CRfloat p_red, CRfloat p_green, CRfloat p_blue, CRfloat p_alpha);
	~Color();
	//
    void setValues(CRfloat p_red, CRfloat p_green, CRfloat p_blue, CRfloat p_alpha);
	//CRfloat* getColor16f();
    void getColor16f(CRfloat* p_vertexColor);
	
	CRfloat _red;
	CRfloat _green;
	CRfloat _blue;
	CRfloat _alpha;
};

#endif
