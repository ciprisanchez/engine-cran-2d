#include "math/crVector2.h"

using namespace Cran::Math;

Cran::Math::Vector2::Vector2()
{
}

Cran::Math::Vector2::Vector2(CRfloat p_x, CRfloat p_y)
{
	_x = p_x;
	_y = p_y;
}

Cran::Math::Vector2::~Vector2()
{
}

void Cran::Math::Vector2::zero()
{
	_x = 0.0f;
	_y = 0.0f;
}

void Cran::Math::Vector2::setValues(CRfloat p_x, CRfloat p_y)
{
    _x = p_x;
	_y = p_y;
}

Vector2 & Vector2::operator=(const Vector2 &p_vector2)
{
	_x = p_vector2._x;
    _y = p_vector2._y;
    return *this;
}

Vector2 & Vector2::operator-(const Vector2 &p_vector2)
{
	_x = _x - p_vector2._x;
	_y = _y - p_vector2._y;
    return *this;
}

CRbool Vector2::operator==(const Vector2 &p_vector2) const
{
	if (_x == p_vector2._x && _y == p_vector2._y){
		return CR_TRUE;
	} else {
		return CR_FALSE;
	}
}