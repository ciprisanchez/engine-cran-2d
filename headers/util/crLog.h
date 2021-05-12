#ifndef __CRAN_UTIL_LOG_H__
#define __CRAN_UTIL_LOG_H__

#ifdef ANDROID_ENVIRONMENT
#include <android/log.h>
#define  LOG_TAG    "cran_engine"
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)
#endif

#include "crPrerequisites.h"
extern "C"{
    #include "commons.h"
}
#include "util/crString.h"
#include "util/crTime.h"

namespace Cran {
    namespace Util {
        class Log{
        public:
            static void writeLogDebug(const char *p_message, ...);
            static void writeLogError(const char *p_message, ...);
            static void writeLogInfo(const char *p_message, ...);
        };
    }
}
#endif
