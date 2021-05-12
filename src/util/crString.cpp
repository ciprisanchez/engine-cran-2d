#include "util/crString.h"

using namespace Cran::Util;

void Cran::Util::String::init(char **p_char)
{
    *p_char = (char*) malloc (CRAN_STRING_MAX_SIZE);
}

void Cran::Util::String::init(char **p_char, int p_length)
{
    *p_char = (char*) malloc (p_length);
}

void Cran::Util::String::release(char **p_char)
{
    free(*p_char);
}

void Cran::Util::String::copy( char *p_destination, const char *p_source )
{
	memcpy( p_destination, p_source, length( p_source ) + 1 );
}

void Cran::Util::String::concat( char *p_str1, const char *p_str2 )
{
	int i, j;
	//
	i = j = 0;
	// Find end of p_str1
	while (p_str1[i] != '\0'){
		i++;
	}
	//
	do{
		// Copy p_str2 to p_str1
		p_str1[i++] = p_str2[j++];
	} while ( p_str1[i-1] != '\0');	
    
}

CRuint Cran::Util::String::length( const char *p_str )
{
	CRuint i = 0;
	while( p_str[ i ] )
	{ ++i; }
	
	return i;
}

int Cran::Util::String::compare( const char *_str1, const char *_str2 )
{
	unsigned int s = length( _str2 );
	
	if( *_str1 != *_str2 )
	{ return 1; }
	
	return memcmp( _str1, _str2, s + 1 );
}

// *** Search _str1 into _str2.
CRbool Cran::Util::String::startsWith( const char *_str1, const char *_str2 )
{
	CRbool isFound = CR_FALSE;
	CRuint i = 0;
	CRuint s = length( _str2 );
	//
	while ( i < s ){
		if( *_str1 == *_str2 ){
			*_str1++;
			*_str2++;
			isFound = CR_TRUE;
		} else {
			isFound = CR_FALSE;
			break;
		}
		i++;
	}
    
	return isFound;
}

char* Cran::Util::String::contains( char *_str1, char _str2 )
{
	while( *_str1 )
	{
		++_str1;
		if( *_str1 == _str2 )
		{ return _str1; }
	}
	return NULL;
}

char* Cran::Util::String::token( char *_str1, char *_str2 )
{
	unsigned int s = length( _str2 );
    
	while( *_str1 )
	{
		if( *_str1 == *_str2 )
		{
			if( s == 1 )
			{ return _str1; }
			
			if( !memcmp( _str1, _str2, s ) )
			{ return _str1; }
		}
		
		++_str1;		
	}
    
	return NULL;
}

void Cran::Util::String::format(char *p_str, CR_STRING p_mode)
{
	CRuint i = 0;
	CRuint s = length( p_str );
    
	if (p_mode == CR_STRING_LZEROES)
	{
		while( i < s )
		{
			if (p_str[ i ] == '0'){
				p_str[ i ] = ' ';
			} else {
				break;
			}
			++i;
		}
	}
}
/*
void Cran::Util::String::toUpper( char *_str )
{
	unsigned int i = 0,
    s = length( _str );
    
	while( i != s )
	{
		//_str[ i ] = toupper( _str[ i ] );
		_str[ i ] = (char)toupper( _str[ i ] );
		++i;
	}
}*/

void Cran::Util::String::reverse(char *p_out, const char *p_in)
{
    int i, j;
    char c;
    int length = strlen(p_in);
    for (i = 0, j = length-1; i<=j; i++, j--) {
        c = p_in[i];
        p_out[i] = p_in[j];
        p_out[j] = c;
    }
	p_out[length]='\0';
}

void Cran::Util::String::reverse(char s[])
{
    int i, j;
    char c;
    
    for (i = 0, j = strlen(s)-1; i<j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}

int Cran::Util::String::toInt(char *c, int p_char_size) {
	int result = 0;
	int size = 0;
	while ( (*c >= '0' && *c <= '9') && (size < p_char_size) ){
		result = result * 10 + *c++ - '0';
		size++;
	}
	return result;
}

void Cran::Util::String::toChar(long n, char s[])
{
    int i, sign;
    if ((sign = n) < 0)  // record sign 
        n = -n;          // make n positive
    i = 0;
    do {      // generate digits in reverse order
        s[i++] = n % 10 + '0';  // get next digit
    } while ((n /= 10) > 0);    // delete it
    if (sign < 0)
        s[i++] = '-';
    s[i] = '\0';
    reverse(s);
}

void Cran::Util::String::toChar(long n, char s[], int p_long_size)
{
    int i, sign;
    if ((sign = n) < 0)  // record sign
        n = -n;          // make n positive
    i = 0;
    do {      // generate digits in reverse order
        s[i++] = n % 10 + '0';  // get next digit
    } while ((n /= 10) > 0);    // delete it
	while (i < p_long_size){
		s[i++] = ' ';
	}
	if (sign < 0){
		s[i++] = '-';
	}
    s[i] = '\0';
    reverse(s);
}

void Cran::Util::String::toChar(long n, char s[], int p_long_size, char p_fill)
{
    int i, sign;
    if ((sign = n) < 0)  // record sign
        n = -n;          // make n positive
    i = 0;
    do {      // generate digits in reverse order
        s[i++] = n % 10 + '0';  // get next digit
    } while ((n /= 10) > 0);    // delete it
	while (i < p_long_size){
		s[i++] = p_fill;
	}
	if (sign < 0){
		s[i++] = '-';
	}
    s[i] = '\0';
    reverse(s);
}
