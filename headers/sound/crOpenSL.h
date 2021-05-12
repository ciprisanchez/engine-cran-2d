#ifndef __CRAN_OPENSL_H__
#define __CRAN_OPENSL_H__

#include "crPrerequisites.h"
extern "C"{
    #include "commons.h"
}
#include "sound/crMusic.h"
#include "sound/crSound.h"

class CranOpenSL
{
	
public:
	static CranOpenSL* Instance(); 
	//
	static void createEngine();
	static CranMusic* createMusic(const char* p_filename);
	static CranSound* createSound(const char* p_filename);
	//static void play(const char* p_filename);
	static void clean();

protected:
	CranOpenSL();
	CranOpenSL(const CranEngine &);
	~CranOpenSL();
    
private:
	// *** Static methods
	static void createEngineIPhone();
	static void createEngineAndroid();
	
	// *** Static data
	static CranOpenSL*          			_instance;

#ifdef ANDROID_ENVIRONMENT
	// *** Engine interfaces
	static SLObjectItf						engineObject;
	static SLEngineItf						engineEngine;

	// *** Output mix interfaces
	static SLObjectItf						outputMixObject;
	static SLEnvironmentalReverbItf			outputMixEnvironmentalReverb;

	// *** Aux effect on the output mix, used by the buffer queue player
	static const SLEnvironmentalReverbSettings reverbSettings;
	
	// *** Buffer queue player interfaces
	static SLObjectItf						bqPlayerObject;
	static SLPlayItf						bqPlayerPlay;
	static SLAndroidSimpleBufferQueueItf	bqPlayerBufferQueue;
	static SLEffectSendItf					bqPlayerEffectSend;
#endif
    
	// ***
	static short		*nextBuffer;
	static unsigned		nextSize;
	static int			nextCount;
};

#endif
