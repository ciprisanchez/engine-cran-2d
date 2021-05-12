#include "util/crLog.h"

using namespace Cran::Util;

void Cran::Util::Log::writeLogDebug(const char *p_message, ...)
{
#ifdef CRAN_DEBUG_HIGH
    char *time;
    String::init(&time);
    Time::getHHMMSS(&time);
	#ifdef IPHONE_ENVIRONMENT
		printf("DEBUG - %s - %s\n", time, p_message);
	#endif
	#ifdef ANDROID_ENVIRONMENT
		LOGD("DEBUG - %s - %s\n", time, p_message);
	#endif
	#ifdef WINDOWS_ENVIRONMENT
		printf("DEBUG - %s - %s\n", time, p_message);
	#endif
    String::release(&time);
#endif
}

void Cran::Util::Log::writeLogError(const char *p_message, ...)
{
    char *time;
    String::init(&time);
    Time::getHHMMSS(&time);
	#ifdef IPHONE_ENVIRONMENT
		printf("ERROR - %s - %s\n", time, p_message);
	#endif
	#ifdef ANDROID_ENVIRONMENT
		LOGE("ERROR - %s - %s\n", time, p_message);
	#endif
	#ifdef WINDOWS_ENVIRONMENT
		printf("ERROR - %s - %s\n", time, p_message);
	#endif
    String::release(&time);
}

void Cran::Util::Log::writeLogInfo(const char *p_message, ...)
{
    char *time;
    String::init(&time);
    Time::getHHMMSS(&time);
	#ifdef IPHONE_ENVIRONMENT
		printf("INFO - %s - %s\n", time, p_message);
	#endif
	#ifdef ANDROID_ENVIRONMENT
		LOGI("INFO - %s - %s\n", time, p_message);
	#endif
	#ifdef WINDOWS_ENVIRONMENT
		printf("INFO - %s - %s\n", time, p_message);
	#endif
    String::release(&time);
}
