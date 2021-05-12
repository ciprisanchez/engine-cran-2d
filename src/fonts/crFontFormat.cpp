#include "fonts/crFontFormat.h"

CranFontFormat::CranFontFormat()
{
    _color = new Color();
    _align = CR_FONT_ALIGN_LEFT;
    _size = 32;
    _gap = 16;
}

CranFontFormat::~CranFontFormat()
{
    delete _color;
}

//
void CranFontFormat::load(Color *p_color, int p_align, int p_size, int p_gap)
{
    _color->setValues(p_color->_red, p_color->_green, p_color->_blue, p_color->_alpha);
    _size = p_size;
    _align = p_align;
    _gap = p_gap;
}
