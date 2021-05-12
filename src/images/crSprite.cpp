#include "images/crSprite.h"

CranSprite::CranSprite()
{
    // Init model view matrix
	_color = new Color(0.0f, 0.0f, 0.0f, 1.0f);
    _ct = new CranTexture();
    _alphaChannel = 1.0f;
    //
    initModelViewMatrix();
	
    // Inherits methods
    setRenderFlags(CR_ATTRIB_POSITION_INDEX|CR_VERTEX_ATTRIB_TEXCOORD0);
    //addToResourceManager(CRAN_SPRITE);
}

CranSprite::~CranSprite()
{
    delete _color;
    delete _ct;
}

void CranSprite::load(const char *p_filename)
{	
    // Load texture from a file
    _ct->loadFromFile(p_filename);

	// Load texture into OPENGL
    _ct->loadTexture();

	loadModelViewMatrix();
    _isLoaded = CR_TRUE;
}

void CranSprite::rotate(CRfloat p_angleRotation, CRfloat p_x, CRfloat p_y, CRfloat p_z)
{
    _rotationMatrix->rotate(p_angleRotation, p_x, p_y, p_z);
}

/*
 * Modify pivot point of sprite image. Note:
 * - If this method isn't called the pivot point will be the center of the screen.
 * - If this method is called the pivot point will be (0 + p_x, 0 + p_y).
 */
void CranSprite::modifySpritePivot(Rectangle *p_screenArea, short p_x, short p_y)
{
	// Init
    Vector2 *pivot = new Vector2();
    Vector2 *pivotInPixels = new Vector2();
	
	// Calc data
	if ( CranEngine::isOrientationPortrait() ){
		float x_screen = (((p_screenArea->_x2 - p_screenArea->_x1)/2)+p_x) + p_screenArea->_x1;
		float y_screen = (((p_screenArea->_y2 - p_screenArea->_y1)/2)+p_y) + p_screenArea->_y1;
        float x = CranEngine::convertPxToGl(CR_AXIS_X, x_screen);//p_x  *  (1.0f/ getScreenHeight());
        float y = CranEngine::convertPxToGl(CR_AXIS_Y, y_screen);//p_y  *  (1.0f/ getScreenHeight());
		//float x = (x_screen * getPixelWidth()) - 1.0f;
		//float y = (y_screen * getPixelHeight()) + 1.0f;
        pivot->setValues(x,y);
        pivotInPixels->setValues(x_screen, y_screen);
        
        // Update data
        _translationAMatrix->translate( -pivot->_x, -pivot->_y, 0.0f);
        _translationBMatrix->translate( pivot->_x, pivot->_y, 0.0f);
        //
        delete pivot;
        delete pivotInPixels;

	} else if ( CranEngine::isOrientationLandscape() ){
		float x_screen = (((p_screenArea->_x2 - p_screenArea->_x1)/2)+p_x) + p_screenArea->_x1;
		float y_screen = (((p_screenArea->_y2 - p_screenArea->_y1)/2)+p_y) + p_screenArea->_y1;
        float x = CranEngine::convertPxToGl(CR_AXIS_X, x_screen);//p_x  *  (1.0f/ getScreenHeight());
        float y = CranEngine::convertPxToGl(CR_AXIS_Y, y_screen);//p_y  *  (1.0f/ getScreenHeight());
		//float x = (x_screen * getPixelWidth()) - 1.0f;
		//float y = (y_screen * getPixelHeight()) + 1.0f;
        pivot->setValues(x,y);
        pivotInPixels->setValues(x_screen, y_screen);
        
        // Update data
        _translationAMatrix->translate( -pivot->_x, -pivot->_y, 0.0f);
        _translationBMatrix->translate( pivot->_x, pivot->_y, 0.0f);
        //
        delete pivot;
        delete pivotInPixels;
	}
}

void CranSprite::draw(Rectangle *p_screenArea)
{	
	// *** Init
	Rectangle *sprite_area;
    float *screen_coordinates;
    float *texture_coordinates;
	float *color_values;

	// *** Load
    sprite_area = new Rectangle( 0, 0, (CRfloat)_ct->getWidth(), (CRfloat)_ct->getHeight());
    //
	screen_coordinates = getAreaCoordinates(p_screenArea);
    texture_coordinates = _ct->getTextureCoordinates(sprite_area);
	color_values = getColor(_color);
	
	// Render
    _ct->bindTexture();
    
    updateModelViewMatrix();
    render(screen_coordinates, color_values, texture_coordinates);
		
    // *** Clean
    delete sprite_area;
    free(color_values);
	free(texture_coordinates);
	free(screen_coordinates);
}

void CranSprite::drawArea(Rectangle *p_screenArea, Rectangle *p_spriteArea)
{
	// *** Init
    float *screen_coordinates;
    float *texture_coordinates;
	float *color_values;

    //CranTexture *ct = (CranTexture*)getFromResourceManager(CRAN_TEXTURE, _idTexture);
	// *** Load
    Rectangle *rectScreen = new Rectangle( 0, 0, (CRfloat)_ct->getWidth(), (CRfloat)_ct->getHeight());
    if (p_spriteArea->operator<=(*rectScreen)){
        // *** Load
		screen_coordinates = getAreaCoordinates(p_screenArea);
        texture_coordinates = _ct->getTextureCoordinates(p_spriteArea);
		//color_values = getColorValues();
		color_values = getColor(_color);
        
        
		// Render
        _ct->bindTexture();
        
        Log::writeLogDebug("updateModelViewMatrix SPRITE");
        updateModelViewMatrix();
        render(screen_coordinates, color_values, texture_coordinates);
        
        // *** Clean
		free(color_values);
		free(texture_coordinates);
        free(screen_coordinates);
    }
    delete rectScreen;
	/*if (result){
        
	}*/
}

// ********************************************************************** PRIVATE funtions
// *******************************************************************************************
float* CranSprite::getAreaCoordinates(Rectangle *p_screenArea)
{
	float *screen_coordinates = ( float * ) calloc( 1, SQUARE_VERTEX2_SIZE  * sizeof( float ));

    screen_coordinates[0] = CranEngine::convertPxToGl(CR_AXIS_X, p_screenArea->_x1);
	screen_coordinates[1] = CranEngine::convertPxToGl(CR_AXIS_Y, p_screenArea->_y2);
	
	screen_coordinates[2] = CranEngine::convertPxToGl(CR_AXIS_X, p_screenArea->_x2);
	screen_coordinates[3] = CranEngine::convertPxToGl(CR_AXIS_Y, p_screenArea->_y2);
	
	screen_coordinates[4] = CranEngine::convertPxToGl(CR_AXIS_X, p_screenArea->_x1);
	screen_coordinates[5] = CranEngine::convertPxToGl(CR_AXIS_Y, p_screenArea->_y1);
	
	screen_coordinates[6] = CranEngine::convertPxToGl(CR_AXIS_X, p_screenArea->_x2);
	screen_coordinates[7] = CranEngine::convertPxToGl(CR_AXIS_Y, p_screenArea->_y1);
    
	// Get the screen coordinates
    /*
	screen_coordinates[0] = (getPixelWidth() * p_screenArea->_x1) - 1.0f;	// Vertex Bottom-Left
	screen_coordinates[1] = (getPixelHeight() * p_screenArea->_y2) + 1.0f;	//
	
	screen_coordinates[2] = (getPixelWidth() * p_screenArea->_x2) - 1.0f;	// Vertex Bottom-Right
	screen_coordinates[3] = (getPixelHeight() * p_screenArea->_y2) + 1.0f;	//
	
	screen_coordinates[4] = (getPixelWidth() * p_screenArea->_x1) - 1.0f;	// Vertex Top-Left
	screen_coordinates[5] = (getPixelHeight()* p_screenArea->_y1) + 1.0f;	
	
	screen_coordinates[6] = (getPixelWidth() * p_screenArea->_x2) - 1.0f;	// Vertex Top-Right
	screen_coordinates[7] = (getPixelHeight() * p_screenArea->_y1) + 1.0f;
	*/
	return screen_coordinates;
}

float* CranSprite::getColor(Color *p_color)
{
	float *color_values = ( float * ) calloc( 1, 16  * sizeof( float ));

	// Get the color coordinates
	color_values[0] = p_color->_red;
	color_values[1] = p_color->_green;
	color_values[2] = p_color->_blue;
	color_values[3] = p_color->_alpha;
	//
	color_values[4] = p_color->_red;
	color_values[5] = p_color->_green;
	color_values[6] = p_color->_blue;
	color_values[7] = p_color->_alpha;
	//
	color_values[8] = p_color->_red;
	color_values[9] = p_color->_green;
	color_values[10] = p_color->_blue;
	color_values[11] = p_color->_alpha;
	//
	color_values[12] = p_color->_red;
	color_values[13] = p_color->_green;
	color_values[14] = p_color->_blue;
	color_values[15] = p_color->_alpha;
	
	return color_values;
}
