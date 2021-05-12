#ifndef __CRAN_UTIL_STRING_H__
#define __CRAN_UTIL_STRING_H__

#include "crPrerequisites.h"
extern "C"{
    #include "commons.h"
}
#include <string>

namespace Cran {
	namespace Util {
		class String{
		
		public:
            static void init(char **p_char);
            static void init(char **p_char, int p_length);
            static void release(char **p_char);
			static void copy( char *p_destination, const char *p_source );
			static void concat( char *p_str1, const char *p_str2 );
			static CRuint length( const char *p_str );
			static CRbool startsWith( const char *_str1, const char *_str2 );
			static int compare( const char *_str1, const char *_str2 );
			static char *contains( char *_str1, char _str2 );
			static char *token( char *_str1, char *_str2 );
			static void format(char *p_str, CR_STRING p_mode);
			static void toUpper( char *_str );
			static void reverse(char *p_out, const char *p_in);
			static void reverse(char s[]);
			static int toInt(char *c, int p_char_size);
			static void toChar(long n, char s[]);
			static void toChar(long n, char s[], int p_long_size);
            static void toChar(long n, char s[], int p_long_size, char p_fill);
		};
	}
}

#endif
