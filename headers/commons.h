#ifndef __CRAN_COMMONS_H__
#define __CRAN_COMMONS_H__

//***************************************
// CRAN TYPES DEFINITIONS
//***************************************
 #define CRNULL						0
 //
typedef unsigned int uint32;
typedef unsigned short uint16;
typedef unsigned char uint8;
typedef int CRint;
typedef short CRshort;
typedef unsigned int CRuint;
typedef unsigned short CRushort;
typedef unsigned char CRuchar;
typedef float CRfloat;
typedef enum { CR_FALSE = (0), CR_TRUE = !CR_FALSE } CRbool;
typedef enum { CR_ORIENTATION_PORTRAIT, CR_ORIENTATION_LANDSCAPE} CRorientation;
typedef enum { CR_STRING_LZEROES } CR_STRING;
typedef enum { CR_FT_LEFT, CR_FT_CENTER, CR_FT_RIGHT } CRftAlign;
typedef enum { CR_AXIS_X, CR_AXIS_Y } CRaxis;
//typedef enum { STOP, PLAYING, PAUSED } CRstatusAnimation;
//typedef enum { NOREPEAT, LOOP } CR_SCENE_MODE;

#define NOREPEAT            0x00
#define LOOP                0x01

#define STOP		0x00
#define PLAYING     0x01
#define PAUSED		0x02

#define CR_FONT_ALIGN_LEFT		0x00
#define CR_FONT_ALIGN_CENTER	0x01
#define CR_FONT_ALIGN_RIGHT		0x02

/*
typedef enum
{
	CR_SHADER_NONE,
	CR_SHADER_2D,
    CR_SHADER_COLOR

} CRshader;
*/


#define FONT_TO_TRANSPARENT		0x1
#define FONT_TO_COLOR			0x2


#define CR_SHADER_NONE					0x00
#define CR_SHADER_2D					0x01
#define CR_SHADER_COLOR					0x02
//
#define CRAN_OBJECT					0x00
#define CRAN_BUFFER					0x01
#define CRAN_TEXTURE				0x02
#define CRAN_IMAGE					0x03
#define CRAN_SPRITE					0x04
#define CRAN_ANIMATION				0x05
#define CRAN_FONT					0x06
#define CRAN_FT_FONT				0x07
#define CRAN_FONT_EFFECT			0x08
#define CRAN_SHADER					0x0A
#define CRAN_SOUND					0x0B
#define CRAN_MUSIC					0x0C
#define CRAN_TILEMAP				0x0D
#define CRAN_RESOURCE_ALL			0x0E

#define IMAGE_INITIALIZED			0x00
#define IMAGE_OK					0x01
#define IMAGE_ERROR_FILE_NOT_OPENED	0x02
#define IMAGE_ERROR_FILE_IS_NOT_VALID	0x03
#define IMAGE_ERROR_READ_STRUCT_FAILED	0x04
#define IMAGE_ERROR_INFO_STRUCT_FAILED	0x05
#define IMAGE_ERROR_INIT_IO				0x06
#define IMAGE_ERROR_READING_FILE		0x07
#define IMAGE_ERROR_BUFFERING_IMAGE		0x08

//************************************************************************************************************************
// Preprocessor directives depending on enviroment development. 
// 1.- Define < #define WINDOWS_ENVIRONMENT > if you use VSTUDIO 2010 EXPRESS EDITION
// 2.- Define < #define IPHONE_ENVIRONMENT > if you use XCODE4, for IPhone development
// 3.- Define < #define ANDROID_ENVIRONMENT > if you use ECLIPSE, for Android development. NOT IMPLEMENTED.
//
// You must define at least one of them in your preprocessor directives.
//************************************************************************************************************************

//***************************************
// WINDOWS
//***************************************
#ifdef WINDOWS_ENVIRONMENT
// **** WINDOWS
#include <windows.h>		// Header File For Windows

// **** OPENGL
#include <gl/gl.h>			// Opengl 1.x 
#include <gl/glu.h>			// Header File For The GLu32 Library

// **** RESOLUTION
#define RESOLUTION_DEFAULT_WIDTH			768.0f
#define RESOLUTION_DEFAULT_HEIGHT			1024.0f

#endif



//***************************************
// IPHONE
//***************************************
#ifdef IPHONE_ENVIRONMENT

// **** UNIX HEADERS - UNIX BASED SYSTEMS
//#include <unistd.h>
//#include <dirent.h>

// **** OPENGL
#include <OpenGLES/ES1/gl.h>
#include <OpenGLES/ES1/glext.h>
#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>

// **** RESOLUTION
#define RESOLUTION_XIB_WIDTH			320.0f
#define RESOLUTION_XIB_HEIGHT           480.0f
#define RESOLUTION_IPHONE_WIDTH			640.0f
#define RESOLUTION_IPHONE_HEIGHT		960.0f
#define RESOLUTION_IPAD_WIDTH			768.0f
#define RESOLUTION_IPAD_HEIGHT			1024.0f

#endif


//***************************************
// ANDROID
//***************************************
#ifdef ANDROID_ENVIRONMENT

#define CRAN_DEBUG_HIGH

// **** ANDROID - Native asset manager
#include <sys/types.h>
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>

// **** OPENGL ES 2.0
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

// *** OPENLSL ES - NATIVE AUDIO
#include <SLES/OpenSLES.h>
#include <SLES/OpenSLES_Android.h>

#endif



//************************************************************************************************************************
// COMMON ENGINE CONSTANTS DEFINITIONS
//
//************************************************************************************************************************

//**********************************************
// OPENGL
//
// Top Left		---> -1.0, +1.0		// x, y
// Top Right	---> +1.0, +1.0		// x, y
// Bottom Right ---> +1.0, -1.0		// x, y
// Bottom Left	---> -1.0, -1.0		// x, y
// Screen map coordinates:
//            +y
//            |
//            |
//  -x <---- 0,0 ----> +x
//            |
//            |
//            -y
//
//**********************************************
#define OPENGL_COORD_UP					+1.0f	// OpenGL coordinates - UP
#define OPENGL_COORD_BOTTOM				-1.0f	// OpenGL coordinates - BOTTOM
#define OPENGL_COORD_LEFT				-1.0f	// OpenGL coordinates - LEFT
#define OPENGL_COORD_RIGHT				+1.0f	// OpenGL coordinates - RIGHT

#define OPENGL_SCREEN_SIZE              2.0f	// From -1.0f to 1.0f
#define OPENGL_TEXTURE_SIZE				1.0f	// From 0.0f to 1.0f

//************************************************************************
// FREETYPE CONSTANTS
//
//************************************************************************
#define CR_FREETYPE_VERSION				"2.4.5"

//************************************************************************
// PNG CONSTANTS
//
//************************************************************************
#define CR_PNG_VERSION                	"1.5.5"
#define CR_PNG_PRECISION                8

//************************************************************************
// CRAN RENDER CONSTANTS
//
//************************************************************************
// **** SHADER attributes
#define CR_ATTRIB_POSITION              "position"					
#define CR_ATTRIB_COLOR                 "color"
#define CR_ATTRIB_TEXCOORD0				"textureCoordIn"

#define CR_ATTRIB_POSITION_INDEX		0
#define CR_ATTRIB_COLOR_INDEX           1
#define CR_ATTRIB_TEXCOORD0_INDEX		2

#define CR_VERTEX_ATTRIB_COLOR			1
#define CR_VERTEX_ATTRIB_TEXCOORD0		2
#define CR_VERTEX_ATTRIB_TEXCOORD1		3
#define CR_VERTEX_ATTRIB_NORMAL			4

#define TRIANGLE_VERTEX_COUNT			3
#define SQUARE_VERTEX_COUNT				4
#define SQUARE_VERTEX2_SIZE				SQUARE_VERTEX_COUNT * VERTEX_POS_SIZE_XY
#define SQUARE_VERTEX3_SIZE				SQUARE_VERTEX_COUNT * VERTEX_POS_SIZE_XYZ

#define CRAN_2DVERTEX_ATTRIB_SIZE		VERTEX_POS_SIZE_XYZ + \
										VERTEX_COLOR_SIZE + \
										VERTEX_TEXCOORD0_SIZE + \
										VERTEX_TEXCOORD1_SIZE

#define VERTEX_POS_SIZE_XY				2		// x and y
#define VERTEX_POS_SIZE_XYZ				3		// x, y and z
#define VERTEX_NORMAL_SIZE				3		// x, y and z
#define VERTEX_COLOR_SIZE				4		// r, g, b, a
#define VERTEX_TEXCOORD_SIZE			2 		// s and t

// **** CONSTANTS
#define CRAN_STRING_BLANK				""
#define CRAN_STRING_MAX_SIZE			256
#define CRAN_STRING_MAX_SIZE_LONG		1024
#define CRAN_MAX_CHAR					256
#define CRAN_MAX_BIGCHAR				4096
#define CRAN_TEXTURES_MAX				50
#define CRAN_ANIMATIONS_MAX				200
#define CRAN_FRAMEBUFFERS_MAX			8
#define CRAN_FRAMEBUFFERS_TEXTURES_MAX	4

// **************** C INCLUDES
#include <ctype.h>
#include <math.h>
#include <string.h>
#include <time.h>

#endif
