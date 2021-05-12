#include "fonts/crFTFont.h"
/*
const CRint CR_FT_POINTS = 16;
const CRuint CR_FT_DPI_IPHONE = 163;
const CRuint CR_FT_DPI_ANDROID = 96;
const CRuint CR_FT_DPI_WINDOWS = 96;
const CRushort CR_FT_CHARACTERS = 255;


CranFTFont::CranFTFont()
{	
    _textures = (unsigned int*)malloc(sizeof(unsigned int)* CR_FT_CHARACTERS);
    
	// *** Font size in points
	_pt = CR_FT_POINTS;
	// *** Dots per inches depends on device
	_dpi = CR_FT_DPI_IPHONE;
    
	// *** Generate textures
	glGenTextures(CR_FT_CHARACTERS, _textures);
	//
    addToResourceManager(CRAN_FONT);
}

// *** Destructor
CranFTFont::~CranFTFont()
{
	FT_Done_Face(_face);
	//
	glDeleteTextures(CR_FT_CHARACTERS,_textures);
}

// ********************************************************************************** Load data
#ifdef IPHONE_ENVIRONMENT
CRbool CranFTFont::loadFont(const char *p_filename)
{
    FT_Error error;
	unsigned char i;
	//
	getPathResource(p_filename);
    
	// *** Load the font from the file
	if (FT_New_Face(CranEngine::Instance()->getFTLibrary(), _filename, 0, &(_face)))
	{
		//cranLogError("cranFTFontLoad", "Error on load new face");
		return CR_FALSE;
	}
	
    // *** Select charmap
    //error = FT_Select_Charmap( _face, FT_ENCODING_UNICODE );
    //if( error )
    //{
    //FT_Done_Face( _face );
    //return CR_FALSE;
    //}
    
    // *** Set char size
	// Freetype measures fonts in 64ths of pixels, 6 left bit(pt<<6), multiplies the pt size by 64.
	error = FT_Set_Char_Size( _face, _pt<<6,_pt<<6, _dpi, _dpi);
    if( error )
    {
        FT_Done_Face( _face );
        return CR_FALSE;
    }
    
	// Create glyph texture
    it=mapGlyph.begin();
	for (i=0; i<CR_FT_CHARACTERS; i++)
	{
		if (!createGlyphTexture(i))
		{
			FT_Done_Face(_face);
            //
            glDeleteTextures(CR_FT_CHARACTERS,_textures);
		}
	}
	return CR_TRUE;
}
#endif

#ifdef ANDROID_ENVIRONMENT
CRbool CranFTFont::loadFont(const char *p_filename)
{
    FT_Error error;
	unsigned char i;

	// *** Use asset manager to open asset by filename
    AAssetManager* manager = AAssetManager_fromJava(CranEngine::getJavaEnvironment(), CranEngine::getAssetManager());
	//AAsset* fontFile = AAssetManager_open(manager, p_filename, AASSET_MODE_UNKNOWN);
	AAsset* fontFile = AAssetManager_open(manager, p_filename, AASSET_MODE_BUFFER);
	
	// *** The asset might not be found
    if (fontFile == NULL) {
    	Log::writeLogError("CranFTFont - loadFont - Error, the asset might not be found");
        return CR_FALSE;
    }
	
	// *** Get data buffer of font file
	const void* fontData = AAsset_getBuffer(fontFile);
	off_t fontLen = AAsset_getLength(fontFile);
	
	// *** Create font from memory loaded data
	if (FT_New_Memory_Face(CranEngine::Instance()->getFTLibrary(), (FT_Byte*)fontData, (FT_Long)fontLen, 0, &_face)) {
		Log::writeLogError("cranFTFontLoad - loadFont - Error loading new face");
		return CR_FALSE;
	} else {
		Log::writeLogInfo("cranFTFontLoad - loadFont - Font loaded");
	}
    AAsset_close(fontFile);

    // *** Select charmap
	//error = FT_Select_Charmap( _face, FT_ENCODING_UNICODE );
	//if( error )
	//{
	//	Log::writeLogError("cranFTFontLoad - loadFont - Error selecting charmap");
	//	FT_Done_Face( _face );
	//	return CR_FALSE;
	//}
    
	Log::writeLogError("aaaaaaaa 2");
    // *** Set char size
	// Freetype measures fonts in 64ths of pixels, 6 left bit(pt<<6), multiplies the pt size by 64.
	error = FT_Set_Char_Size( _face, _pt<<6,_pt<<6, _dpi, _dpi);
    if( error )
    {
		Log::writeLogError("cranFTFontLoad - loadFont - Error setting char size");
        FT_Done_Face( _face );
        return CR_FALSE;
    }
    
    Log::writeLogError("aaaaaaaa 3");
	// *** Create glyph texture
    it = mapGlyph.begin();
	for (i=0; i<CR_FT_CHARACTERS; i++)
	{
		Log::writeLogError("aaaaaaaa 34");
		if (!createGlyphTexture(i))
		{
			Log::writeLogError("cranFTFontLoad - loadFont - Error creating glyph texture");
			FT_Done_Face(_face);
            //
            glDeleteTextures(CR_FT_CHARACTERS,_textures);
		}
	}
	Log::writeLogError("aaaaaaaa 4");
	return CR_TRUE;
}
#endif

CRbool CranFTFont::createGlyphTexture(unsigned char ch)
{

	#ifdef ANDROID_ENVIRONMENT

	// *** Freetypes variables
	FT_Glyph glyph;
    FT_GlyphSlot slot;
	FT_Bitmap bitmap;
	FT_BitmapGlyph bitmap_glyph;

	// *** Variables
	CRuint width, height;

	Log::writeLogError("aaaaaaaa 5a");
	LOGD("aaaa->>> %d",_face->num_glyphs);
	LOGD("aaaa2->>> %c", ch);
	LOGD("aaaa3->>> %i", ch);
	FT_UInt gindex;
	Log::writeLogError("aaaaaaaa 5Ba");
	LOGD("total --> %d",_face->num_glyphs);

	for (FT_ULong charcode=FT_Get_First_Char(_face, &gindex);   gindex != 0;   charcode=FT_Get_Next_Char(_face, charcode, &gindex)) {
		Log::writeLogError("aaaaaaaa 5Ba");
	}
	Log::writeLogError("aaaaaaaa 5B");

	// *** Load glyph data
	if ( FT_Load_Glyph(_face, FT_Get_Char_Index(_face,ch), FT_LOAD_TARGET_LIGHT) ){
		Log::writeLogError("cranFTFontLoad - createGlyphTexture - Error loading glyph");
		return CR_FALSE;
	}

	Log::writeLogError("aaaaaaaa 6");
	// *** Get glyph data
    if ( FT_Get_Glyph(_face->glyph, &glyph) ){
		Log::writeLogError("cranFTFontLoad - createGlyphTexture - Error getting glyph");
		return CR_FALSE;
	}

    Log::writeLogError("aaaaaaaa 7");
	// *** Transform glyph to bitmap
    FT_Glyph_To_Bitmap(&glyph, FT_RENDER_MODE_LIGHT, 0, 1);

	// *** Get bitmap and glyph data
    slot = _face->glyph;
    bitmap_glyph = (FT_BitmapGlyph)glyph;
	bitmap = bitmap_glyph->bitmap;

	Log::writeLogError("aaaaaaaa 8");
	// ***
    width = Cran::Math::Math::pow2(bitmap.width);
	height = Cran::Math::Math::pow2(bitmap.rows);

    //*** Set glyph data
    if (ch == 113){
        int a = 10;
        a = a+1;
    }
    Log::writeLogError("aaaaaaaa 9");
    CranFTBitmapChar *bitmapChar = new CranFTBitmapChar(ch);
    bitmapChar->setGlyph(glyph);
    bitmapChar->drawToBitmap(_textures, ch);
    bitmapChar->_top = slot->bitmap_top;
    bitmapChar->_left = slot->bitmap_left;
    bitmapChar->_top2 = bitmap_glyph->top;
    bitmapChar->_left2 = bitmap_glyph->left;
    bitmapChar->m_charCode = ch;
    bitmapChar->_glyphIndex = FT_Get_Char_Index(_face, ch);
    bitmapChar->_qvws = bitmap.width;
    bitmapChar->_qvhs = bitmap.rows;
    bitmapChar->_qtws = (float)bitmap.width/(float)width;
    bitmapChar->_qths = (float)bitmap.rows/(float)height;
    bitmapChar->_advance = (float)(_face->glyph->advance.x>>6);
    bitmapChar->_bearingY = (float)(_face->glyph->metrics.horiBearingY>>6);
    bitmapChar->_hoss = (float)((_face->glyph->metrics.horiBearingY - _face->glyph->metrics.height)>>6);
    //
    mapGlyph.insert (it, std::pair<unsigned char,CranFTBitmapChar*>(ch,bitmapChar) );

	#endif
	#ifdef IPHONE_ENVIRONMENT

	// *** Freetypes variables
	FT_Glyph glyph;
    FT_GlyphSlot slot;
	FT_Bitmap bitmap;
	FT_BitmapGlyph bitmap_glyph;
	
	// *** Variables
	CRuint width, height;
	// *** Load glyph data
	if ( FT_Load_Glyph(_face, FT_Get_Char_Index(_face,ch), FT_LOAD_TARGET_LIGHT) ){
		Log::writeLogError("cranFTFontLoad - createGlyphTexture - Error loading glyph");
		return CR_FALSE;
	}
	
	Log::writeLogError("aaaaaaaa 6");
	// *** Get glyph data
    if ( FT_Get_Glyph(_face->glyph, &glyph) ){
		Log::writeLogError("cranFTFontLoad - createGlyphTexture - Error getting glyph");
		return CR_FALSE;
	}
	
    Log::writeLogError("aaaaaaaa 7");
	// *** Transform glyph to bitmap
    FT_Glyph_To_Bitmap(&glyph, FT_RENDER_MODE_LIGHT, 0, 1);
    
	// *** Get bitmap and glyph data
    slot = _face->glyph;
    bitmap_glyph = (FT_BitmapGlyph)glyph;
	bitmap = bitmap_glyph->bitmap;
	
	Log::writeLogError("aaaaaaaa 8");
	// ***
    width = Cran::Math::Math::pow2(bitmap.width);
	height = Cran::Math::Math::pow2(bitmap.rows);
	
    //*** Set glyph data
    if (ch == 113){
        int a = 10;
        a = a+1;
    }
    Log::writeLogError("aaaaaaaa 9");
    CranFTBitmapChar *bitmapChar = new CranFTBitmapChar(ch);
    bitmapChar->setGlyph(glyph);
    bitmapChar->drawToBitmap(_textures, ch);
    bitmapChar->_top = slot->bitmap_top;
    bitmapChar->_left = slot->bitmap_left;
    bitmapChar->_top2 = bitmap_glyph->top;
    bitmapChar->_left2 = bitmap_glyph->left;
    bitmapChar->m_charCode = ch;
    bitmapChar->_glyphIndex = FT_Get_Char_Index(_face, ch);
    bitmapChar->_qvws = bitmap.width;
    bitmapChar->_qvhs = bitmap.rows;
    bitmapChar->_qtws = (float)bitmap.width/(float)width;
    bitmapChar->_qths = (float)bitmap.rows/(float)height;
    bitmapChar->_advance = (float)(_face->glyph->advance.x>>6);
    bitmapChar->_bearingY = (float)(_face->glyph->metrics.horiBearingY>>6);
    bitmapChar->_hoss = (float)((_face->glyph->metrics.horiBearingY - _face->glyph->metrics.height)>>6);
    //
    mapGlyph.insert (it, std::pair<unsigned char,CranFTBitmapChar*>(ch,bitmapChar) );
	#endif
	return CR_TRUE;
}


// ********************************************************************************** Draw to screen
void CranFTFont::draw(CRfloat p_x, CRfloat p_y, Color *p_color, CRftAlign p_align, char *text)
{
    FT_UInt glyph_previous;
    FT_Bool isKerning;
    FT_Vector vKerning;
    
    // *** Declares
    Vector2 *vPosition;
    char text_aux[CRAN_STRING_MAX_SIZE];
    char *character;
    unsigned char ch;
    
    // *** Init
    vKerning.x = 0;
    vKerning.y = 0;
    vPosition = new Vector2(p_x, p_y);
    glyph_previous = 0;
    isKerning = FT_HAS_KERNING(_face);
    
    // *** Start process
    if (p_align == CR_FT_RIGHT){
        String::reverse(text_aux, text);
    } else {
        String::copy(text_aux, text);
    }
    
    for (character=text_aux; *character; character++)
    {
        ch = *character;
        it = mapGlyph.find(ch);
        CranFTBitmapChar *cft = it->second; 
        
        // *** Get kerning data of character
        if (isKerning && glyph_previous && cft->_glyphIndex){
            if (p_align == CR_FT_RIGHT){
                FT_Get_Kerning(_face, cft->_glyphIndex, glyph_previous, FT_KERNING_DEFAULT , &vKerning);
            } else {
                FT_Get_Kerning(_face, glyph_previous, cft->_glyphIndex, FT_KERNING_DEFAULT , &vKerning);
            }
        }
        
        int pr1 = (_pt - cft->_qvhs);
        int pr2 = vPosition->_y + pr1 - (cft->_hoss);
        //
        if (p_align == CR_FT_LEFT){
            vPosition->_x += vKerning.x>>6;
        } else if (p_align == CR_FT_RIGHT){
            vPosition->_x -= vKerning.x>>6;
            vPosition->_x -= cft->_advance;
        }
        
        //
        float x = CranEngine::convertPxToTxGl(CR_AXIS_X, vPosition->_x + cft->_left2);
        float y = CranEngine::convertPxToTxGl(CR_AXIS_Y, -(vPosition->_y - cft->_hoss));//
        //
        cft->drawToScreen(_face, _textures, x, y, p_color);
        //
        glyph_previous = cft->_glyphIndex;
        if (p_align == CR_FT_LEFT){
            vPosition->_x += cft->_advance;
        }
        //*****************************************************
    }
}

// ********************************************************************************** Get / Set data
float CranFTFont::getTextLength(char *text)
{
	float length = 0;
	char *character = text;
	for (; *character; character++){
		it = mapGlyph.find(*character);
		length += it->second->getCharLength();
	}
	return length;
}

void CranFTFont::setSize(CRint p_size)
{
	_pt = p_size;
}
*/