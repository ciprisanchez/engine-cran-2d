#include "core/crBuffer.h"

CranBuffer::CranBuffer()
{
    _defaultFramebuffer = 0;
	_colorRenderBuffer = 0;
	_widthRenderBuffer =  0;
	_heightRenderBuffer = 0;
    n_frameBuffer = 0;
	n_frameBufferTexture = 0;
    //
    addToResourceManager(CRAN_BUFFER);
}

CranBuffer::~CranBuffer()
{
    
}

void CranBuffer::cranBufferInit(GLuint p_mainFB, GLuint p_colorRB, GLint p_widthRB, GLint p_heightRB){
    #ifdef IPHONE_ENVIRONMENT
	_defaultFramebuffer = p_mainFB;
	_colorRenderBuffer = p_colorRB;
	_widthRenderBuffer =  p_widthRB;
	_heightRenderBuffer = p_heightRB;
	//
	n_frameBuffer = 0;
	n_frameBufferTexture = 0;
	//
	cranBufferCreateGeneral();
#endif
}

// *** Open Buffer to write
void CranBuffer::cranBufferBindFrameBufferSystem()
{
	#ifdef IPHONE_ENVIRONMENT
	glBindFramebuffer(GL_FRAMEBUFFER, _defaultFramebuffer);
	#endif
}

// *** Close Buffer
void CranBuffer::cranBufferRenderToBufferSystem()
{
	#ifdef IPHONE_ENVIRONMENT
	glBindRenderbuffer(GL_RENDERBUFFER, _colorRenderBuffer);
#endif
}

/*
void CranBuffer::cranBufferBindTexture()
{
	glBindTexture(GL_TEXTURE_2D, _textureSimpleId);
}*/


void CranBuffer::cranBufferCreateGeneral()
{	
#ifdef IPHONE_ENVIRONMENT
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
	
	// *** Frame buffer
	glGenFramebuffers(1, &_gameFramebuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, _gameFramebuffer);

	// *** Texture buffer
	glGenTextures(1, &_textureSimpleId);
	glBindTexture(GL_TEXTURE_2D, _textureSimpleId);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _widthRenderBuffer, _heightRenderBuffer, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _textureSimpleId, 0);

	// *** Check FBO status
	//CRbool frameBufferCreated = CR_FALSE;
	GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	if(status == GL_FRAMEBUFFER_COMPLETE)
	{
		_active = CR_TRUE;
	}
	else
	{
		_active = CR_FALSE;
	}
#endif
}
