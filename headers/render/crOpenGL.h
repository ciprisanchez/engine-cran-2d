#ifndef __CRAN_GL_H__
#define __CRAN_GL_H__

#include "crPrerequisites.h"
extern "C"{
	#include "commons.h"
}

namespace Cran {
	namespace Render {
		class GL{
		
		public:
			// TEXTURES
			static void crGlGenTextures(GLuint p_textures[]);
			static void crGlGenTextures(GLuint p_numTextures, GLuint *p_textures);
			static void crGlPixelStorei();
			static void crGlTexImage2D(GLint p_internalformat, GLsizei p_width, GLsizei p_height, GLsizei p_border, GLenum p_format, GLenum p_type, const GLvoid* p_data);
			static void crGlBindTexture(GLuint p_textures[], GLuint p_id);
			static void crGlDeleteTexture(GLuint p_textures[], GLuint p_id);

			// FRAME BUFFERS
			static void crGlGenFramebuffers(unsigned int p_numBuffers);

			// SCREEN
			static void crGlClearColor(CRfloat p_r, CRfloat p_g, CRfloat p_b, CRfloat p_alpha);
			static void crGlClear(CRuint p_mask);
			static void crGlEnableAlphaTest(CRuint p_function, CRfloat p_ref);
			static void crGlEnableBlending(CRuint p_sfactor, CRuint p_dfactor);
			static void crGlDisableAlphaTest();
			static void crGlDisableBlending();

			// VIEW
			static void crGlViewPort(int p_x, int p_y, int p_width, int p_height);
			/*
			matrix4 *cranGlPerspectiveFieldOfView(float p_fieldOfVision, float p_near, float p_far, float p_aspectRatio);
			matrix4 *cranGlFrustum(float p_left, float p_right, float p_bottom, float p_top, float p_near, float p_far);
			matrix4 *cranGlProjection(float p_fov, float p_aspect,float p_zNear, float p_zFar);
			matrix4 *cranGlOrtho(float p_left, float p_right, float p_bottom,float p_top, float p_near, float p_far);
			matrix4 *cranGlOrtho2D(float p_left, float p_right, float p_bottom, float p_top);
			*/
		};
	}
}

#endif