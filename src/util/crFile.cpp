#include "util/crFile.h"

using namespace Cran::Util;

FILE* File::open(const char *p_filename, const char *p_mode)
{
	FILE *file;
    file = fopen ( p_filename, p_mode);
	return file;
}

void File::read(FILE *p_file, char *p_stream)
{
    int c = 0;
	CRuint index = 0;
	//
	do{
		c = fgetc(p_file);
		p_stream[index] = (char)c;
		index++;
	} while(c != EOF);
}

CRbool File::exist(const char *p_filename)
{
    FILE *file;
	file = File::open(p_filename, "r");
	if (file){
		fclose(file);        
		return CR_TRUE;    
	}
	return CR_FALSE;
}
