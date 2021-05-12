#ifndef __CRAN_ANIMATION_H__
#define __CRAN_ANIMATION_H__

#include "crPrerequisites.h"
#include "images/crSprite.h"
#include "images/crScene.h"
extern "C"{
	#include "commons.h"
}
#include <vector>


class CranAnimation: public CranSprite
{
public:
    
    CranAnimation();
    ~CranAnimation();

	// **************
	void addFrame(Rectangle *p_bounds);
	void play(Rectangle *p_screenArea, CRuint p_mode, int p_speed);
	//
   	void draw(CranScene* p_scene);
    	std::vector<CranScene*>     _vAScenes;
    
private:
	// *** Vars
	std::vector<Rectangle*>     _vFrames;
	
	// *** Methods
	void render(CranScene* p_scene);
	void reset(CranScene* p_scene);
	void stop(CranScene* p_scene);
	CRuint getStatus(CranScene* p_scene);
};

#endif
