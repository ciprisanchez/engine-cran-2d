#ifndef __CRAN_RENDERABLE_H__
#define __CRAN_RENDERABLE_H__

#include "crPrerequisites.h"
#include "cran.h"
#include "core/crObject.h"
#include "core/crColor.h"
#include "math/crMatrix4.h"
#include "math/crVector2.h"
extern "C"{
    #include "commons.h"
}

using namespace Cran::Math;

class CranRenderable
{
    
public:
    CranRenderable();
    ~CranRenderable();	
    
protected:
    int     _renderFlags;
    
    CranTexture *_ct;
	
	// *** Matrix used for worldViewMatrix
    Matrix4			*_modelViewMatrix;
	Matrix4			*_rotationMatrix;
	Matrix4			*_scaleAMatrix;
	Matrix4			*_scaleBMatrix;
	Matrix4			*_translationAMatrix;
	Matrix4			*_translationBMatrix;
	
	// *** Vector used for texture pivot(rotations)
    Vector2         *_pivotInPixels;
	
	// *** Color texture
	Color			*_color;
	
    // *** Matrix methods
    void initModelViewMatrix();
    void loadModelViewMatrix();
	void updateModelViewMatrix();
    
	// *** Render an object
    
	void render(CRfloat *p_vertex_data, CRfloat *p_vertex_color, CRfloat *p_vertex_texture);
    void setRenderFlags(int p_flags);

};

#endif

