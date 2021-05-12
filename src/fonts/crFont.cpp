#include "fonts/crFont.h"

const char letters [CR_FONT_LETTERS_SIZE+CR_FONT_EOL] = {"abcdefghijklmnopqrstuvwxyz"};
const char numbers [CR_FONT_NUMBERS_SIZE+CR_FONT_EOL] = {"0123456789"};
const char symbols [CR_FONT_SYMBOLS_SIZE+CR_FONT_EOL] = {" !#$%&'()*+,-./:;<=>?@[]^_€{}"};
int symbols_value[CR_FONT_SYMBOLS_SIZE] = {32, 33, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 58, 59, 60, 61, 62, 63, 64, 91, 93, 94, 95, 128, 123, 125};
int numbers_value[CR_FONT_NUMBERS_SIZE] = {48, 49, 50, 51, 52, 53, 54, 55, 56, 57 };
int letters_value[CR_FONT_LETTERS_SIZE] = {65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90};


// ********************************************************************** PUBLIC funtions
// *******************************************************************************************************
CranFont::CranFont()
{	
	_idTexture = -1;
    _ct = new CranTexture();
	 //
    initModelViewMatrix();
	
    // Inherits methods
    setRenderFlags(CR_ATTRIB_POSITION_INDEX|CR_VERTEX_ATTRIB_COLOR|CR_VERTEX_ATTRIB_TEXCOORD0);
    //addToResourceManager(CRAN_FONT);
}

// *** Destructor
CranFont::~CranFont()
{
    delete _ct;
}

CRbool CranFont::load(const char *p_filename)
{ 
	// Load texture from a file
    _ct->loadFromFile(p_filename);

	// Load texture into OPENGL
    _idTexture = _ct->getId();
    _ct->loadTexture();
	
	loadModelViewMatrix();
    _isLoaded = CR_TRUE;
    return CR_TRUE;
}


void CranFont::createAnimatedText(Vector2* p_position, Color* p_color, CRuint p_time, CRuint p_mode, char *p_str)
{
    CranFontScene* cs = new CranFontScene(p_position, p_color, p_time, p_mode, p_str);	
    cs->setMove(10);
    //
	_vFScenes.push_back(cs);
}

void CranFont::writeAnimatedText(CranFontScene* p_fontscene)
{
    if (p_fontscene->_actualFrame < p_fontscene->_frames)
	{	
        CranEngine::Instance()->useShader(CR_SHADER_COLOR);
        useFormat(p_fontscene->_format);
		write(p_fontscene->_position, p_fontscene->_message, p_fontscene->_color);
        p_fontscene->update();
        CranEngine::Instance()->useShader(CR_SHADER_2D);

	} else {
		stopAnimatedText(p_fontscene);
	}

}

void CranFont::stopAnimatedText(CranFontScene* p_fontscene)
{
    
}

void CranFont::useFormat(CranFontFormat* p_format)
{
    _ffomat = p_format;
}

void CranFont::write(Vector2 *p_position, const char *p_str)
{
    Color* color = new Color(0.0f, 0.0f, 0.0f, 1.0f);
    //
	write( p_position, p_str, color, String::length(p_str) );
    //
    delete color;
}

void CranFont::write(Vector2 *p_position, const char *p_str, int p_length)
{
    Color* color = new Color(0.0f, 0.0f, 0.0f, 1.0f);
    //
    write(p_position, p_str, color, p_length);
    //
    delete color;
}

void CranFont::write(Vector2 *p_position, const char *p_str, Color* p_color)
{
    write(p_position, p_str, p_color, String::length(p_str));
}

void CranFont::write(Vector2 *p_position, const char *p_str, Color* p_color, int p_length)
{
	// *** Declare
	Rectangle* character_texture;
	Rectangle* character_position;
	float *screen_coordinates;
	float *texture_coordinates;
	float *color_values;
	char str[CRAN_STRING_MAX_SIZE];
	int i, z;
	
	// *** Process
	if (_ffomat->_align == CR_FONT_ALIGN_LEFT){
		String::copy(str, CRAN_STRING_BLANK);
	    String::reverse(str, p_str);
	} else {
		String::copy(str, CRAN_STRING_BLANK);
	    String::concat(str, p_str);
	}

	i = 0;
	// *** Process - Loop the string
	while( i < p_length && str[i])
	{
		// *** SYMBOLS
		z = 0;
		while( z < CR_FONT_SYMBOLS_SIZE )
		{
			if (str[ i ] == symbols[z] ){
				//
                character_texture = new Rectangle();
                character_position = new Rectangle();
                //
                getCharPosition(character_position, p_position, i);
				getCharTexture(character_texture, symbols_value[z]);
				//
				screen_coordinates = getAreaCoordinates(character_position);
				texture_coordinates = _ct->getTextureCoordinates(character_texture);
				color_values = getColor(p_color);
	
				// Render
				_ct->bindTexture();
    
				updateModelViewMatrix();
				render(screen_coordinates, color_values, texture_coordinates);

				// *** Clean
                delete character_texture;
                delete character_position;
				free(color_values);
				free(texture_coordinates);
				free(screen_coordinates);
            }
			z++;
		}
		// *** NUMBERS 
		z = 0;
		while( z < CR_FONT_NUMBERS_SIZE )
		{
			if (str[ i ] == numbers[z] ){
                character_texture = new Rectangle();
                character_position = new Rectangle();
                //
				getCharPosition(character_position, p_position, i);
				getCharTexture(character_texture, numbers[z]);
				//
				screen_coordinates = getAreaCoordinates(character_position);
				texture_coordinates = _ct->getTextureCoordinates(character_texture);
				color_values = getColor(p_color);
	
				// Render
				_ct->bindTexture();
    
				updateModelViewMatrix();
				render(screen_coordinates, color_values, texture_coordinates);

				// *** Clean
                delete character_texture;
                delete character_position;
				free(color_values);
				free(texture_coordinates);
				free(screen_coordinates);
			}
			z++;
		}
		// *** LETTERS
		z = 0;
		while( z < CR_FONT_LETTERS_SIZE )
		{
			if (str[ i ] == letters[z] ){
                character_texture = new Rectangle();
                character_position = new Rectangle();
                //
                getCharPosition(character_position, p_position, i);
                getCharTexture(character_texture, letters[z]);
                //
				screen_coordinates = getAreaCoordinates(character_position);
				texture_coordinates = _ct->getTextureCoordinates(character_texture);
				color_values = getColor(p_color);
	
				// Render
				_ct->bindTexture();
    
				updateModelViewMatrix();
				render(screen_coordinates, color_values, texture_coordinates);

				// *** Clean
                delete character_texture;
                delete character_position;
				free(color_values);
				free(texture_coordinates);
				free(screen_coordinates);
			}
			z++;
		}
		i++;
	} // End main loop
	//
}


// ********************************************************************** PRIVATE funtions
// *******************************************************************************************
void CranFont::getCharTexture(Rectangle *p_rectangle, int p_position_value)
{
	int row, column;
	CRfloat x1, y1, x2, y2;
	//
	row = (p_position_value / CR_FONT_CHAR_PER_COLUMN);
	column = p_position_value - (row * CR_FONT_CHAR_PER_COLUMN);
	//
	x1 = column * CR_FONT_DEFAULT_SIZE;
	y1 = row * CR_FONT_DEFAULT_SIZE;
	x2 = x1 + CR_FONT_DEFAULT_SIZE;
	y2 = y1 + CR_FONT_DEFAULT_SIZE;
	//
	p_rectangle->setValues(x1, y1, x2, y2);
}

void CranFont::getCharPosition(Rectangle* p_rectangle, Vector2 *p_position, int p_index)
{
	float position = 0;
	//

	_ffomat->_gap = 13;
	_ffomat->_size = CR_FONT_DEFAULT_SIZE;
	if (_ffomat->_align == CR_FONT_ALIGN_LEFT){
		position = p_position->_x - (_ffomat->_gap * p_index);
		p_rectangle->setValues(position - _ffomat->_size, (CRfloat)(p_position->_y), position,  (CRfloat)(p_position->_y+_ffomat->_size));
	//} else if (_ffomat->_align == CR_FONT_ALIGN_CENTER){
	} else if (_ffomat->_align == CR_FONT_ALIGN_RIGHT){
		position = p_position->_x + (_ffomat->_gap * p_index);
		p_rectangle->setValues(position, (CRfloat)(p_position->_y), position+_ffomat->_size,  (CRfloat)(p_position->_y+_ffomat->_size));
	} else {
        p_rectangle->setValues(0.0f, 0.0f, 0.0f, 0.0f);
    }
}


// ********************************************************************** PRIVATE funtions
// *******************************************************************************************
float* CranFont::getAreaCoordinates(Rectangle *p_screenArea)
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
    
	return screen_coordinates;
}

float* CranFont::getColor(Color *p_color)
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


