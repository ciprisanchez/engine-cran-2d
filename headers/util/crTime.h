#ifndef __CRAN_UTIL_TIME_H__
#define __CRAN_UTIL_TIME_H__

#include "crPrerequisites.h"
extern "C"{
	#include "commons.h"
}

namespace Cran {
    namespace Util {
        class Time{
		public:
			static void getHHMMSS(char **p_cdate);
			#ifdef IPHONE_ENVIRONMENT
				static struct tm* getLocalTime();
			#endif
			#ifdef ANDROID_ENVIRONMENT
            	static struct tm* getLocalTime();
			#endif
			#ifdef WINDOWS_ENVIRONMENT
            	static struct tm getLocalTime();
			#endif
		};
	}
}

#endif
