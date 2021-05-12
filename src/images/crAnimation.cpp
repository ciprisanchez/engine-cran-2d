#include "images/crAnimation.h"

CranAnimation::CranAnimation()
{
    initModelViewMatrix();
    //
    addToResourceManager(CRAN_ANIMATION);
}

CranAnimation::~CranAnimation()
{
}

void CranAnimation::addFrame(Rectangle *p_bounds)
{	
	_vFrames.push_back(p_bounds);
}

void CranAnimation::play(Rectangle *p_screenArea, CRuint p_mode, int p_speed)
{
    CranScene* cs = new CranScene();
    cs->_screenArea->setValues(p_screenArea->_x1, p_screenArea->_y1, p_screenArea->_x2, p_screenArea->_y2);
	cs->_mode = p_mode;
	cs->_status = PLAYING;
	// Animation speed
	cs->_speedCounter = 0;
	cs->_speed = p_speed;
    //
	_vAScenes.push_back(cs);
    //
}

CRuint CranAnimation::getStatus(CranScene* p_scene)
{
	return p_scene->_status;
}

void CranAnimation::draw(CranScene* p_scene)
{
	if (p_scene->_actualFrame < _vFrames.size())
	{		
		render(p_scene);
	} else if (p_scene->_mode == LOOP){
		reset(p_scene);
        render(p_scene);
	} else {
		stop(p_scene);
	}
}


void CranAnimation::render(CranScene* p_scene)
{
	Rectangle* boundsSprite = _vFrames.at(p_scene->_actualFrame);
	//
	if (p_scene->_speedCounter >= p_scene->_speed)
	{
		p_scene->_speedCounter = 0;
        drawArea(p_scene->_screenArea, boundsSprite);
		p_scene->_actualFrame++;
        
	} else {
		p_scene->_speedCounter++;
        drawArea(p_scene->_screenArea, boundsSprite);
	}
}

void CranAnimation::stop(CranScene* p_scene)
{
	p_scene->_speedCounter = 0;
	p_scene->_status = STOP;
	//delete p_scene;
}

void CranAnimation::reset(CranScene* p_scene)
{
	p_scene->_actualFrame = 0;
}

