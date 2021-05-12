#include "sound/crMusic.h"

// *** Constructor of the class
CranMusic::CranMusic()
{
    #ifdef ANDROID_ENVIRONMENT
	fdPlayerObject = NULL;
	fdPlayerPlay = NULL;
	fdPlayerSeek = NULL;
#endif
	//
	addToResourceManager(CRAN_MUSIC);
}

// *** Destructor
CranMusic::~CranMusic()
{
	clean();
}

#ifdef IPHONE_ENVIRONMENT
void CranMusic::prepare(const char* p_filename)
{
    Log::writeLogDebug("CranMusic - START prepare");
    //
    Cran::Util::String::copy(_filename, p_filename);
    //
    crMusicPrepare(p_filename, p_filename);
    //
    Log::writeLogDebug("CranMusic - END prepare");
}
#endif


#ifdef ANDROID_ENVIRONMENT
void CranMusic::prepare(SLEngineItf p_engineEngine, SLObjectItf p_outputMixObject, const char* p_filename)
{
	Log::writeLogDebug("CranMusic - START prepare");
	//
	Cran::Util::String::copy(_filename, CRAN_STRING_BLANK);
	Cran::Util::String::copy(_filename, p_filename);
	//
	SLresult result;

    // *** Use asset manager to open asset by filename
    AAssetManager* mgr = AAssetManager_fromJava(CranEngine::getJavaEnvironment(), CranEngine::getAssetManager());
	AAsset* asset = AAssetManager_open(mgr, _filename, AASSET_MODE_UNKNOWN);

    // *** The asset might not be found
    if (asset == NULL) {
    	Log::writeLogError("CranOpenSL - prepare - Error, the asset might not be found");
        return;
    }

    // *** Open asset as file descriptor
    off_t start;
	off_t length;
    int fd = AAsset_openFileDescriptor(asset, &start, &length);
    if (fd <= 0) {
		Log::writeLogError("CranOpenSL - prepare - Error, not file descriptor founded");
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
		Log::writeLogError("CranOpenSL - prepare - Error creating audio player");
		return;
	}

    // *** Realize the player
    result = (*fdPlayerObject)->Realize(fdPlayerObject, SL_BOOLEAN_FALSE);
    if (result != SL_RESULT_SUCCESS){
		Log::writeLogError("CranOpenSL - prepare - Error realizing");
		return;
	}

    // *** Get the play interface
    result = (*fdPlayerObject)->GetInterface(fdPlayerObject, SL_IID_PLAY, &fdPlayerPlay);
    if (result != SL_RESULT_SUCCESS){
		Log::writeLogError("CranOpenSL - prepare - Error getting interface");
		return;
	}

    // *** Get the seek interface
    result = (*fdPlayerObject)->GetInterface(fdPlayerObject, SL_IID_SEEK, &fdPlayerSeek);
    if (result != SL_RESULT_SUCCESS){
		Log::writeLogError("CranOpenSL - prepare - Error getting interface");
		return;
	}

	// *** Get the queue interface
	result = (*fdPlayerObject)->GetInterface(fdPlayerObject, SL_IID_BUFFERQUEUE, (void*)&_bufferQueueItf);
    if (result != SL_RESULT_SUCCESS){
		Log::writeLogError("CranOpenSL - prepare - Error getting interface");
		return;
	}

    // *** Enable whole file looping
    result = (*fdPlayerSeek)->SetLoop(fdPlayerSeek, SL_BOOLEAN_TRUE, 0, SL_TIME_UNKNOWN);
    if (result != SL_RESULT_SUCCESS){
		Log::writeLogError("CranOpenSL - prepare - Error set loop");
		return;
	}
    //
    Log::writeLogDebug("CranMusic - END prepare");
}
#endif

void CranMusic::play()
{
	#ifdef IPHONE_ENVIRONMENT
        crMusicPlay(_filename);
	#endif
	#ifdef ANDROID_ENVIRONMENT
    SLresult result;

    // *** Make sure the asset audio player was created
    if (fdPlayerPlay != NULL) {
        // Set the player's state
        result = (*fdPlayerPlay)->SetPlayState(fdPlayerPlay, SL_PLAYSTATE_PLAYING);
        if (result != SL_RESULT_SUCCESS){
			Log::writeLogError("CranMusic - play - Error playing");
			return;
		} else {
			Log::writeLogInfo("CranMusic - pause - Playing");
		}
    }
	#endif
}

void CranMusic::pause()
{
	#ifdef IPHONE_ENVIRONMENT
        crMusicPause(_filename);
	#endif
	#ifdef ANDROID_ENVIRONMENT
	SLresult result;

    // *** Make sure the asset audio player was created
    if (fdPlayerPlay != NULL) {
        // Set the player's state
        result = (*fdPlayerPlay)->SetPlayState(fdPlayerPlay, SL_PLAYSTATE_PAUSED);
		if (result != SL_RESULT_SUCCESS){
			Log::writeLogError("CranMusic - pause - Error pausing");
			return;
		} else {
			Log::writeLogInfo("CranMusic - pause - Paused");
		}
    }
	#endif
}

void CranMusic::resume()
{
	#ifdef IPHONE_ENVIRONMENT
        //crMusicResume(_filename);
	#endif
	#ifdef ANDROID_ENVIRONMENT
	SLresult result;

    // *** Make sure the asset audio player was created
    if (fdPlayerPlay != NULL) {
        // Set the player's state
        result = (*fdPlayerPlay)->SetPlayState(fdPlayerPlay, SL_PLAYSTATE_PLAYING);
		if (result != SL_RESULT_SUCCESS){
			Log::writeLogError("CranMusic - pause - Error pausing");
			return;
		} else {
			Log::writeLogInfo("CranMusic - pause - Paused");
		}
    }
	#endif
}

void CranMusic::stop()
{
	#ifdef IPHONE_ENVIRONMENT
        crMusicStop(_filename);
	#endif
	#ifdef ANDROID_ENVIRONMENT
	SLresult result;

    // *** Make sure the asset audio player was created
    if (fdPlayerPlay != NULL) {
        // Set the player's state
        result = (*fdPlayerPlay)->SetPlayState(fdPlayerPlay, SL_PLAYSTATE_STOPPED);
		if (result != SL_RESULT_SUCCESS){
			Log::writeLogError("CranMusic - stopped - Error stopping");
			return;
		} else {
			Log::writeLogInfo("CranMusic - pause - Stopped");
		}
    }
	#endif
}

CRbool CranMusic::isPlaying()
{
	#ifdef IPHONE_ENVIRONMENT
        CRbool result = (CRbool)crIsMusicPlaying(_filename);
        return result;
	#endif
	#ifdef ANDROID_ENVIRONMENT
	SLresult result;
	//
    if (fdPlayerPlay != NULL) {

		result = (*_bufferQueueItf)->GetState(_bufferQueueItf, &_bufferQueueState);
		if (result != SL_RESULT_SUCCESS){
			Log::writeLogError("CranMusic - isPlaying - Error getting state");
			return CR_FALSE;
		}
		//
		if (_bufferQueueState.count > 0){
			Log::writeLogInfo("CranMusic - isPlaying - Continue playing");
			return CR_TRUE;
		} else {
			Log::writeLogInfo("CranMusic - isPlaying - No playing");
			return CR_FALSE;
		}
    }
    return CR_FALSE;
	#endif
}

// *** Shut down the native audio system
void CranMusic::clean()
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
