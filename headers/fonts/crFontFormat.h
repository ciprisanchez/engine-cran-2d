#ifndef __CRAN_FONT_FORMAT_H__
#define __CRAN_FONT_FORMAT_H__

#include "cran.h"
#include "core/crColor.h"

class CranFontFormat : public CranObject
{
public:
    CranFontFormat();
    ~CranFontFormat();
    //
    void load(Color *p_color, int p_align, int p_size, int p_gap);
    //
	Color*          _color;
	int             _align;
	int				_size;
	int				_gap;
};

#endif
