/*****************************************************************
 * This class permits handle a texture like a sprite map.
 *
 * cranSpriteRender --> Render on screen the full texture
 * cranSpriteRenderArea	--> Rencer on screen an specified area of the texture. (Example: Tiles, ...)
 *
 *****************************************************************/
#ifndef CRAN_SPRITE_H
#define CRAN_SPRITE_H

#include "crPrerequisites.h"
#include "cran.h"
#include "render/crRender.h"
#include "math/crRectangle.h"
#include "images/crTexture.h"
extern "C"{
    #include "commons.h"
}


class CranSprite : public CranObject, public CranRenderable
{
public:
    CranSprite();
    ~CranSprite();
    
	//CRint           _idTexture;
    CRbool          _isLoaded;
	//
	CRfloat			_alphaChannel;
	
    void load(const char *p_filename);
	void draw(Rectangle *p_screenArea);
    void drawArea(Rectangle *p_screenArea, Rectangle *p_spriteArea);
    //
    void modifySpritePivot(Rectangle *p_screenArea, short p_x, short p_y);
    void rotate(CRfloat p_angleRotation, CRfloat p_x, CRfloat p_y, CRfloat p_z);
    
protected:
    float* getAreaCoordinates(Rectangle *p_screenArea);
    float* getColor(Color *p_color);

private:
    void cranSpriteTextureLoad(CranTexture *p__texture);
};
#endif
