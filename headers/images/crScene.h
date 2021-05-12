#ifndef __CRAN_SCENE_H__
#define __CRAN_SCENE_H__

#include "crPrerequisites.h"
extern "C"{
	#include "commons.h"
}
#include "math/crRectangle.h"

using namespace Cran::Math;

class CranScene
{
public:
    
    CranScene();
    CranScene(Rectangle* p_rectangle);
    ~CranScene();
    //
	CRuint				_mode;
	CRuint                      _status;
	Rectangle					*_screenArea;
	CRuint						_actualFrame;
    CRuint						_speed;
	CRuint                      _speedCounter;
};


#endif
