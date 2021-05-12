#ifndef __CRAN_MATH_H__
#define __CRAN_MATH_H__

#define CR_PI						3.1415926535897932384626433832795
#define CR_PI_OVER_180				0.017453292519943295769236907684886
#define CR_PI_OVER_360				0.0087266462599716478846184538424431
#define CR_DEGREES_TO_RADIANS(x)	((CR_PI * x) / 180.0)
#define CR_RADIANS_TO_DEGREES(x)	(x * 180.0 / CR_PI)

#include "crPrerequisites.h"
extern "C"{
    #include "commons.h"
}


namespace Cran {
	namespace Math {
		class Math{
			public:
				static CRuint pow2(CRuint p_number);
		};
	}
}
#endif
