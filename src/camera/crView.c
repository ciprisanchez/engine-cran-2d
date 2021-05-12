/*

typedef enum { 
	CR_TRANSITION_TO_LEFT, 
	CR_TRANSITION_TO_RIGHT
} CR_TRANSITION_DIRECTION;

typedef struct {
	int							_counter;
	CR_TRANSITION_DIRECTION		_direction;
	CRrectangle					*_positionSpriteToHide;
	CRrectangle					*_positionSpriteToShow;
	CRANsprite					*_spriteToShow;
	CRANsprite					*_spriteToHide;
} CRANtransition;


void cranLoadMatrixPerspective()
{
	//cran->_projectionMatrix = cranGlPerspectiveFieldOfView(90.0f, 0.1f, 100.0f, 640.0f/960.0f);
	//projectionMatrix = cranGlProjection(70.0f, 320/480, 1.0f, 100.0f)
	//projectionMatrix = cranGlOrthografic(-1.0f, 1.0f, -1.0, 1.0, 5, 100);
}

void cranSetViewPort()
{
	cranGlViewPort(0, 0, cran->_CRANbuffer->_widthRenderBuffer, cran->_CRANbuffer->_heightRenderBuffer);
}

void cranTransition(CRANsprite *p_sprite_hide, CRANsprite *p_sprite_show, CR_TRANSITION_DIRECTION p_transition_direction)
{
	CRANtransition *_CRANtransition = ( CRANtransition * ) calloc( 1, sizeof( CRANtransition ) );
	//
	_CRANtransition->_counter = 0;
	cranRectangle(_CRANtransition->_positionSpriteToHide, 0, 0, cran->_screenHeight, cran->_screenWidth);
	if (p_transition_direction == CR_TRANSITION_TO_LEFT){
        cranRectangle(_CRANtransition->_positionSpriteToShow, 0, 0, -cran->_screenWidth, cran->_screenHeight);
	} else if (p_transition_direction == CR_TRANSITION_TO_RIGHT){
		cranRectangle(_CRANtransition->_positionSpriteToShow, cran->_screenWidth, 0, (cran->_screenWidth*2), cran->_screenHeight);
	}
	_CRANtransition->_spriteToShow = p_sprite_show;
	_CRANtransition->_spriteToHide = p_sprite_hide;
}
*/