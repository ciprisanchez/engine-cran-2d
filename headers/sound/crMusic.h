#ifndef __CRAN_MUSIC_H__
#define __CRAN_MUSIC_H__

#include "crPrerequisites.h"
#include "cran.h"
extern "C"{
    #include "commons.h"
}

class CranMusic : public CranObject
{
	
public:
	CranMusic();
	~CranMusic();
	//
    void play();
	void pause();
	void resume();
	void stop();
	void clean();
	//
	CRbool isPlaying();

#ifdef IPHONE_ENVIRONMENT
    void prepare(const char* p_filename);
#endif
    
#ifdef ANDROID_ENVIRONMENT
    void prepare(SLEngineItf p_engineEngine, SLObjectItf p_outputMixObject, const char* p_filename);
    
private:

    
	// *** File descriptor player interfaces
	SLObjectItf				fdPlayerObject;
	SLPlayItf				fdPlayerPlay;
	SLSeekItf				fdPlayerSeek;
	SLBufferQueueItf		_bufferQueueItf;
	SLBufferQueueState		_bufferQueueState;
    
#endif
};

#endif
