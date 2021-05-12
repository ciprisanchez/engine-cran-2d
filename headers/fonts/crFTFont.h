#ifndef __CRAN_FT_FONT_H__
#define __CRAN_FT_FONT_H__

#include <map>
#include "crPrerequisites.h"
#include "cran.h"
#include "render/crRender.h"
#include "fonts/crFTBitmapChar.h"

extern "C"{
	#include "commons.h"
}

using namespace Cran::Util;

class CranFTFont : public CranObject
{    
public:
    
	CranFTFont();
    ~CranFTFont();
	// 
	CRbool loadFont(const char *p_filename);
	// 
    void draw(CRfloat p_x, CRfloat p_y, Color *p_color, CRftAlign p_align, char *text);
	//
	void setSize(CRint p_size);
    float getTextLength(char *text);
    
private:
	FT_Face			_face;
	CRint			_pt;	// Size in points
	CRuint			_dpi;	// Dots per inch
	CRuint			*_textures;
    //
    std::map<unsigned char,CranFTBitmapChar*> mapGlyph;
    std::map<unsigned char,CranFTBitmapChar*>::iterator it;
    std::pair<std::map<unsigned char,CranFTBitmapChar*>::iterator,bool> ret;
    
	// *** Methods
	CRbool createGlyphTexture(unsigned char ch);
	
};

#endif

