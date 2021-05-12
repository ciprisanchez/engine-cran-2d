#ifdef IPHONE_ENVIRONMENT
#ifndef __IOS_INTERFACE_H__
#define __IOS_INTERFACE_H__

#include "cran.h"
//#include "EAGLView.h"

using namespace std;
class CranBridge;

// **********************************************************************************
// ******************************* SOUND MANAGEMENT
void crInitSoundManager();
//
void crMusicPrepare(const char *p_key, const char *p_file);
void crMusicPlay(const char *p_key);
void crMusicPause(const char *p_key);
void crMusicStop(const char *p_key);
bool crIsMusicPlaying(const char *p_key);
//
void crSoundPrepare(const char *p_key, const char *p_file);
void crSoundPlay(const char *p_key);
void crSoundStop(const char *p_key);
bool crIsSoundPlaying(const char *p_key);

// **********************************************************************************
// ******************************* ALERTS
int cranShowAlert(void *p_objectInstance);

// *** Get path application
const char* getSystemPath();
const char* getDocumentPath();


// **********************************************************************************
// ******************************* BUFFERS
void setContext(void *p_newContext, void *eaglLayer);
void setFramebuffer();
void setPresentFramebuffer();
void deleteFramebuffer();
GLuint getFrameBufferWidth();
GLuint getFrameBufferHeight();
GLuint getDefaultFramebuffer();
GLuint getColorRenderbuffer();
/*void setScreenBuffer();
void flushScreenBuffer();
*/
#endif
#endif
