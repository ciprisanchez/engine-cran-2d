#include "core/crResource.h"
#include "core/crBuffer.h"
#include "fonts/crFont.h"
#include "images/crAnimation.h"
#include "images/crSprite.h"

CranResource::CranResource()
{
    n_object = 0;
    n_texture = 0;
}

CranResource::~CranResource()
{
    //
    for (std::vector<CranObject*>::iterator it = _vMusics.begin(); it!= _vMusics.end(); ++it) {
        CranMusic* cm = (CranMusic*)*it;
        delete cm;
    }
    //
    for (std::vector<CranObject*>::iterator it = _vSounds.begin(); it!= _vSounds.end(); ++it) {
        CranSound* cs = (CranSound*)*it;
        delete cs;
    }
    //
    for (std::vector<CranObject*>::iterator it = _vBuffers.begin(); it!= _vBuffers.end(); ++it) {
        CranBuffer *cb = (CranBuffer*)*it;
        delete cb;
    }
    //
    for (std::vector<CranObject*>::iterator it = _vShaders.begin(); it!= _vShaders.end(); ++it) {
        CranShader *ca = (CranShader*)*it;
        delete ca;
    }
    //
    _vSprites.clear();
    _vAnimation.clear();
    _vFonts.clear();
    _vEffect.clear();
    _vBuffers.clear();
    _vShaders.clear();
    _vMusics.clear();
    _vSounds.clear();
    _vTextures.clear();
    _vTilemaps.clear();
}

void CranResource::add(int p_type, CranObject *p_object)
{
	switch( p_type ){
		case CRAN_MUSIC:
		{
			p_object->setId(n_object++);
			_vMusics.push_back(p_object);
			break;
		}
		case CRAN_ANIMATION:
		{
			p_object->setId(n_object++);
			_vAnimation.push_back(p_object);
			break;
		}
        case CRAN_FONT:
		{
			p_object->setId(n_object++);
			_vFonts.push_back(p_object);
			break;
		}

		case CRAN_SPRITE:
		{
			p_object->setId(n_object++);
			_vSprites.push_back(p_object);
			break;
		}
		case CRAN_SHADER:
		{
			p_object->setId(n_object++);
			_vShaders.push_back(p_object);
			break;
		}
		case CRAN_SOUND:
		{
			p_object->setId(n_object++);
			_vSounds.push_back(p_object);
			break;
		}
		case CRAN_BUFFER:
		{
			p_object->setId(n_object++);
			_vBuffers.push_back(p_object);
			break;
		}
		case CRAN_TEXTURE:
		{
			p_object->setId(n_texture++);
			_vTextures.push_back(p_object);
			break;
		}
		case CRAN_TILEMAP:
		{
			p_object->setId(n_object++);
			_vTilemaps.push_back(p_object);
			break;
		}
	}
}
/*
void CranResource::add(CRresource p_type, CranObject *p_object)
{    
	switch( p_type ){
		case CRAN_SCENE:
		{
			p_object->setId(n_object++);
			_vScenes.push_back(p_object);
			break;
		}
		case CRAN_ANIMATION:
		{
			p_object->setId(n_object++);
			_vAnimation.push_back(p_object);
			break;
		}
		case CRAN_SPRITE:
		{
			p_object->setId(n_object++);
			_vSprites.push_back(p_object);
			break;
		}
        case CRAN_SHADER:
		{
			p_object->setId(n_object++);
			_vShaders.push_back(p_object);
			break;
		}
        case CRAN_SOUND:
		{
			p_object->setId(n_object++);
			_vSounds.push_back(p_object);
			break;
		}
        case CRAN_BUFFER:
		{
			p_object->setId(n_object++);
			_vBuffers.push_back(p_object);
			break;
		}
        case CRAN_TEXTURE:
		{
			p_object->setId(n_texture++);
			_vTextures.push_back(p_object);
			break;
		}
		case CRAN_TILEMAP:
		{
			p_object->setId(n_object++);
			_vTilemaps.push_back(p_object);
			break;
		}
	}
}
*/

void CranResource::remove(int p_type, CranObject *p_object)
{
	CRuint counter = 0;
	/*switch( p_type )
	{
		case CRAN_SCENE:
        {
            for (std::vector<CranObject*>::iterator it = _vScenes.begin(); it!=_vScenes.end(); ++it) {
                CranObject *_co = *it;
                if (_co->getId() == p_object->getId()){
					_vScenes.erase(it);
                    break;
                }
				counter++;
            }
        }
        break;
	}*/
}

CranObject* CranResource::get(int p_type, CRuint p_id)
{
	switch( p_type )
	{
		case CRAN_SOUND:
		{
			break;
		}
		case CRAN_TILEMAP:
		{
			break;
		}
		case CRAN_FONT:
		{
			break;
		}
		case CRAN_FONT_EFFECT:
		{
			break;
		}
		case CRAN_OBJECT:
		{
			break;
		}
		case CRAN_ANIMATION:
        {
            for (std::vector<CranObject*>::iterator it = _vAnimation.begin(); it!=_vAnimation.end(); ++it) {
                CranObject *_co = *it;
                if (_co->getId() == p_id){
                    return _co;
                }
            }
            return 0;      
        }
        case CRAN_SHADER:
        {
            for (std::vector<CranObject*>::iterator it = _vShaders.begin(); it!=_vShaders.end(); ++it) {
                CranObject *_co = *it;
                if (_co->getId() == p_id){
                    return _co;
                }
            }
            return 0;      
        }
        case CRAN_BUFFER:
        {
            for (std::vector<CranObject*>::iterator it = _vBuffers.begin(); it!=_vBuffers.end(); ++it) {
                CranObject *_co = *it;
                if (_co->getId() == p_id){
                    return _co;
                }
            }
            return 0;      
        }
        case CRAN_SPRITE:
        {
            for (std::vector<CranObject*>::iterator it = _vSprites.begin(); it!=_vSprites.end(); ++it) {
                CranObject *_co = *it;
                if (_co->getId() == p_id){
                    return _co;
                }
            }
            return 0;      
        }
        case CRAN_TEXTURE:
        {
            for (std::vector<CranObject*>::iterator it = _vTextures.begin(); it!=_vTextures.end(); ++it) {
                CranObject *_co = *it;
                if (_co->getId() == p_id){
                    printf("---------> id = %i",_co->getId());
                    return _co;
                }
            }
            return 0;      
        }
	}
    return 0;
}

CRbool CranResource::drawRenderable()
{
    CRuint i;
    // *** SPRITE ANIMATIONS
    CRbool scenesPending = CR_FALSE;
	for (std::vector<CranObject*>::iterator it = _vAnimation.begin(); it!= _vAnimation.end(); ++it) {
        CranAnimation *ca = (CranAnimation*)*it;
        for (i = 0; i < ca->_vAScenes.size(); i++){
            CranScene *cs = (CranScene*)ca->_vAScenes[i];
            ca->draw(cs);
            scenesPending = CR_TRUE;
        }
    }
    
    // *** TEXT ANIMATIONS
    
    for (std::vector<CranObject*>::iterator it = _vFonts.begin(); it!= _vFonts.end(); ++it) {
        CranFont *cf = (CranFont*)*it;
        for (i = 0; i < cf->_vFScenes.size(); i++){
            CranFontScene *cfs = (CranFontScene*)cf->_vFScenes[i];
            cf->writeAnimatedText(cfs);
            scenesPending = CR_TRUE;
        }
    }
    //
    return scenesPending;
}

void CranResource::removeRenderable()
{
	CRuint i;
	std::vector<CRuint> stoppedScenes;
	//
    if (_vAnimation.size()>0){
        for (std::vector<CranObject*>::iterator it = _vAnimation.begin(); it!= _vAnimation.end(); ++it) {
            CranAnimation *ca = (CranAnimation*)*it;
            for (i = 0; i < ca->_vAScenes.size(); i++){
                CranScene *cs = (CranScene*)ca->_vAScenes[i];
                if (cs->_status == STOP){
                    delete cs;
                    ca->_vAScenes.erase(ca->_vAScenes.begin()+i);
                }
            }
        }
    }
    //
    //
    if (_vFonts.size()>0){
        for (std::vector<CranObject*>::iterator it = _vFonts.begin(); it!= _vFonts.end(); ++it) {
            CranFont *cf = (CranFont*)*it;
            for (i = 0; i < cf->_vFScenes.size(); i++){
                CranFontScene *cfs = (CranFontScene*)cf->_vFScenes[i];
                if (cfs->_actualFrame >= cfs->_frames){
                    delete cfs;
                    cf->_vFScenes.erase(cf->_vFScenes.begin()+i);
                }
            }
        }
    }

}

CranShader* CranResource::getShader(int p_shader)
{
    for (std::vector<CranObject*>::iterator it = _vShaders.begin(); it!=_vShaders.end(); ++it) {
        CranShader *_cs = (CranShader*)*it;
        if (_cs->_shader == p_shader){
            return _cs;
        }
    }
	return 0;
}

/*
CRANanimation *cranResourceGetAnimation(CRuint p_id )
{
	return ( CRANanimation * )cranResourceGet(CRAN_ANIMATION, p_id );
}

CRANfont *cranResourceGetFont(CRuint p_id )
{
	return ( CRANfont * )cranResourceGet(CRAN_FONT, p_id );
}

CRANeffect *cranResourceGetFontEffect( CRuint p_id )
{
	return ( CRANeffect * )cranResourceGet(CRAN_FONT_EFFECT, p_id );
}

CRANftfont *cranResourceGetFTFont(CRuint p_id )
{
	return ( CRANftfont * )cranResourceGet(CRAN_FT_FONT, p_id );
}

CRANimage *cranResourceGetImage(CRuint p_id )
{
	return ( CRANimage * )cranResourceGet(CRAN_IMAGE, p_id );
}


*/
/*
#ifdef IPHONE_ENVIRONMENT
CranShader *CranResource::cranResourceGetShader(CRshader p_shader)
{
    unsigned int i = 0;
    for (std::vector<CranShader*>::iterator it = _vShaders.begin(); it!=_vShaders.end(); ++it) {
        CranShader *crs = *it;



        if (crs->_shader == p_shader){
            return crs;
        }
    }
    return 0;    
}
#endif*/
/*
CRANsprite *cranResourceGetSprite(CRuint p_id )
{
	return ( CRANsprite * )cranResourceGet(CRAN_SPRITE, p_id );
}

/*
CRANtilemap *cranResourceGetTilemap(CRuint p_id )
{
	return ( CRANtilemap * )cranResourceGet(CRAN_TILEMAP, p_id );
}
*/
