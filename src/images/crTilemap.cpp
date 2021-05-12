#include "images/crTilemap.h"

using namespace Cran::Math;

CranTilemap::CranTilemap(){
	// Init model view matrix
	_color = new Color();
    initModelViewMatrix();
    _pivotInPixels = new Vector2();
	_alphaChannel = 1.0f;
    
    // Inherits methods
    setRenderFlags(CR_ATTRIB_POSITION_INDEX|CR_VERTEX_ATTRIB_TEXCOORD0);
    //
    addToResourceManager(CRAN_TILEMAP);
}

CranTilemap::~CranTilemap()
{
}

void CranTilemap::loadTexture(const char *p_filename, int cols, int rows)
{
	// The user specifies the number of rows in the texture
    _textureRows = rows;
	// The user specifies the number of cols in the texture
    _textureCols = cols;

	// Texture coordinates start in 0.0f and finish in 1.0f in x and y axis.
    _xtilesize = OPENGL_TEXTURE_SIZE / _textureCols;
	_ytilesize = OPENGL_TEXTURE_SIZE / _textureRows;

	// Load texture from a file
    //CranTexture *_ct = new CranTexture();
    _ct = new CranTexture();
    _ct->loadFromFile(p_filename);

	// Load texture into OPENGL
    _ct->loadTexture();
	_textureWidth = _ct->getWidth();
	_textureHeight = _ct->getHeight();
    
    loadModelViewMatrix();
}

void CranTilemap::loadMap(std::vector<int> p_map, int p_rows, int p_cols){
    //_data = (unsigned int **)p_data;
	_map = p_map;
    _rows = p_rows;
    _cols = p_cols;
	_visiblerows = p_rows;
	_visiblecols = p_cols;
	if ( CranEngine::isOrientationPortrait() ){
		_rowtilesize = OPENGL_SCREEN_SIZE / p_rows;
		_coltilesize = OPENGL_SCREEN_SIZE / p_cols;
	} else if ( CranEngine::isOrientationLandscape() ){
		_rowtilesize = OPENGL_SCREEN_SIZE / p_cols;
		_coltilesize = OPENGL_SCREEN_SIZE / p_rows;
	}
}

void CranTilemap::setVisibleMap(int p_visible_rows, int p_visible_cols){
	if (p_visible_rows > _rows){
		_visiblerows = _rows;
	} else {
		_visiblerows = p_visible_rows;
	}
	//
	if (p_visible_cols > _cols){
		_visiblecols = _cols;
	} else {
		_visiblecols = p_visible_cols;
	}
	//
	if ( CranEngine::isOrientationPortrait() ){
		_rowtilesize = OPENGL_SCREEN_SIZE / _visiblerows;
		_coltilesize = OPENGL_SCREEN_SIZE / _visiblecols;
	} else if ( CranEngine::isOrientationLandscape() ){
		_rowtilesize = OPENGL_SCREEN_SIZE / _visiblecols;
		_coltilesize = OPENGL_SCREEN_SIZE / _visiblerows;
	}
}

void CranTilemap::updateMap(std::vector<int> p_map){
    //_data = (unsigned int **)p_data;
    _map = p_map;
}

void CranTilemap::cranTilemapRender(){
	// Declare
    CRushort y, x;
	Rectangle *screenArea;
	Rectangle *textureArea;
	//
	for (y=0;y < _rows; y++){
		for (x=0;x < _cols; x++){
			// Get screen coordinates for tile
			screenArea = getScreenTileCoordinates(x,y);
			// Get tile number.
			int tile_value = _map[(_cols * y)+x];
			// Calc tile position.
			textureArea = getTextureTileCoordinates(tile_value);
			//
            drawArea(screenArea, textureArea);
		}
	}
}

void CranTilemap::cranTilemapRenderRegion(unsigned int p_coordy, unsigned int p_coordx){
	// Declare
    CRushort y, x;
    Rectangle *screenArea;
	Rectangle *textureArea;
	int coordy_init, coordy_end, coordx_init, coordx_end;
	// Calc
	cranTilemapScreenLimits(p_coordy, p_coordx, &coordy_init, &coordy_end, &coordx_init, &coordx_end);
	//
	for (y=coordy_init;y < coordy_end; y++){
		for (x=coordx_init;x < coordx_end; x++){
            // Get screen coordinates for tile
			screenArea = getScreenTileCoordinates(x,y);
			// Get tile number.
			int tile_value = _map[(_cols * y)+x];
			// Calc tile position.
			textureArea = getTextureTileCoordinates(tile_value);
			//
			drawArea(screenArea, textureArea);
        }
	}
	
}

void CranTilemap::cranTileRender(int p_tilenumber, int p_row, int p_column){
	// Declare
	Rectangle *screenArea;
	Rectangle *textureArea;
	//
    screenArea = getScreenTileCoordinates(p_column,p_row);
    //
    textureArea = getTextureTileCoordinates(p_tilenumber);
    //
    drawArea(screenArea, textureArea);
}

void CranTilemap::cranTileRenderRegion(int p_tilenumber, int p_row, int p_column){
	// Declare
	Rectangle *screenArea;
	Rectangle *textureArea;
	int tile_half = 0;
	int tile_distance = 0;

	//
	// Row position
	tile_half = _visiblerows / 2;
	tile_distance = _rows - p_row;
	if (tile_distance <= tile_half){
		p_row = _visiblerows - tile_distance;
	} else if (p_row >= tile_half){
		p_row = tile_half;
	}
	
	// Column position
	tile_half = _visiblecols / 2;
	tile_distance = _cols - p_column;
	if (tile_distance <= tile_half){
		p_column = _visiblecols - tile_distance;
	} else if (p_column >= tile_half){
		p_column = tile_half;
	}
	
    //
    screenArea = getScreenTileCoordinates(p_column,p_row);
    //
    textureArea = getTextureTileCoordinates(p_tilenumber);
    //
    drawArea(screenArea, textureArea);
}


// *******************************************
Rectangle* CranTilemap::getScreenTileCoordinates(CRuint p_column, CRuint p_row)
{
	Rectangle *r;
	//
	r = new Rectangle();
	CRfloat tile_width = CranEngine::getScreenWidth() / _cols;
	CRfloat tile_height = CranEngine::getScreenHeight() / _rows;
	//
	CRfloat column = tile_width * p_column;
	CRfloat row = tile_height * p_row;
	//
    r->setValues(column, row, column+tile_width, row+tile_height);
    //
	return r;
}


Rectangle* CranTilemap::getTextureTileCoordinates(int tile_number)
{
	Rectangle *rectangle;
	//
	float tile_row;
	float tile_col;
	float posx, posy, posx_final, posy_final;
    
	// Calc tile position.
	CRfloat result = (CRfloat)(tile_number / _textureCols);
	tile_row = (float)(floor(result));
    
	if (tile_row>0)	{	tile_col = tile_number - (_textureCols * tile_row);	} 
	else 			{	tile_col = (float)tile_number;}
	
	int tile_width = _textureWidth / _textureCols;
	int tile_height = _textureHeight / _textureRows;
	//
	// Calc textures coords.
	posx = tile_col * tile_width;
	posy =  tile_row * tile_height;
	posx_final = posx + tile_width;
	posy_final = posy + tile_height;
    
    rectangle = new Rectangle(posx, posy, posx_final, posy_final);
    
	return rectangle;
}

void CranTilemap::cranTilemapScreenLimits(int p_coordy, int p_coordx, int *p_coordy_init, int *p_coordy_end, int *p_coordx_init, int *p_coordx_end){
	*p_coordy_init = (int)(p_coordy - (_visiblerows/2));
	*p_coordy_end = (int)(p_coordy + (_visiblerows/2)) + 1;
	*p_coordx_init = (int)(p_coordx - (_visiblecols/2));
	*p_coordx_end = (int)(p_coordx + (_visiblecols/2)) + 1;
	if (*p_coordy_init<0){
		*p_coordy_init = 0;
		*p_coordy_end = _visiblerows;
	}
	if (*p_coordy_end >= _rows){
		*p_coordy_init = _rows - _visiblerows;
		*p_coordy_end = _rows;
	}
	if (*p_coordx_init < 0){
		*p_coordx_init = 0;
		*p_coordx_end = _visiblecols;
	}
	if (*p_coordx_end >= _cols){
		*p_coordx_init = _cols - _visiblecols;
		*p_coordx_end = _cols;
	}
}
