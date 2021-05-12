#ifndef __CRAN_FONT_H__
#define __CRAN_FONT_H__

#define CR_FONT_ALIGN_LEFT		0x00
#define CR_FONT_ALIGN_CENTER	0x01
#define CR_FONT_ALIGN_RIGHT		0x02

#include "crPrerequisites.h"
#include "cran.h"
#include "fonts/crFontScene.h"
#include "render/crRender.h"
#include "math/crRectangle.h"
#include "images/crTexture.h"
#include "fonts/crFontFormat.h"
extern "C"{
	#include "commons.h"
}

//
#define CR_FONT_DEFAULT_SIZE		64.0f
#define CR_FONT_CHAR_PER_COLUMN		16
#define CR_FONT_CHAR_PER_ROW		16
//
#define CR_FONT_LETTERS_SIZE			26
#define CR_FONT_NUMBERS_SIZE			10
#define CR_FONT_SYMBOLS_SIZE			31
#define CR_FONT_EOL						1			// End of line = '\0'

using namespace Cran::Util;

class CranFont : public CranObject, public CranRenderable
{
public:
	CranFont();
    ~CranFont();

    CranFontFormat*     _ffomat;
	// *** Effects
	char			*_text;
	CRint           _idTexture;
	CRbool          _isLoaded;
    
	// *** Font
	CRbool load(const char *p_filename);
    void useFormat(CranFontFormat* p_format);
	void write(Vector2 *p_position, const char *p_str);
    void write(Vector2 *p_position, const char *p_str, int p_length);
    void write(Vector2 *p_position, const char *p_str, Color* p_color);
    void write(Vector2 *p_position, const char *p_str, Color* p_color, int p_length);

    // *** Animated text
    std::vector<CranFontScene*>     _vFScenes;
	void createAnimatedText(Vector2* p_position, Color* p_color, CRuint p_time, CRuint p_mode, char *p_str);
	void writeAnimatedText(CranFontScene* p_fontscene);
	void stopAnimatedText(CranFontScene* p_fontscene);

private:
    float* getAreaCoordinates(Rectangle *p_screenArea);
    float* getColor(Color *p_color);
    void getCharPosition(Rectangle* p_rectangle, Vector2 *p_position, int p_index);
    void getCharTexture(Rectangle *p_rectangle, int p_position_value);
};


#endif

