#include "images/crTexture.h"

// *** Constructor
CranTexture::CranTexture()
{
    _state = IMAGE_INITIALIZED;
    //
    glGenTextures(1, &_texture[0]); 

    //addToResourceManager(CRAN_TEXTURE);
}

// *** Destructor
CranTexture::~CranTexture()
{
    glDeleteTextures ( 1, &_texture[0] );
}

// *** Load the texture
void CranTexture::loadTexture()
{
	// Use tightly packed data
	Cran::Render::GL::crGlPixelStorei();

	// Bind the texture
    bindTexture();

	// Load the texture
	Cran::Render::GL::crGlTexImage2D(_format, _width, _height, 0, _format, GL_UNSIGNED_BYTE, _data);

	// Free data texture
	free(_data);
}

// *** Bind the texture
void CranTexture::bindTexture()
{
    Cran::Render::GL::crGlBindTexture(_texture, 0);
}

// *** Get the width and height texture
CRuint CranTexture::getWidth()
{
	return _width;
}

CRuint CranTexture::getHeight()
{
	return _height;
}

// *** Get the texture coordinates
float* CranTexture::getTextureCoordinates(Rectangle *p_spriteArea)
{
	float *texture_coordinates = ( float * ) calloc( 1, SQUARE_VERTEX2_SIZE  * sizeof( float ));

	if ( CranEngine::isOrientationPortrait() ){
		// Get the texture coordinates.
		texture_coordinates[0] = _pixelHeight * p_spriteArea->_x1;	// Vertex Bottom-Left	0.0;
		texture_coordinates[1] = _pixelWidth * (_width - p_spriteArea->_y2);

		texture_coordinates[2] = _pixelHeight * p_spriteArea->_x2;	// Vertex Bottom-Right
		texture_coordinates[3] = _pixelWidth * (_width - p_spriteArea->_y2);

		texture_coordinates[4] = _pixelHeight * p_spriteArea->_x1;	// Vertex Top-Right
		texture_coordinates[5] = _pixelWidth * (_width - p_spriteArea->_y1);

		texture_coordinates[6] = _pixelHeight * p_spriteArea->_x2;	// Vertex Top-Left
		texture_coordinates[7] = _pixelWidth * (_width - p_spriteArea->_y1);

	} else if ( CranEngine::isOrientationLandscape() ){
		// Get the texture coordinates.
		texture_coordinates[0] = _pixelWidth * p_spriteArea->_x1;	// Vertex Bottom-Left	0.0;
		texture_coordinates[1] = _pixelHeight * (_height - p_spriteArea->_y2);

		texture_coordinates[2] = _pixelWidth * p_spriteArea->_x2;	// Vertex Bottom-Right
		texture_coordinates[3] = _pixelHeight * (_height - p_spriteArea->_y2);

		texture_coordinates[4] = _pixelWidth * p_spriteArea->_x1;	// Vertex Top-Right
		texture_coordinates[5] = _pixelHeight * (_height - p_spriteArea->_y1);

		texture_coordinates[6] = _pixelWidth * p_spriteArea->_x2;	// Vertex Top-Left
		texture_coordinates[7] = _pixelHeight * (_height - p_spriteArea->_y1);
	}
	return texture_coordinates;

}

// ********************************************************************** LOAD FILE
void CranTexture::loadFromFile(const char* p_filename)
{
    getPathResource(p_filename);
    #ifdef IPHONE_ENVIRONMENT
    	_state = loadFilePNG(_filename);
	#endif
	#ifdef ANDROID_ENVIRONMENT
    	_state = loadFilePNGFromZIP(_filename);
	#endif
    _pixelWidth = OPENGL_TEXTURE_SIZE / _width;
	_pixelHeight = OPENGL_TEXTURE_SIZE / _height;
}

int CranTexture::loadFilePNG(char *p_filename)
{
	unsigned int i;

    png_byte header[CR_PNG_PRECISION];
    png_structp png_ptr;
    png_infop info_ptr;
    png_uint_32 width = 0;
    png_uint_32 height = 0;
    png_bytep *data;
    //int bitDepth = 0;
    int colorType = -1;
    //int number_of_passes = 0;

    // Open file and test for it being a png
	FILE *infile;
    infile = fopen(p_filename, "rb");

    if (!infile){
        Log::writeLogError(p_filename);
        return IMAGE_ERROR_FILE_NOT_OPENED;
    }
    // Check if it is a png file
    fread(header, 1, CR_PNG_PRECISION, infile);
    if (png_sig_cmp(header, 0, CR_PNG_PRECISION)){
    	Log::writeLogError("CranTexture - loadFilePNG - File %s is not recognized as a PNG file", p_filename);
        return IMAGE_ERROR_FILE_IS_NOT_VALID;
    }

    // Initialize stuff
    png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!png_ptr){
        Log::writeLogError("CranTexture - loadFilePNG - png_create_read_struct failed.");
        return IMAGE_ERROR_READ_STRUCT_FAILED;
    }
    //
    info_ptr = png_create_info_struct(png_ptr);
    if (!info_ptr){
        png_destroy_read_struct(&png_ptr, (png_infopp)NULL, (png_infopp)NULL);
        Log::writeLogError("CranTexture - loadFilePNG - png_create_info_struct failed.");
        return IMAGE_ERROR_INFO_STRUCT_FAILED;
    }
    //
    if (setjmp(png_jmpbuf(png_ptr))){
        png_destroy_read_struct(&png_ptr, &info_ptr, (png_infopp)NULL);
        Log::writeLogError("CranTexture - loadFilePNG - Error during init_io.");

        return IMAGE_ERROR_INIT_IO;
    }

    //
    png_init_io(png_ptr, infile);
    png_set_sig_bytes(png_ptr, CR_PNG_PRECISION);
    png_read_info(png_ptr, info_ptr);
    //
    //number_of_passes = png_set_interlace_handling(png_ptr);
    png_read_update_info(png_ptr, info_ptr);

    //
    width = png_get_image_width ( png_ptr, info_ptr );
    height = png_get_image_height ( png_ptr, info_ptr );
    //bitDepth = png_get_bit_depth ( png_ptr, info_ptr );
    colorType = png_get_color_type( png_ptr, info_ptr );
    //
    switch( colorType )
    {
        case PNG_COLOR_TYPE_GRAY:
        {
            _bits = 1;
            break;
        }
        case PNG_COLOR_TYPE_GRAY_ALPHA:
        {
            _bits = 2;
            break;
        }
        case PNG_COLOR_TYPE_RGB:
        {
            _bits = 3;
            _format = GL_RGB;
            break;
        }
        case PNG_COLOR_TYPE_RGB_ALPHA:
        {
            _bits = 4;
            _format = GL_RGBA;
            break;
        }
    }
    _width = width;
    _height = height;

    // Read file
    if (setjmp(png_jmpbuf(png_ptr))){
        Log::writeLogError("CranTexture - loadFilePNG - Error during read_image.");
        return IMAGE_ERROR_READING_FILE;
    }

    //
    _data = ( unsigned char * ) malloc( _width * _height * _bits );
    data = ( png_bytep * ) malloc( _height * sizeof( png_bytep ) );

    for (i = 0; i < ( int )_height; ++i){
        data[ i ] = ( png_bytep )( _data +( _height - ( i + 1 ) ) * _width  * _bits );
    }

    //
    png_read_image(png_ptr, data);
    png_read_end( png_ptr, NULL );

    // Clean up.
    free(data);

    // Clean up.
    png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
    fclose(infile);

    return IMAGE_OK;
}

#ifdef ANDROID_ENVIRONMENT
void png_zip_read(png_structp png_ptr, png_bytep data, png_size_t length)
{
	struct CranTexture;
	zip_file *zfp = (zip_file*) png_get_io_ptr(png_ptr);// ->io_ptr;
	zip_fread(zfp, data, length);
}

int CranTexture::loadFilePNGFromZIP(char *p_filename)
{
	unsigned int i;

    png_byte header[CR_PNG_PRECISION];
    png_structp png_ptr;
    png_infop info_ptr;
    png_uint_32 width = 0;
    png_uint_32 height = 0;
    png_bytep *data;
    //int bitDepth = 0;
    int colorType = -1;
    //int number_of_passes = 0;

    // Open file and test for it being a png
	zip_file *infile;
	infile = zip_fopen(getAPKFile(), p_filename, 0);

    if (!infile){
        Log::writeLogError("CranTexture - loadFilePNGFromZIP - File %s could not be opened for reading", p_filename);
        return IMAGE_ERROR_FILE_NOT_OPENED;
    }
    // Check if it is a png file
    zip_fread(infile, header, CR_PNG_PRECISION);
	if (png_sig_cmp(header, 0, CR_PNG_PRECISION)){
		Log::writeLogError("CranTexture - loadFilePNGFromZIP - File %s is not recognized as a PNG file", p_filename);
		return IMAGE_ERROR_FILE_IS_NOT_VALID;
	}

    // Initialize stuff
    png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!png_ptr){
    	Log::writeLogError("CranTexture - loadFilePNGFromZIP - png_create_read_struct failed.");
        return IMAGE_ERROR_READ_STRUCT_FAILED;
    }
    //
    info_ptr = png_create_info_struct(png_ptr);
    if (!info_ptr){
        png_destroy_read_struct(&png_ptr, (png_infopp)NULL, (png_infopp)NULL);
    	Log::writeLogError("CranTexture - loadFilePNGFromZIP - png_create_info_struct failed.");
        return IMAGE_ERROR_INFO_STRUCT_FAILED;
    }
    //
    if (setjmp(png_jmpbuf(png_ptr))){
        png_destroy_read_struct(&png_ptr, &info_ptr, (png_infopp)NULL);
        Log::writeLogError("CranTexture - loadFilePNGFromZIP - Error during init_io.");
        return IMAGE_ERROR_INIT_IO;
    }
    //
    //
    png_set_read_fn(png_ptr, (png_voidp)infile, png_zip_read);
    png_set_sig_bytes(png_ptr, CR_PNG_PRECISION);
    png_read_info(png_ptr, info_ptr);
    //
    //number_of_passes = png_set_interlace_handling(png_ptr);
    png_read_update_info(png_ptr, info_ptr);
    //
    width = png_get_image_width ( png_ptr, info_ptr );
    height = png_get_image_height ( png_ptr, info_ptr );
    //bitDepth = png_get_bit_depth ( png_ptr, info_ptr );
    colorType = png_get_color_type( png_ptr, info_ptr );
    //
    switch( colorType )
    {
        case PNG_COLOR_TYPE_GRAY:
        {
            _bits = 1;
            break;
        }
        case PNG_COLOR_TYPE_GRAY_ALPHA:
        {
            _bits = 2;
            break;
        }
        case PNG_COLOR_TYPE_RGB:
        {
            _bits = 3;
            _format = GL_RGB;
            break;
        }
        case PNG_COLOR_TYPE_RGB_ALPHA:
        {
            _bits = 4;
            _format = GL_RGBA;
            break;
        }
    }
    _width = width;
    _height = height;

    // Read file
    if (setjmp(png_jmpbuf(png_ptr))){
        Log::writeLogError("CranTexture - loadFilePNGFromZIP - Error during read_image.");
        return IMAGE_ERROR_READING_FILE;
    }

    //
    _data = ( unsigned char * ) malloc( _width * _height * _bits );
    data = ( png_bytep * ) malloc( _height * sizeof( png_bytep ) );

    for (i = 0; i < ( int )_height; ++i){
        data[ i ] = ( png_bytep )( _data +( _height - ( i + 1 ) ) * _width  * _bits );
    }

    //
    png_read_image(png_ptr, data);
    png_read_end( png_ptr, NULL );

    // Clean up.
    free(data);

    // Clean up.
    png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
    zip_fclose(infile);
    //
    return IMAGE_OK;
}
#endif