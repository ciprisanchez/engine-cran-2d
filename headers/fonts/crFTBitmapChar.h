#ifndef __CRAN_FT_BITMAPCHAR_H__
#define __CRAN_FT_BITMAPCHAR_H__

#include "crPrerequisites.h"
#include "cran.h"
#include "render/crRender.h"
#include "core/crColor.h"
extern "C"{
    #include "commons.h"
}

struct FT_GlyphRec_;

const int verticesPerQuad = 4;
const int indicesPerQuad = 6;
const int compVertPos = 2;
const int compVertTex = 2;

const int WHITE = 0xffffff;
const int BLACK = 0;

// each FTBitmapChar represents a character from the fnt file
// reads paramaters from fnt file and creates textured quad   
class CranFTBitmapChar: public CranRenderable
{
public:
    //	enum { numVertices = 4 } Enum;
	CranFTBitmapChar();
	CranFTBitmapChar(int charCode);

	~CranFTBitmapChar();
    
    //
    void drawabc();
    void drawabc(FT_Face _face, CRuint *_textures, CRfloat p_x, CRfloat p_y, Color *p_color);
    void drawToBitmap(CRuint *_textures , unsigned char p_idTexture);
    void drawToScreen(FT_Face _face, CRuint *_textures, CRfloat p_x, CRfloat p_y, Color *p_color);
	void Render(int x, int y) const;
	void SetXY(int x, int y) 
	{
		m_x = x;
		m_y = y;
	}
	int GetX2() const
	{
		return m_x + m_width; 
	}
	int GetY2() const
	{
		return m_x + m_width; 
	}
	int GetXAdvance() const
	{
		return m_xAdvance;
	}
	void SetXAdvance(int xAdvance)
	{
		m_xAdvance = xAdvance;
	}
	int GetHeight() const
	{
		return m_height;
	}
	int GetTotalHeight() const
	{
		return m_yOffset + m_height;
	}
	int GetWidth() const
	{
		return m_width;
	}
	void SetSize(int width, int height)
	{
		m_width = width;
		m_height = height;
	}
	void SetOffsets(int xOffset, int yOffset)
	{
		m_xOffset = xOffset;
		m_yOffset = yOffset;
	}
	int GetYOffset() const
	{
		return m_yOffset;
	}
	void ReduceYOffset(int amount)
	{
		m_yOffset -= amount;
	}
	void AddKerning(CranFTBitmapChar* pBitmapChar, int amount);
	bool IsLoaded() const
	{
		return m_x >= 0;
	}
	int GetNumPixels() const
	{
		return m_width*m_height;
	}
	int GetCharCode() const
	{
		return m_charCode;
	}
	void SetCharCode(int charCode)
	{
		m_charCode = charCode;
	}
	void setGlyph(struct FT_GlyphRec_* pGlyph);

	bool IsEmpty() const
	{
		return m_width == 0 || m_height == 0;
	}
	void ReleaseGlyph();
	void InitTexCoords(int texWidth, int texHeight);
	int m_charCode;	// for debugging
    
    int _top;
    int _left;
    int _top2;
    int _left2;
    int _advance;
    int _bearingY;
    int _hoss;
    int _hoss2;
    int _qvws;     // Vertex width
    int _qvhs;     // Vertex height
	float _qtws;   // Texture width
    float _qths;   // Texture height
	int m_x, m_y;
	int m_width;
	int m_height;
	int m_xOffset;
	int m_yOffset;
	int m_xAdvance;
    
    FT_UInt _glyphIndex;
    
    float getCharLength();
    
private:

	
	
	float m_texCoords[verticesPerQuad*compVertTex];
	struct FT_GlyphRec_* m_pGlyph;
};

#endif /*FTBITMAPCHAR_H_*/
