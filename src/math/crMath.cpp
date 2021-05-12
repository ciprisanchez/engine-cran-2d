#include "math/crMath.h"

CRuint Cran::Math::Math::pow2(CRuint p_number)
{
	register CRuint p2;
	for (p2=1; p2<p_number; p2<<=1);
	return p2;
}
