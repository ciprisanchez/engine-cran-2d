#ifndef __CRAN_TILEMAP_H__
#define __CRAN_TILEMAP_H__

extern "C"{
	#include "commons.h"
}

#include "crPrerequisites.h"
#include "images/crSprite.h"
#include "images/crTexture.h"
#include "math/crRectangle.h"
#include <vector>
#include <cmath>

class CranTilemap: public CranSprite
{
public:
	CranTilemap();
	~CranTilemap();

	// *** About texture
	void loadTexture(const char *p_filename, int cols, int rows);

	// *** About tilemap
	void loadMap(std::vector<int> p_map, int p_rows, int p_cols);
    void updateMap(std::vector<int> p_map);         // Update map with tile to be drawn
	void setVisibleMap(int p_rows, int p_cols);		// Set rows and cols to show when map is being drawn
    void cranTilemapRender();
    void cranTilemapRenderRegion(unsigned int p_coordy, unsigned int p_coordx);
    void cranTileRender(int tilenumber, int row, int column);
    void cranTileRenderRegion(int p_tilenumber, int p_row, int p_column);

private:
    // *** Map
    std::vector<int> _map;
    int _rows;
    int _cols;
	int _visiblerows;
	int _visiblecols;
	float _rowtilesize;
	float _coltilesize;
    
    // *** Texture
    int _textureRows;
    int _textureCols;
    float _xtilesize;
    float _ytilesize;
	CRuint _textureWidth;
	CRuint _textureHeight;

    // *** Methods
	Rectangle* getTextureTileCoordinates(int tile_number);
	Rectangle* getScreenTileCoordinates(CRuint p_column, CRuint p_row);
	//
	void cranTilemapScreenLimits(int p_coordy, int p_coordx, int *p_coordy_init, int *p_coordy_end, int *p_coordx_init, int *p_coordx_end);

};

#endif


