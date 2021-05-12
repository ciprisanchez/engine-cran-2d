#include "sound/crSound.h"

// *** Constructor of the class
CranSound::CranSound()
{
    #ifdef ANDROID_ENVIRONMENT
	fdPlayerObject = NULL;
	fdPlayerPlay = NULL;
	fdPlayerSeek = NULL;
#endif
	//
	addToResourceManager(CRAN_SOUND);
}

// *** Destructor
CranSound::~CranSound()
{
	clean();
}

#ifdef IPHONE_ENVIRONMENT
void CranSound::prepare(const char* p_filename)
{
    Log::writeLogDebug("CranSound - START prepare");
    //
    Cran::Util::String::copy(_filename, p_filename);
    //
    crSoundPrepare(p_filename, p_filename);
    //
    Log::writeLogDebug("CranSound - END prepare");
}
#endif

#ifdef ANDROID_ENVIRONMENT
void CranSound::prepare(SLEngineItf p_engineEngine, SLObjectItf p_outputMixObject, const char* p_filename)
{
	Log::writeLogDebug("CranSound - START prepare");
	//
	Cran::Util::String::copy(_filename, p_filename);
	//
	SLresult result;

    // *** Use asset manager to open asset by filename
    AAssetManager* mgr = AAssetManager_fromJava(CranEngine::getJavaEnvironment(), CranEngine::getAssetManager());
	AAsset* asset = AAssetManager_open(mgr, _filename, AASSET_MODE_UNKNOWN);

    // *** The asset might not be found
    if (asset == NULL) {
    	Log::writeLogError("CranSound - prepare - Error, the asset might not be found");
        return;
    }

    // *** Open asset as file descriptor
    off_t start;
	off_t length;
    int fd = AAsset_openFileDescriptor(asset, &start, &length);
    if (fd <= 0) {
		Log::writeLogError("CranSound - prepare - Error, not file descriptor founded");
		return;
	}
    AAsset_close(asset);

    // *** Configure audio source
    SLDataLocator_AndroidFD loc_fd = {SL_DATALOCATOR_ANDROIDFD, fd, start, length};
    SLDataFormat_MIME format_mime = {SL_DATAFORMAT_MIME, NULL, SL_CONTAINERTYPE_UNSPECIFIED};
    SLDataSource audioSrc = {&loc_fd, &format_mime};

    // *** Configure audio sink
    SLDataLocator_OutputMix loc_outmix = {SL_DATALOCATOR_OUTPUTMIX, p_outputMixObject};
    SLDataSink audioSnk = {&loc_outmix, NULL};

    // *** Create audio player
    const SLInterfaceID ids[1] = {SL_IID_SEEK};
    const SLboolean req[1] = {SL_BOOLEAN_TRUE};
    result = (*p_engineEngine)->CreateAudioPlayer(p_engineEngine, &fdPlayerObject, &audioSrc, &audioSnk, 1, ids, req);
    if (result != SL_RESULT_SUCCESS){
		Log::writeLogError("CranSound - prepare - Error creating audio player");
		return;
	}

    // *** Realize the player
    result = (*fdPlayerObject)->Realize(fdPlayerObject, SL_BOOLEAN_FALSE);
    if (result != SL_RESULT_SUCCESS){
		Log::writeLogError("CranSound - prepare - Error realizing");
		return;
	}

    // *** Get the play interface
    result = (*fdPlayerObject)->GetInterface(fdPlayerObject, SL_IID_PLAY, &fdPlayerPlay);
    if (result != SL_RESULT_SUCCESS){
		Log::writeLogError("CranSound - prepare - Error getting interface");
		return;
	}

    // *** Get the seek interface
    result = (*fdPlayerObject)->GetInterface(fdPlayerObject, SL_IID_SEEK, &fdPlayerSeek);
    if (result != SL_RESULT_SUCCESS){
		Log::writeLogError("CranSound - prepare - Error getting interface");
		return;
	}

	// *** Get the queue interface
	result = (*fdPlayerObject)->GetInterface(fdPlayerObject, SL_IID_BUFFERQUEUE, (void*)&_bufferQueueItf);
    if (result != SL_RESULT_SUCCESS){
		Log::writeLogError("CranSound - prepare - Error getting interface");
		return;
	}

    // *** Enable whole file looping
    result = (*fdPlayerSeek)->SetLoop(fdPlayerSeek, SL_BOOLEAN_TRUE, 0, SL_TIME_UNKNOWN);
    if (result != SL_RESULT_SUCCESS){
		Log::writeLogError("CranSound - prepare - Error set loop");
		return;
	}
    //
    Log::writeLogDebug("CranSound - END prepare");
}
#endif

void CranSound::play()
{
	#ifdef IPHONE_ENVIRONMENT
		crSoundPlay(_filename);
        //crIsSoundPlaying("laser");
		//crPlaySound("laser", "hallelujah.caf");
        //crIsSoundPlaying(_filename);
	#endif
	#ifdef ANDROID_ENVIRONMENT
    SLresult result;

    // *** Make sure the asset audio player was created
    if (fdPlayerPlay != NULL) {
        // Set the player's state
        result = (*fdPlayerPlay)->SetPlayState(fdPlayerPlay, SL_PLAYSTATE_PLAYING);
        if (result != SL_RESULT_SUCCESS){
			Log::writeLogError("CranSound - play - Error playing");
			return;
		} else {
			Log::writeLogInfo("CranSound - pause - Playing");
		}
    }
	#endif
}

void CranSound::stop()
{
	#ifdef IPHONE_ENVIRONMENT
        crSoundStop(_filename);
	#endif
	#ifdef ANDROID_ENVIRONMENT
	SLresult result;

    // *** Make sure the asset audio player was created
    if (fdPlayerPlay != NULL) {
        // Set the player's state
        result = (*fdPlayerPlay)->SetPlayState(fdPlayerPlay, SL_PLAYSTATE_STOPPED);
		if (result != SL_RESULT_SUCCESS){
			Log::writeLogError("CranSound - stopped - Error stopping");
			return;
		} else {
			Log::writeLogInfo("CranSound - pause - Stopped");
		}
    }
	#endif
}

CRbool CranSound::isPlaying()
{
	#ifdef IPHONE_ENVIRONMENT
        crIsSoundPlaying(_filename);
        return CR_TRUE;
	#endif
	#ifdef ANDROID_ENVIRONMENT
	SLresult result;
	//
    if (fdPlayerPlay != NULL) {

		result = (*_bufferQueueItf)->GetState(_bufferQueueItf, &_bufferQueueState);
		if (result != SL_RESULT_SUCCESS){
			Log::writeLogError("CranSound - isPlaying - Error getting state");
			return CR_FALSE;
		}
		//
		if (_bufferQueueState.count > 0){
			Log::writeLogInfo("CranSound - isPlaying - Continue playing");
			return CR_TRUE;
		} else {
			Log::writeLogInfo("CranSound - isPlaying - No playing");
			return CR_FALSE;
		}
    }
    return CR_FALSE;
	#endif
}

// *** Shut down the native audio system
void CranSound::clean()
{
    #ifdef ANDROID_ENVIRONMENT
    // Destroy file descriptor audio player object, and invalidate all associated interfaces
    if (fdPlayerObject != NULL) {
        (*fdPlayerObject)->Destroy(fdPlayerObject);
        fdPlayerObject = NULL;
        fdPlayerPlay = NULL;
        fdPlayerSeek = NULL;
    }
#endif
}
