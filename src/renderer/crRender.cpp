#include "render/crRender.h"

using namespace Cran::Math;
using namespace Cran::Util;

// *** Constructor
CranRenderable::CranRenderable()
{
    _pivotInPixels = new Vector2();
	_modelViewMatrix = new Matrix4();
	_rotationMatrix = new Matrix4();
	_translationAMatrix = new Matrix4();
	_translationBMatrix = new Matrix4();
	_scaleAMatrix = new Matrix4();
	_scaleBMatrix = new Matrix4();

}

// *** Destructor
CranRenderable::~CranRenderable()
{
    delete _pivotInPixels;
    delete _modelViewMatrix;
    delete _rotationMatrix;
    delete _translationAMatrix;
    delete _translationBMatrix;
    delete _scaleAMatrix;
    delete _scaleBMatrix;

}

// *** Initialize matrix used in worldViewMatrix
void CranRenderable::initModelViewMatrix()
{
	Log::writeLogDebug("CranRenderable - initModelViewMatrix");
	//
    //_pivotInPixels = new Vector2();
	//_modelViewMatrix = new Matrix4();
	//_rotationMatrix = new Matrix4();
	//_translationAMatrix = new Matrix4();
	//_translationBMatrix = new Matrix4();
	//_scaleAMatrix = new Matrix4();
	//_scaleBMatrix = new Matrix4();
    //
	Log::writeLogDebug("CranRenderable - initModelViewMatrix end");
}

// *** Load initial values in matrix
void CranRenderable::loadModelViewMatrix()
{
	Log::writeLogDebug("CranRenderable - loadModelViewMatrix");
	//
    CRfloat relationWH = CranEngine::getPixelWidth() / CranEngine::getPixelHeight();
    CRfloat relationHW = CranEngine::getPixelHeight() / CranEngine::getPixelWidth();
    CRfloat centerH = CranEngine::getScreenHeight()/2;
    CRfloat centerW = CranEngine::getScreenWidth()/2;

    // Load values
	// Translate screen size(in pixels) to Opengl coordinates(in units from -1.0f to 1.0f).
	if ( CranEngine::isOrientationPortrait() ){
		_scaleAMatrix->scale(relationWH, 1.0f, 1.0f);
		_scaleBMatrix->scale(relationHW, 1.0f, 1.0f);
		//
        _pivotInPixels->setValues(centerW, centerH);
	} else if ( CranEngine::isOrientationLandscape() ){
		_scaleAMatrix->scale(relationHW, 1.0f, 1.0f);
		_scaleBMatrix->scale(relationWH, 1.0f, 1.0f);
		//
        _pivotInPixels->setValues(centerH, centerW);
	}
	//
	_modelViewMatrix->identity();
	_rotationMatrix->identity();
	_translationAMatrix->identity();
	_translationBMatrix->identity();
	//
	Log::writeLogDebug("CranRenderable - loadModelViewMatrix end");
}

// *** Update model view matrix
void CranRenderable::updateModelViewMatrix()
{   
	Log::writeLogDebug("CranRenderable - updateModelViewMatrix");
	//
	_modelViewMatrix->identity();
	//
#ifdef IPHONE_ENVIRONMENT
	_modelViewMatrix->operator*(*_translationAMatrix);
	_modelViewMatrix->operator*(*_scaleAMatrix);
	_modelViewMatrix->operator*(*_rotationMatrix);
	_modelViewMatrix->operator*(*_scaleBMatrix);
	_modelViewMatrix->operator*(*_translationBMatrix);
#endif
#ifdef ANDROID_ENVIRONMENT
	_modelViewMatrix->operator*(*_translationBMatrix);
	_modelViewMatrix->operator*(*_scaleBMatrix);
	_modelViewMatrix->operator*(*_rotationMatrix);
	_modelViewMatrix->operator*(*_scaleAMatrix);
	_modelViewMatrix->operator*(*_translationAMatrix);
#endif
	//
    float* modelView = CRNULL;
	modelView = _modelViewMatrix->toArray16f(modelView);
    CranEngine::Instance()->updateShader(modelView);
    free(modelView);
    //
    Log::writeLogDebug("CranRenderable - updateModelViewMatrix end");
}

// *** Render to buffer screen
void CranRenderable::render(CRfloat *p_vertex_data, CRfloat *p_vertex_color, CRfloat *p_vertex_texture)
{   
	Log::writeLogDebug("CranRenderable - render");
	//
    if ((_renderFlags & CR_ATTRIB_POSITION_INDEX) == CR_ATTRIB_POSITION_INDEX){
    	Log::writeLogDebug("CranRenderable - render A");
		glEnableVertexAttribArray(CR_ATTRIB_POSITION_INDEX);
		glVertexAttribPointer(CR_ATTRIB_POSITION_INDEX, VERTEX_POS_SIZE_XY, GL_FLOAT, GL_FALSE, 0, p_vertex_data);
	}
	//
	if ((_renderFlags & CR_VERTEX_ATTRIB_COLOR) == CR_VERTEX_ATTRIB_COLOR){
		Log::writeLogDebug("CranRenderable - render B");
		glEnableVertexAttribArray(CR_VERTEX_ATTRIB_COLOR);
		glVertexAttribPointer(CR_VERTEX_ATTRIB_COLOR, VERTEX_COLOR_SIZE, GL_FLOAT, GL_FALSE, 0, p_vertex_color);
	}
	//
	if ((_renderFlags & CR_VERTEX_ATTRIB_TEXCOORD0) == CR_VERTEX_ATTRIB_TEXCOORD0){
		Log::writeLogDebug("CranRenderable - render C");
		glEnableVertexAttribArray(CR_VERTEX_ATTRIB_TEXCOORD0);
		glVertexAttribPointer(CR_VERTEX_ATTRIB_TEXCOORD0, VERTEX_TEXCOORD_SIZE, GL_FLOAT, GL_FALSE, 0, p_vertex_texture);
	}
    //
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	//
    Log::writeLogDebug("CranRenderable - render end");
}

void CranRenderable::setRenderFlags(int p_flags)
{
    _renderFlags = p_flags;
}
