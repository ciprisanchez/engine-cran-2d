#ifndef __CRAN_ENGINE_H__
#define __CRAN_ENGINE_H__

#ifdef ANDROID_ENVIRONMENT
#include <jni.h>
#endif

#include "crPrerequisites.h"
//*********** C STANDARD INCLUDES
extern "C" {
    #include "commons.h"
}

//*********** CRAN INCLUDES
#include "os/crOsIosInterface.h"
#include "os/crOsWinInterface.h"
#include "os/crOsAndroidInterface.h"
//
#include "core/crResource.h"
#include "core/crBuffer.h"
//
#include "math/crMath.h"
#include "math/crMatrix4.h"
#include "math/crVector2.h"
#include "math/crRandom.h"
#include "render/crOpenGL.h"
#include "sound/crMusic.h"
#include "sound/crSound.h"
#include "sound/crOpenSL.h"
#include "util/crString.h"
#include "util/crLog.h"
#include "util/crTime.h"

using namespace Cran::Util;

class CranEngine
{

private:
	static CranEngine*          _instance;
    static CRorientation		_screenOrientation;
    static CRfloat				_screenWidth;
	static CRfloat				_screenHeight;
	static CRfloat				_screenPixelWidth;
	static CRfloat				_screenPixelHeight;
    static CRfloat				_screenTextureWidth;
    static CRfloat				_screenTextureHeight;
    static const char*			_pathZipFile;
    
#ifdef ANDROID_ENVIRONMENT
    static zip*					_zipFile;
    static JNIEnv*				_env;
    static jobject				_assetManager;
#endif
protected:
	CranEngine();
	CranEngine(const CranEngine &);
	CranEngine &operator= (const CranEngine &);
    
public:
    static void setOrientation(CRorientation p_orientation);   // Screen orientation
    static void setOrientation(int width, int height, CRorientation p_orientation);
    static CranEngine* Instance(); 
    static CRfloat convertPxToTxGl(CRaxis p_axis, CRint p_position);
    static CRfloat convertPxToGl(CRaxis p_axis, CRint p_position);
    static CRbool isOrientationPortrait();
    static CRbool isOrientationLandscape();
    static CRfloat getPixelWidth();
    static CRfloat getPixelHeight();
    static CRfloat getScreenWidth();
    static CRfloat getScreenHeight();
    
    ~CranEngine();
    
    // **** CYCLE OF LIFE
    void init();
    void update();
    CRbool draw();
    void cleanFT();
    
    // *** SET METHODS
    //void setOrientation(CRorientation p_orientation);   // Screen orientation

#ifdef ANDROID_ENVIRONMENT
    static void setZipFile(const char* p_filename);
    static zip* getZipFile();
    static void listZipFile();
    //
    static void setAssetManager(jobject p_assetManager);
   	JNIEnv* getJNIEnvironment();
    static void setJavaEnvironment(JNIEnv* p_env);
    static JNIEnv* getJavaEnvironment();
    static jobject getAssetManager();
#endif

    void setIosController(void *p_self);  // IOS controller

    
    // *** 
    void showKeyboardPanel();
        
    // *** RESOURCE MANAGER
    void addResource(int p_resource, CranObject *p_object);
    void removeResource(int p_resource, CranObject *p_object);
    CranObject* getResource(int p_resource, CRuint p_id);
    void updateShader(float *p_modelViewMatrix);
    
    // ***
    
	// *** SHADER
    void loadShader(int p_shader);
    void useShader(int p_shader);
    
    // *** BUFFER
    void initBuffer(GLuint p_mainFB, GLuint p_colorRB, GLint p_widthRB, GLint p_heightRB);
    void setViewPortBuffer();
    void beginActiveBuffer();
    void endActiveBuffer();
    
    // *** FREETYPE
    FT_Library getFTLibrary();

	const char* getPathResource();
	const char* getPathDocuments();
    //unsigned int* getTexturePool();
    
    
    
protected:
    
    // Singletons
    CranResource        *_resourceManager;
    
private:
    void initGL();
    void initSL();
    void initFT();
    
    // *** Application paths
    char*			_pathResource;
    char*			_pathDocuments;

    // *** Ios Controller
    void*           _iosViewController;  //Objective C object - View controller active
    
    // *** Active classes
    CRuint              _activeShaderId;
    CRuint              _activeBufferId;
    
    // *** Freetype
	FT_Library			_ftlib;
    
    
};

#endif
