#ifdef WINDOWS_ENVIRONMENT
#include "crOpenGL1x.h"
#include "stdlib.h"

// **** VIEW
void Cran::Render::GL1x::crGl1LoadIdentity()
{
	glLoadIdentity();
}

void Cran::Render::GL1x::crGl1IdentityProjection()
{
	glMatrixMode(GL_PROJECTION);
	cranGl1LoadIdentity();
}

void Cran::Render::GL1x::crGl1IdentityModelview()
{
	glMatrixMode(GL_MODELVIEW);
	cranGl1LoadIdentity();
}

void Cran::Render::GL1x::crGl1Perspective(double p_fieldOfView, double p_aspect, double p_zNear, double p_zFar)
{
	gluPerspective( p_fieldOfView, p_aspect, p_zNear, p_zFar );
}

// **** CAPABILITIES
void Cran::Render::GL1x::crGl1Enable2DTextures()
{
	glEnable(GL_TEXTURE_2D);
}

void Cran::Render::GL1x::crGl1Disable2DTextures()
{
	glDisable(GL_TEXTURE_2D);
}


// **** RENDER
void Cran::Render::GL1x::crGl1Render2f( CR_PRIMITIVE p_primitive, float *p_data, float *p_color, float *p_texture_data)
{
	float x1, y1, x2, y2, x3, y3, x4, y4;
	float u1, v1, u2, v2, u3, v3, u4, v4;
	//
	if (p_primitive == CR_PRIMITIVE_QUAD){
		glBegin(GL_QUADS);								// Drawing Using Triangles
		x4 = *p_data;		y4 = *(++p_data);
		x3 = *(++p_data);	y3 = *(++p_data);
		x1 = *(++p_data);	y1 = *(++p_data);
		x2 = *(++p_data);	y2 = *(++p_data);
		//
		u1 = *p_texture_data;		v1 = *(++p_texture_data);
		u2 = *(++p_texture_data);	v2 = *(++p_texture_data);
		u4 = *(++p_texture_data);	v4 = *(++p_texture_data);
		u3 = *(++p_texture_data);	v3 = *(++p_texture_data);
		//
		glColor4f(p_color[0], p_color[1], p_color[2], p_color[3]); 
		glTexCoord2f(u4, v4);
		glVertex3f( x1, y1, 0.0f);
		//
		//glColor4f(1.0f, 0.0f, 0.0f, 0.5f); 
		glColor4f(p_color[4], p_color[5], p_color[6], p_color[7]); 
		glTexCoord2f(u3, v3);
		glVertex3f(x2, y2, 0.0f);
		//
		//glColor4f(1.0f, 0.0f, 0.0f, 0.5f); 
		glColor4f(p_color[8], p_color[9], p_color[10], p_color[11]); 
		glTexCoord2f(u2, v2);
		glVertex3f( x3, y3, 0.0f);
		//
		//glColor4f(1.0f, 0.0f, 0.0f, 0.5f); 
		glColor4f(p_color[12], p_color[13], p_color[14], p_color[15]); 
		glTexCoord2f(u1, v1);
		glVertex3f( x4, y4, 0.0f);
		//
		glEnd();
	}
	
}
#endif