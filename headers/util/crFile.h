#ifndef __CRAN_UTIL_FILE_H__
#define __CRAN_UTIL_FILE_H__

#include "crPrerequisites.h"
extern "C"{
    #include "commons.h"
}

namespace Cran {
    namespace Util {
        class File{
        public:
            static FILE *open(const char *p_filename, const char *p_mode);
            static void read(FILE *p_file, char *p_stream);
            static CRbool exist(const char *p_filename);
        };
    }
}
#endif
