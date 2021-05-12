#ifndef __CRAN_BUFFER_H__
#define __CRAN_BUFFER_H__

#include "crPrerequisites.h"
#include "math/crRectangle.h"
#include "core/crObject.h"
extern "C"{
    #include "commons.h"
}

using namespace Cran::Math;

// FB - Frame Buffer
// RB - Render Buffer
class CranBuffer : public CranObject
{
public:
    CranBuffer();
    ~CranBuffer();
    
	//unsigned int 	_frameBuffer[CRAN_FRAMEBUFFERS_MAX];
	unsigned int 	_frameBuffer;
	unsigned int	n_frameBuffer;
	
	unsigned int 	_frameBufferTexture[CRAN_FRAMEBUFFERS_TEXTURES_MAX];
	unsigned int	n_frameBufferTexture;
	//
	GLuint		_texture;
	GLuint		_frameBufferObjectId;
	GLuint		_renderBufferObjectId;
	GLuint		_depthRenderBuffer;
	
	// Buffers PRUEBASSSSSSSSSSSSSS
	GLuint		_gameFramebuffer;
	GLuint		_myColorRenderbuffer;
	GLuint		_textureSimpleId;
	
	// External
	GLuint		_defaultFramebuffer;
	GLuint		_systemFrameBuffer;
	GLuint		_colorRenderBuffer;
    //
	GLuint		_widthRenderBuffer;
	GLuint		_heightRenderBuffer;
	CRbool		_active;
	

void cranBufferInit(GLuint p_mainFB, GLuint p_colorRB, GLint p_widthRB, GLint p_heightRB);
void cranBufferCreateGeneral();
//
unsigned int cranBufferCreate();
void cranBufferBind(unsigned int p_idBuffer);
//
unsigned int cranBufferCreateTexture(unsigned int);
void cranBufferBindTexture();
//
//void cranBufferRender(CRrectangle*, CRrectangle*, unsigned int);
void cranBufferRender(Rectangle*, Rectangle*, unsigned int);
//
void cranBufferBindFrameBufferSystem();
void cranBufferRenderToBufferSystem();

};

#endif
