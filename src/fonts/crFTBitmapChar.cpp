#include "fonts/crFTBitmapChar.h"

CranFTBitmapChar::CranFTBitmapChar()
{
	m_x = 0;
	m_y = 0;
	m_width = 0;
	m_height = 0;
	m_xOffset = 0;
	m_yOffset = 0;
	m_xAdvance = 0;
	m_pGlyph = 0;
}

CranFTBitmapChar::CranFTBitmapChar(int charCode)
{
	m_x = 0;
	m_y = 0;
	m_width = 0;
	m_height = 0;
	m_xOffset = 0;
	m_yOffset = 0;
	m_xAdvance = 0;
	m_pGlyph = 0;
    initModelViewMatrix();
	setRenderFlags(CR_ATTRIB_POSITION_INDEX|CR_VERTEX_ATTRIB_COLOR|CR_VERTEX_ATTRIB_TEXCOORD0);
	m_charCode = charCode;
}

CranFTBitmapChar::~CranFTBitmapChar()
{
}

float CranFTBitmapChar::getCharLength()
{
	return m_xAdvance;
}

void CranFTBitmapChar::setGlyph(FT_Glyph p_glyph)
{
	m_pGlyph = p_glyph;
}

void CranFTBitmapChar::drawToBitmap(CRuint *_textures , unsigned char p_idTexture)
{
    // *** Freetypes variables
	FT_Bitmap bitmap;
	FT_BitmapGlyph bitmap_glyph;
    // *** Variables
	CRuint i,j;
	CRuint width, height;
	GLubyte *expanded_data;
    
	// *** Get bitmap and glyph data
    bitmap_glyph = (FT_BitmapGlyph)m_pGlyph;
	bitmap = bitmap_glyph->bitmap;
	
	// ***
	width = Cran::Math::Math::pow2(bitmap.width);
	height = Cran::Math::Math::pow2(bitmap.rows);
	
	// *** Alloc memory for texture
	expanded_data = (GLubyte *)malloc( sizeof(GLubyte)*2*width*height );    
	for (j=0; j<height;j++)
	{
		for (i=0; i<width; i++)
		{
			if ( (i>=(CRuint)bitmap.width) || (j>=(CRuint)bitmap.rows) ){
				expanded_data[2*(i+j*width)] = 0;
				expanded_data[2*(i+j*width)+1] = 0;
			} else {
				expanded_data[2*(i+j*width)] = bitmap.buffer[i+bitmap.width*j];
				expanded_data[2*(i+j*width)+1] = bitmap.buffer[i+bitmap.width*j];
			}
		}
	}
	
	// *** Load texture into memory
    glBindTexture(GL_TEXTURE_2D, _textures[p_idTexture]);
    //glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_FALSE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);	// GL_NEAREST
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);	// GL_LINEAR
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    Cran::Render::GL::crGlTexImage2D(GL_LUMINANCE_ALPHA, width, height, 0, GL_LUMINANCE_ALPHA, GL_UNSIGNED_BYTE, expanded_data);
    //
	free((void *)expanded_data);
}



void CranFTBitmapChar::drawToScreen(FT_Face _face, CRuint *_textures, CRfloat p_x, CRfloat p_y, Color *p_color)
{
	float p_vertex_data[8];
	float p_vertex_texture[8];
	float* color_values;
	
	//color_values = p_color->getColor16f();
    //color_values = p_color->getColor16f(color_values);
    p_color->getColor16f(color_values);
	//
    p_vertex_texture[6] = _qtws;
    p_vertex_texture[7] = _qths;
    p_vertex_texture[4] = 0;
    p_vertex_texture[5] = _qths;
    p_vertex_texture[2] = _qtws;
    p_vertex_texture[3] = 0;
    p_vertex_texture[0] = 0;
    p_vertex_texture[1] = 0;
	//
    p_vertex_data[0] = CranEngine::convertPxToGl(CR_AXIS_X, 0);
    p_vertex_data[1] = CranEngine::convertPxToGl(CR_AXIS_Y, -_qvhs);
    p_vertex_data[2] = CranEngine::convertPxToGl(CR_AXIS_X, _qvws);
    p_vertex_data[3] = CranEngine::convertPxToGl(CR_AXIS_Y, -_qvhs);
    p_vertex_data[4] = CranEngine::convertPxToGl(CR_AXIS_X, 0);
    p_vertex_data[5] = CranEngine::convertPxToGl(CR_AXIS_Y, 0);
    p_vertex_data[6] = CranEngine::convertPxToGl(CR_AXIS_X, _qvws);
    p_vertex_data[7] = CranEngine::convertPxToGl(CR_AXIS_Y, 0);
    
	//
	loadModelViewMatrix();
    
    _translationAMatrix->translate(p_x, p_y, 0);
    _translationBMatrix->translate(p_x, p_y, 0);
    
	updateModelViewMatrix();
    
    glBindTexture(GL_TEXTURE_2D, _textures[m_charCode]);
    //glEnable(GL_POINT_SMOOTH);
	Cran::Render::GL::crGlEnableBlending(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	render(p_vertex_data, color_values, p_vertex_texture);
	Cran::Render::GL::crGlDisableBlending();
}

void CranFTBitmapChar::InitTexCoords(int texWidth, int texHeight)
{
	float x1 = (float)m_x/(float)texWidth;
	float y1 = (float)m_y/(float)texHeight;
	float x2 = (float)(m_x+m_width)/(float)texWidth;
	float y2 = (float)(m_y+m_height)/(float)texHeight;
    
	m_texCoords[0] = x1;
	m_texCoords[1] = y1;
    
	m_texCoords[2] = x2;
	m_texCoords[3] = y1;
    
	m_texCoords[4] = x1;
	m_texCoords[5] = y2;
    
	m_texCoords[6] = x2;
	m_texCoords[7] = y2;
}

// setup quad and draw as triangle groups
void CranFTBitmapChar::Render(int x, int y) const
{
	if (IsEmpty()) return;
	x += m_xOffset;	
	y += m_yOffset;
	float vertices[verticesPerQuad*compVertPos];
	vertices[0] = (float)x;
	vertices[1] = (float)y;
    
	vertices[2] = (float)(x+m_width);
	vertices[3] = (float)y;
    
	vertices[4] = (float)x;
	vertices[5] = (float)(y+m_height);
    
	vertices[6] = (float)(x+m_width);
	vertices[7] = (float)(y+m_height);
}


void CranFTBitmapChar::ReleaseGlyph() 
{
	if (m_pGlyph) FT_Done_Glyph(m_pGlyph);
}
