#include "math/crRectangle.h"

using namespace Cran::Math;

Rectangle::Rectangle()
{
	_x1 = 0.0f;
	_y1 = 0.0f;
	_x2 = 0.0f;
	_y2 = 0.0f;
}

Rectangle::Rectangle(CRfloat p_x1, CRfloat p_y1, CRfloat p_x2, CRfloat p_y2)
{
	_x1 = p_x1;
	_y1 = p_y1;
	_x2 = p_x2;
	_y2 = p_y2;
}

Rectangle::~Rectangle()
{
}


void Rectangle::setValues(CRfloat p_x1, CRfloat p_y1, CRfloat p_x2, CRfloat p_y2)
{
	_x1 = p_x1;
	_y1 = p_y1;
	_x2 = p_x2;
	_y2 = p_y2;
}

CRbool Rectangle::isInside(Vector2 *p_vector)
{
	if ((p_vector->_x >= _x1) &&
		(p_vector->_x <= _x2) &&
		(p_vector->_y >= _y1) &&
		(p_vector->_y <= _y2)){
		return CR_TRUE;
	}
	//
	return CR_FALSE;
}

Rectangle & Rectangle::operator=(const Rectangle &p_rectangle)
{
	// *** Check for self-assignment
	if (this != &p_rectangle) {
		_x1 = p_rectangle._x1;
		_y1 = p_rectangle._y1;
		_x2 = p_rectangle._x2;
		_y2 = p_rectangle._y2;
    }
	return *this;
}

CRbool Rectangle::operator==(const Rectangle &p_rectangle) const
{
    if (p_rectangle._x1 == _x1 && p_rectangle._x2  == _x2 && p_rectangle._y1  == _y1 && p_rectangle._y2 == _y2 ){
		return CR_TRUE;
	} else {
		return CR_FALSE;
	}
}

CRbool Rectangle::operator!=(const Rectangle &p_rectangle) const
{
	if (p_rectangle._x1 != _x1 || p_rectangle._x2  != _x2 || p_rectangle._y1  != _y1 || p_rectangle._y2 != _y2 ){
		return CR_TRUE;
	} else {
		return CR_FALSE;
	}
}

CRbool Rectangle::operator>(const Rectangle &p_rectangle) const
{
	if ((_x1 < p_rectangle._x1 && _x1 > p_rectangle._x2) &&
		(_x2 < p_rectangle._x1 && _x2 > p_rectangle._x2) &&
		(_y1 < p_rectangle._y1 && _y1 > p_rectangle._y2) &&
		(_y2 < p_rectangle._y1 && _y2 > p_rectangle._y2)){
		return CR_TRUE;
	} else {
		return CR_FALSE;
	}
}

CRbool Rectangle::operator<(const Rectangle &p_rectangle) const
{
	if ((_x1 > p_rectangle._x1 && _x1 < p_rectangle._x2) &&
		(_x2 > p_rectangle._x1 && _x2 < p_rectangle._x2) &&
		(_y1 > p_rectangle._y1 && _y1 < p_rectangle._y2) &&
		(_y2 > p_rectangle._y1 && _y2 < p_rectangle._y2)){
		return CR_TRUE;
	} else {
		return CR_FALSE;
	}
}

CRbool Rectangle::operator>=(const Rectangle &p_rectangle) const
{
	if ((_x1 <= p_rectangle._x1 && _x1 >= p_rectangle._x2) &&
		(_x2 <= p_rectangle._x1 && _x2 >= p_rectangle._x2) &&
		(_y1 <= p_rectangle._y1 && _y1 >= p_rectangle._y2) &&
		(_y2 <= p_rectangle._y1 && _y2 >= p_rectangle._y2)){
		return CR_TRUE;
	} else {
		return CR_FALSE;
	}
}

CRbool Rectangle::operator<=(const Rectangle &p_rectangle) const
{
	if ((_x1 >= p_rectangle._x1 && _x1 <= p_rectangle._x2) &&
		(_x2 >= p_rectangle._x1 && _x2 <= p_rectangle._x2) &&
		(_y1 >= p_rectangle._y1 && _y1 <= p_rectangle._y2) &&
		(_y2 >= p_rectangle._y1 && _y2 <= p_rectangle._y2)){
		return CR_TRUE;
	} else {
		return CR_FALSE;
	}
}