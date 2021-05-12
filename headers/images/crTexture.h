#ifndef __CRAN_TEXTURE_H__
#define __CRAN_TEXTURE_H__

#include "crPrerequisites.h"
extern "C"{
    #include "commons.h"
}
#include "cran.h"
#include "core/crObject.h"
#include "math/crRectangle.h"

using namespace Cran::Math;

class CranTexture : public CranObject
{
public:
	static void loadTexture(const char* p_filename);

    CranTexture();
    ~CranTexture();

    // *** Methods
    void loadFromFile(const char* p_filename);
    void loadTexture();
    void bindTexture();
	//
    float* getTextureCoordinates(Rectangle *p_spriteArea);
	CRuint getWidth();
	CRuint getHeight();
    //
    unsigned int 		_texture[1];
	int					_idTexture;

private:
	// *** Class data
	int                 _state;
	CRfloat				_pixelWidth;
	CRfloat				_pixelHeight;

	// *** File data
    CRuint				_width;
    CRuint				_height;
    unsigned char		_bits;
    CRuint				_format;
    CRuint				_flags;
    unsigned char		*_data;
	
	// *** Methods
    int loadFilePNG(char *p_filename);
    int loadFilePNGFromZIP(char *p_filename);
};

#endif

