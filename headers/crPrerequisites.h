#ifndef __CRAN_PREREQUISITES_H__
#define __CRAN_PREREQUISITES_H__

/****************************************
 * EXTERNAL INCLUDES
 * - png
 * - freetype
 * - zip
 *
 ****************************************/
#include "external/png/png.h"
#include "external/zip/zip.h"
#include "external/freetype/ft2build.h"
#include "external/freetype/freetype/freetype.h"
#include "external/freetype/freetype/ftglyph.h"

//*** Pre-declare classes
// Allow use of pointers in header files without including individual .h so
// decrease dependencies between files

class CranEngine;
class CranResource;
//
class CranObject;
class CranMatrix;
//
class CranGL;
class CranSprite;
class CranAnimation;
class CranScene;
class CranTexture;
class CranRenderable;
class CranTilemap;
class CranFont;
class CranFTFont;

//
class CranOpenSL;
class CranMusic;
class CranSound;

#endif
