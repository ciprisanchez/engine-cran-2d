#ifndef __CRAN_FONT_SCENE_H__
#define __CRAN_FONT_SCENE_H__

#include "crPrerequisites.h"
extern "C"{
	#include "commons.h"
}
#include "core/crColor.h"
#include "fonts/crFontFormat.h"
#include "math/crRectangle.h"
#include "util/crString.h"

using namespace Cran::Math;
using namespace Cran::Util;

class CranFontScene
{
public:
    
	CranFontScene();
    CranFontScene(Vector2* p_position, Color* p_color, CRuint p_time, CRuint p_mode, const char *p_str);
    ~CranFontScene();
    //
    void setMove(CRuint p_speedmove);
	void update();
    //
	Vector2*				_position;
	CRuint                  _actualFrame;
	CRuint                  _frames;
    CRfloat                 _speed;
	Color*					_color;
	char*					_message;
    CranFontFormat*         _format;
    
    // Effects
    CRbool                  _move;
    CRuint					_speedmove;
	CRuint					_sceneMode;
};


#endif
