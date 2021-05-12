#include "fonts/crFontScene.h"

CranFontScene::CranFontScene()
{
	_position = new Vector2(0.0f, 0.0f);
	_color = new Color(0.0f, 0.0f, 0.0f, 0.0f);
    _format = new CranFontFormat();
    //
    _actualFrame = 0;
	_frames = 0;
    _speed = 0;
	_message = 0;

    _move = CR_FALSE;
    _speedmove = 0;
	_sceneMode = 0;

}

CranFontScene::CranFontScene(Vector2* p_position, Color* p_color, CRuint p_time, CRuint p_mode, const char *p_str)
{
    _position = new Vector2(p_position->_x, p_position->_y);
	_color = new Color(p_color->_red, p_color->_green, p_color->_blue, p_color->_alpha);
    //
    _format = new CranFontFormat();
    _format->load(p_color, CR_FONT_ALIGN_RIGHT, 15, 15);
    //
	_frames = p_time;
    _speed = 10.0f / p_time;
	_sceneMode = p_mode;
	_actualFrame = 0;
    //
    String::init(&_message);
    String::copy(_message, p_str);
	//
    _move = CR_FALSE;
    _speedmove = 0.0f;
    //
	if (_sceneMode == FONT_TO_TRANSPARENT){
		_color->_alpha = 1.0f;
	} else if (_sceneMode == FONT_TO_COLOR){
		_color->_alpha = 0.0f;
	}
}


CranFontScene::~CranFontScene()
{
	delete _position;
	delete _color;
    delete _format;
    
    free(_message);
    //removeFromResourceManager(CRAN_SCENE);
}

void CranFontScene::setMove(CRuint p_speedmove)
{
    _move = CR_TRUE;
    _speedmove = p_speedmove;
}

void CranFontScene::update()
{
    _actualFrame++;
    if (_sceneMode == FONT_TO_TRANSPARENT){
		if (_color->_alpha > 0.0f){	
            _color->_alpha = _color->_alpha - _speed;
        }
	} else if (_sceneMode == FONT_TO_COLOR){
		if (_color->_alpha < 1.0f){
            _color->_alpha = _color->_alpha + _speed;
        }
	}
    //
    if (_move){
        _position->_y = _position->_y - 2.0f;
    }
}
