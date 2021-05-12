#include "sound/crOpenSL.h"

using namespace Cran::Util;

// *** Define static vars
CranOpenSL* CranOpenSL::_instance;
#ifdef ANDROID_ENVIRONMENT
SLObjectItf CranOpenSL::engineObject = NULL;
SLEngineItf CranOpenSL::engineEngine = NULL;
SLObjectItf CranOpenSL::outputMixObject = NULL;
SLEnvironmentalReverbItf CranOpenSL::outputMixEnvironmentalReverb = NULL;
const SLEnvironmentalReverbSettings CranOpenSL::reverbSettings = SL_I3DL2_ENVIRONMENT_PRESET_STONECORRIDOR;
SLObjectItf CranOpenSL::bqPlayerObject = NULL;
SLPlayItf CranOpenSL::bqPlayerPlay = NULL;
SLAndroidSimpleBufferQueueItf CranOpenSL::bqPlayerBufferQueue = NULL;
SLEffectSendItf CranOpenSL::bqPlayerEffectSend = NULL;
#endif
short* CranOpenSL::nextBuffer =	(short *) NULL;
unsigned CranOpenSL::nextSize = 0;
int CranOpenSL::nextCount = 0;

// ********************************************************************** STATIC METHODS
// *******************************************************************************************
CranOpenSL* CranOpenSL::Instance()
{
    if (_instance == 0){
        _instance = new CranOpenSL();
    }
    return _instance;

}

// ********************************************************************** STATIC METHODS
// *******************************************************************************************
// *** Constructor of the class
CranOpenSL::CranOpenSL()
{
	CranOpenSL::createEngine();
}

// *** Destructor
CranOpenSL::~CranOpenSL()
{
	clean();
}

void CranOpenSL::createEngine()
{
	Log::writeLogDebug("CranRenderable - START createEngine");
	//
	#ifdef IPHONE_ENVIRONMENT
    createEngineIPhone();
	#endif
	#ifdef ANDROID_ENVIRONMENT
	createEngineAndroid();
	#endif
	//
	Log::writeLogDebug("CranRenderable - END createEngine");
	
}

void CranOpenSL::createEngineIPhone()
{
	#ifdef IPHONE_ENVIRONMENT
    crInitSoundManager();
	#endif
}

void CranOpenSL::createEngineAndroid()
{
	#ifdef ANDROID_ENVIRONMENT
	SLresult result;
	
	//SLEngineOption EngineOption[] = {(SLuint32) SL_ENGINEOPTION_THREADSAFE, (SLuint32) SL_BOOLEAN_TRUE};
    // create engine
	result = slCreateEngine(&engineObject, 0, NULL, 0, NULL, NULL);
	if (result != SL_RESULT_SUCCESS){
		Log::writeLogError("CranOpenSL - createEngine - Error creating engine");
		return;
	}

    // *** Realize the engine
    result = (*engineObject)->Realize(engineObject, SL_BOOLEAN_FALSE);
    if (result != SL_RESULT_SUCCESS){
    	Log::writeLogError("CranOpenSL - createEngine - Error realizing");
    	return;
    }

    // *** Get the engine interface, which is needed in order to create other objects
    result = (*engineObject)->GetInterface(engineObject, SL_IID_ENGINE, &engineEngine);
    if (result != SL_RESULT_SUCCESS){
		Log::writeLogError("CranOpenSL - createEngine - Error getting interface");
		return;
	}

    // *** Create output mix, with environmental reverb specified as a non-required interface
    const SLInterfaceID ids[1] = {SL_IID_ENVIRONMENTALREVERB};
    const SLboolean req[1] = {SL_BOOLEAN_FALSE};
    result = (*engineEngine)->CreateOutputMix(engineEngine, &outputMixObject, 1, ids, req);
    if (result != SL_RESULT_SUCCESS){
		Log::writeLogError("CranOpenSL - createEngine - Error creating output mix");
		return;
	}

    // *** Realize the output mix
    result = (*outputMixObject)->Realize(outputMixObject, SL_BOOLEAN_FALSE);
    if (result != SL_RESULT_SUCCESS){
		Log::writeLogError("CranOpenSL - createEngine - Error realizing");
		return;
	}

    // *** Get the environmental reverb interface
    // this could fail if the environmental reverb effect is not available,
    // either because the feature is not present, excessive CPU load, or
    // the required MODIFY_AUDIO_SETTINGS permission was not requested and granted
    result = (*outputMixObject)->GetInterface(outputMixObject, SL_IID_ENVIRONMENTALREVERB, &outputMixEnvironmentalReverb);
    if (result != SL_RESULT_SUCCESS){
    	Log::writeLogError("CranOpenSL - createEngine - Error getting interface");
    	return;
	} else {
		result = (*outputMixEnvironmentalReverb)->SetEnvironmentalReverbProperties(outputMixEnvironmentalReverb, &reverbSettings);
		// *********** ignore unsuccessful result codes for environmental reverb, as it is optional for this example ***********
	}
    //
	#endif
}

CranMusic* CranOpenSL::createMusic(const char* p_filename)
{
	Log::writeLogDebug("CranOpenSL - START createMusic");
	//

	// Load music/effect from a file
	CranMusic* music = new CranMusic();
    #ifdef IPHONE_ENVIRONMENT
    music->prepare(p_filename);
    #endif
    #ifdef ANDROID_ENVIRONMENT
	music->prepare(engineEngine, outputMixObject, p_filename);
    #endif
	//
	Log::writeLogDebug("CranOpenSL - END createMusic");
	//
	return music;
}

CranSound* CranOpenSL::createSound(const char* p_filename)
{
	Log::writeLogDebug("CranOpenSL - START createSound");
	//

	// Load music/effect from a file
	CranSound* sound = new CranSound();
    #ifdef IPHONE_ENVIRONMENT
    sound->prepare(p_filename);
    #endif

    #ifdef ANDROID_ENVIRONMENT
	sound->prepare(engineEngine, outputMixObject, p_filename);
    #endif
	//
	Log::writeLogDebug("CranOpenSL - END createSound");
	//
	return sound;
}

void CranOpenSL::clean()
{
	Log::writeLogDebug("CranOpenSL - START clean");
	//
    #ifdef ANDROID_ENVIRONMENT
    // Destroy buffer queue audio player object, and invalidate all associated interfaces
    if (bqPlayerObject != NULL) {
        (*bqPlayerObject)->Destroy(bqPlayerObject);
        bqPlayerObject = NULL;
        bqPlayerPlay = NULL;
        bqPlayerBufferQueue = NULL;
        bqPlayerEffectSend = NULL;
    }

	// Destroy output mix object, and invalidate all associated interfaces
    if (outputMixObject != NULL) {
        (*outputMixObject)->Destroy(outputMixObject);
        outputMixObject = NULL;
        outputMixEnvironmentalReverb = NULL;
    }

	// Destroy engine object, and invalidate all associated interfaces
    if (engineObject != NULL) {
        (*engineObject)->Destroy(engineObject);
        engineObject = NULL;
        engineEngine = NULL;
    }
    #endif
    //
    Log::writeLogDebug("CranOpenSL - END clean");
}
