#include "render/crOpenGL.h"

// ********************************************************************************************************************
// ************************************************************************ TEXTURES - Load texture and more functions
void Cran::Render::GL::crGlGenTextures(GLuint p_textures[])
{
	glGenTextures(CRAN_TEXTURES_MAX, &p_textures[0] );
}

void Cran::Render::GL::crGlGenTextures(GLuint p_numTextures, GLuint *p_textures)
{
	glGenTextures(p_numTextures, p_textures );
}

void Cran::Render::GL::crGlPixelStorei()
{
	glPixelStorei ( GL_UNPACK_ALIGNMENT, 1 );
}

void Cran::Render::GL::crGlTexImage2D(GLint p_internalformat, GLsizei p_width, GLsizei p_height, GLsizei p_border, GLenum p_format, GLenum p_type, const GLvoid* p_data)
{
	glTexImage2D( GL_TEXTURE_2D, 0, p_internalformat, p_width, p_height, p_border, p_format, p_type, p_data);
	
	// Texture parameters
	glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
	glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
}

void Cran::Render::GL::crGlBindTexture(GLuint p_textures[], GLuint p_id)
{
	glBindTexture ( GL_TEXTURE_2D, p_textures[p_id] );
}

void Cran::Render::GL::crGlDeleteTexture(GLuint p_textures[], GLuint p_id)
{
	//glDeleteTextures ( 1, (const GLuint*)p_textures[p_id] );
    glDeleteTextures ( 1, &p_textures[p_id] );
}

// ***********************************************************************************************************************
// *************************************************************************** SCREEN functions
void Cran::Render::GL::crGlClearColor(CRfloat p_r, CRfloat p_g, CRfloat p_b, CRfloat p_alpha)
{
	glClearColor(p_r, p_g, p_b, p_alpha);
}

void Cran::Render::GL::crGlClear(CRuint p_mask)
{
	glClear(p_mask);
}

void Cran::Render::GL::crGlEnableBlending(CRuint p_sfactor, CRuint p_dfactor){
	glEnable(GL_BLEND);
	glBlendFunc( p_sfactor, p_dfactor );
}

void Cran::Render::GL::crGlDisableBlending(){
	glDisable(GL_BLEND);
}

#ifdef IPHONE_ENVIRONMENT
void Cran::Render::GL::crGlEnableAlphaTest(CRuint p_function, CRfloat p_ref){
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(p_function, p_ref);
}

void Cran::Render::GL::crGlDisableAlphaTest(){
	glDisable(GL_ALPHA_TEST);
}
#endif

// ************************************************************************************************************************
// *************************************************************************** View functions
void Cran::Render::GL::crGlViewPort(int p_x, int p_y, int p_width, int p_height)
{
	glViewport ( p_x, p_y, p_width, p_height );
}

// *** Multiply the current matrix by a perspective matrix
/*
 matrix4 *Cran::Render::GL::crGlPerspectiveFieldOfView(float p_fieldOfVision, float p_near, float p_far, float p_aspectRatio)
 {
 float size = p_near * tanf(CR_DEGREES_TO_RADIANS(p_fieldOfVision) / 2.0); 
 //
 //matrix4 *matrix = cranGlFrustum(-size, size, -size/p_aspectRatio, size/p_aspectRatio, p_near, p_far);
 matrix4 *matrix = 0;
 
 //
 return matrix;
 }
 */
// *********************************************************************************************************************
// *************************************************************************** RENDER functions


/*void cranGlRenderVertex(GLuint p_programHandle, unsigned int p_index, int p_size, GLenum p_type, GLboolean p_normalized, float *p_data)
 {
 glEnableVertexAttribArray(p_index);
 glVertexAttribPointer(p_index, p_size, p_type, p_normalized, 0, p_data);
 glBindAttribLocation(p_programHandle, p_index, CRAN_ATTRIB_POSITION);
 }*/


// ********************************************************************************************************************************
// *************************************************************************** FRAME BUFFERS
/*
 void cranGlGenFramebuffers(unsigned int p_numBuffers)
 {
 glGenFramebuffers(p_numBuffers, &cranbuffer->_frameBuffer[0]);
 }
 
 void cranGlBindFramebuffers(unsigned int p_idBuffer)
 {
 glBindFramebuffer(GL_FRAMEBUFFER, cranbuffer->_frameBuffer[p_idBuffer]);
 }*/


/*
 
 // *** Multiply the current matrix by a perspective matrix
 matrix4 *cranGlFrustum(float p_left, float p_right, float p_bottom, float p_top, float p_near, float p_far)
 {
 float r_l = p_right - p_left;
 float t_b = p_top - p_bottom;
 float f_n = p_far - p_near;	
 float A = (p_right + p_left)/r_l;
 float B = (p_top + p_bottom)/t_b;
 float C = -((p_far + p_near)/f_n);
 float D = -((2 * p_far * p_near)/f_n);
 //
 matrix4 *matrix = ( matrix4 * ) calloc( 1, sizeof( matrix4 ) );
 //
 matrix->_m11 = (2 * p_near)/r_l;	matrix->_m12 = 0; 					matrix->_m13 = A;		matrix->_m14 = 0; 
 matrix->_m21 = 0; 					matrix->_m22 = (2 * p_near)/t_b;	matrix->_m23 = B;		matrix->_m24 = 0; 
 matrix->_m31 = 0; 					matrix->_m32 = 0;					matrix->_m33 = C;		matrix->_m34 = D; 
 matrix->_m41 = 0; 					matrix->_m42 = 0;					matrix->_m43 = -1;		matrix->_m44 = 1;
 //
 return matrix;
 }
 
 matrix4 *cranGlProjection(float p_fov, float p_aspect,float p_zNear, float p_zFar)
 {
 const float h = 1.0f / (float)(tan(p_fov*CR_PI_OVER_360));
 float neg_depth = p_zNear - p_zFar;
 //
 matrix4 *matrix = ( matrix4 * ) calloc( 1, sizeof( matrix4 ) );
 //
 matrix->_m11 = h / p_aspect; 	matrix->_m12 = 0; matrix->_m13 = 0; 								matrix->_m14 = 0; 
 matrix->_m21 = 0; 				matrix->_m22 = h; matrix->_m23 = 0; 								matrix->_m24 = 0; 
 matrix->_m31 = 0; 				matrix->_m32 = 0; matrix->_m33 = (p_zFar + p_zNear)/neg_depth; 		matrix->_m34 = 0; 
 matrix->_m41 = 0; 				matrix->_m42 = 0; matrix->_m43 = 2.0f*(p_zNear*p_zFar)/neg_depth;	matrix->_m44 = 1;
 //
 //matrix = cranMatrixMultiply(p_m, matrix);
 //
 
 //const float h2 = 1.0f / tan(p_fov*PI_OVER_360);
 //float neg_depth2 = p_zNear - p_zFar;
 //matrix->_m11 = h; 	matrix->_m12 = 0; 			matrix->_m13 = 0; 								matrix->_m14 = 0; 
 //matrix->_m21 = 0;	matrix->_m22 = p_aspect/h; 	matrix->_m23 = 0; 								matrix->_m24 = 0; 
 //matrix->_m31 = 0; 	matrix->_m32 = 0; 			matrix->_m33 = (p_zFar + p_zNear)/neg_depth; 	matrix->_m34 = 0; 
 //matrix->_m41 = 0; 	matrix->_m42 = 0; 			matrix->_m43 = 2.0f*(p_zNear*p_zFar)/neg_depth;	matrix->_m44 = 1;
 //
 /*		
 return matrix;
 }
 
 matrix4 *cranGlOrtho(float p_left, float p_right, float p_bottom, float p_top, float p_near, float p_far)
 {
 float r_l = p_right - p_left;
 float t_b = p_top - p_bottom;
 float f_n = p_far - p_near;
 //
 float tx = - (p_right + p_left) / r_l;
 float ty = - (p_top + p_bottom) / t_b;
 float tz = - (p_far + p_near) / f_n;
 //
 matrix4 *matrix = ( matrix4 * ) calloc( 1, sizeof( matrix4 ) );
 //
 matrix->_m11 = 2.0f/ r_l;	matrix->_m12 = 0; 			matrix->_m13 = 0; 			matrix->_m14 = tx; 
 matrix->_m21 = 0; 			matrix->_m22 = 2.0f / t_b;	matrix->_m23 = 0;			matrix->_m24 = ty; 
 matrix->_m31 = 0; 			matrix->_m32 = 0; 			matrix->_m33 = 2.0f / f_n;	matrix->_m34 = tz; 
 matrix->_m41 = 0; 			matrix->_m42 = 0; 			matrix->_m43 = 0;			matrix->_m44 = 1;
 //
 return matrix;
 }
 
 matrix4 *cranGlOrtho2D(float p_left, float p_right, float p_bottom, float p_top)
 {
 float p_near = -1;
 float p_far = 1;
 float r_l = p_right - p_left;
 float t_b = p_top - p_bottom;
 float f_n = p_far - p_near;
 //
 float tx = - (p_right + p_left) / r_l;
 float ty = - (p_top + p_bottom) / t_b;
 float tz = - (p_far + p_near) / f_n;
 //
 matrix4 *matrix = ( matrix4 * ) calloc( 1, sizeof( matrix4 ) );
 //
 matrix->_m11 = 2.0f/ r_l;	matrix->_m12 = 0; 			matrix->_m13 = 0; 			matrix->_m14 = tx; 
 matrix->_m21 = 0; 			matrix->_m22 = 2.0f / t_b;	matrix->_m23 = 0;			matrix->_m24 = ty; 
 matrix->_m31 = 0; 			matrix->_m32 = 0; 			matrix->_m33 = 2.0f / f_n;	matrix->_m34 = tz; 
 matrix->_m41 = 0; 			matrix->_m42 = 0; 			matrix->_m43 = 0;			matrix->_m44 = 1;
 //
 return matrix;
 }*/
