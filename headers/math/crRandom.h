#ifndef __CRAN_MATH_RANDOM_H__
#define __CRAN_MATH_RANDOM_H__

#include "crPrerequisites.h"
extern "C"{
    #include "commons.h"
}
#include <ctime>
#include <cstdlib>

namespace Cran {
	namespace Math{
        class Random {
    
        public:
            static void init(int p_seed);
            static void initOnTime();
            static CRint getNumberInRange(CRint p_min, CRint p_range);
        };
    }
}

#endif