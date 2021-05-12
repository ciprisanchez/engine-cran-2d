#ifndef CRAN_RESOURCE_H
#define CRAN_RESOURCE_H

#include "crPrerequisites.h"
#include <vector>
extern "C"{
	#include "commons.h"
}
#include "render/crShader.h"

class CranResource
{
public:
    CranResource();
    ~CranResource();
    
	std::vector<CranObject*>    _vSprites;
	std::vector<CranObject*>    _vAnimation;
	
	std::vector<CranObject*>    _vFonts;
	std::vector<CranObject*>    _vEffect;
    std::vector<CranObject*>    _vBuffers;
    std::vector<CranObject*>    _vShaders;
    std::vector<CranObject*>    _vMusics;
    std::vector<CranObject*>    _vSounds;
    std::vector<CranObject*>    _vTextures;
	std::vector<CranObject*>    _vTilemaps;

	//
    //void add(CRresource p_type, CranObject *p_object);
    void add(int p_type, CranObject *p_object);
    void remove(int p_type, CranObject *p_object);
    CranObject *get(int p_type, CRuint p_id);
    //
	CRbool drawRenderable();
    void removeRenderable();
	CranShader* getShader(int p_shader);

//unsigned int cranResourceAddShader(CranShader *p_object);
    
//

private:
    unsigned int            n_object;
    unsigned int			n_texture;
};

#endif
