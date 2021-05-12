#include "util/crTime.h"
#include "util/crString.h"

using namespace Cran::Util;

void Cran::Util::Time::getHHMMSS(char **p_cdate)
{
	char *chh;
	char *cmm;
	char *css;
    //
    String::init(&chh, 2);
    String::init(&cmm, 2);
    String::init(&css, 2);
	//
#ifdef IPHONE_ENVIRONMENT
	struct tm *date = Cran::Util::Time::getLocalTime();
	int hh = date->tm_hour;
	int mm = date->tm_min;
	int ss = date->tm_sec;
#endif
#ifdef ANDROID_ENVIRONMENT
	struct tm *date = Cran::Util::Time::getLocalTime();
	int hh = date->tm_hour;
	int mm = date->tm_min;
	int ss = date->tm_sec;
#endif
#ifdef WINDOWS_ENVIRONMENT
	struct tm date = Cran::Util::Time::getLocalTime();
	int hh = date.tm_hour;
	int mm = date.tm_min;
	int ss = date.tm_sec;
#endif
	//
    String::toChar(hh, chh, 2, '0');
    String::toChar(mm, cmm, 2, '0');
    String::toChar(ss, css, 2, '0');
	//
    String::copy(*p_cdate, CRAN_STRING_BLANK);
    String::concat(*p_cdate, chh );
    String::concat(*p_cdate, ":" );
    String::concat(*p_cdate, cmm );
	String::concat(*p_cdate, ":" );
    String::concat(*p_cdate, css );
	//
    String::release(&chh);
    String::release(&cmm);
    String::release(&css);
}

#ifdef IPHONE_ENVIRONMENT
struct tm* Cran::Util::Time::getLocalTime()
{
	struct tm *tlocal;
    
	// *** Get local time
	time_t tiempo = time(0);
	
	// *** Parse local time to a struct
	tlocal = localtime(&tiempo);
	
	return tlocal;
}
#endif
#ifdef ANDROID_ENVIRONMENT
struct tm* Cran::Util::Time::getLocalTime()
{
	struct tm *tlocal;

	// *** Get local time
	time_t tiempo = time(0);

	// *** Parse local time to a struct
	tlocal = localtime(&tiempo);

	return tlocal;
}
#endif
#ifdef WINDOWS_ENVIRONMENT
struct tm Cran::Util::Time::getLocalTime()
{
	struct tm tlocal;
	errno_t error;
    
	// *** Get local time
	time_t tiempo = time(0);
	// *** Parse local time to a struct
	error = localtime_s(&tlocal, &tiempo);
	//
	return tlocal;
}
#endif



// ********************************************************************** FILES
/*
 static __inline FILE *cranFileOpen(const char *p_filename, const char *p_mode)
 {
 FILE *file;
 #ifdef WINDOWS_ENVIRONMENT
 fopen_s(&file, p_filename, p_mode) ; 
 #elif IPHONE_ENVIRONMENT
 file = fopen ( p_filename, p_mode) ;
 #endif
 return file;
 }
 
 static __inline void cranFileRead(FILE *p_file, char *p_stream)
 {
 int c = 0;
 CRuint index = 0;
 //
 do{
 c = fgetc(p_file);
 p_stream[index] = (char)c;
 index++;
 } while(c != EOF);
 //while((c = fgetc(p_file)) != EOF)
 //{
 //	p_stream[index] = c;
 //	index++;
 //}
 }
 
 static __inline CRbool cranFileExist(const char *p_filename)
 {
 FILE *file;
 file = cranFileOpen(p_filename, "r");
 if (file){
 fclose(file);        
 return CR_TRUE;    
 }
 return CR_FALSE;
 }
 */


//int cranGetRandomNumber(unsigned int p_range, unsigned int p_min);
//void cranGetCurrentPath();
//void cranSaveData(const char* p_filename, int p_struct_size, char *p_data, int elements);
//void cranGetIphoneVectorFromXIB(vector2 *p_coordinates, int p_x, int p_y);
//void cranGetIphoneCoordsFromXIB(CRrectangle *p_coordinates, int p_x1, int p_x2, int p_y1, int p_y2);


/*
 void cranGetIphoneVectorFromXIB(vector2 *p_coordinates, int p_x, int p_y)
 {
 #ifdef WINDOWS_ENVIRONMENT
 cranVector2(p_coordinates, (CRfloat)p_x, (CRfloat)p_y);
 #elif IPHONE_ENVIRONMENT
 vector2 *coordinates;
 int x, y;
 //
 coordinates = cranVector2Init();
 //
 x = y = 0;
 if (cranIsOrientationPortrait()){
 x = (RESOLUTION_IPHONE_WIDTH * p_x) / RESOLUTION_XIB_WIDTH;
 y = (RESOLUTION_IPHONE_HEIGHT * p_y) / RESOLUTION_XIB_HEIGHT;
 } else if (cranIsOrientationLandscape()){ 
 x = (RESOLUTION_IPHONE_HEIGHT * p_x) / RESOLUTION_XIB_HEIGHT;
 y = (RESOLUTION_IPHONE_WIDTH * p_y) / RESOLUTION_XIB_WIDTH;
 }
 //
 cranVector2(coordinates, x, y);
 //
 *p_coordinates = *coordinates;
 
 cranVector2Free(coordinates);
 #endif
 }
 
 
 void cranGetIphoneCoordsFromXIB(CRrectangle *p_coordinates, int p_x1, int p_x2, int p_y1, int p_y2)
 {
 #ifdef WINDOWS_ENVIRONMENT
 cranRectangle(p_coordinates, (CRfloat)p_x1, (CRfloat)p_x2, (CRfloat)p_y1, (CRfloat)p_y2);
 #elif IPHONE_ENVIRONMENT
 CRrectangle *coordinates;
 int x1, x2, y1, y2;
 //
 x1 = x2 = y1 = y2 = 0;
 if (cranIsOrientationPortrait()){
 x1 = (RESOLUTION_IPHONE_WIDTH * p_x1) / RESOLUTION_XIB_WIDTH;
 x2 = (RESOLUTION_IPHONE_WIDTH * p_x2) / RESOLUTION_XIB_WIDTH;
 y1 = (RESOLUTION_IPHONE_HEIGHT * p_y1) / RESOLUTION_XIB_HEIGHT;
 y2 = (RESOLUTION_IPHONE_HEIGHT * p_y2) / RESOLUTION_XIB_HEIGHT;
 } else if (cranIsOrientationLandscape()){ 
 x1 = (RESOLUTION_IPHONE_HEIGHT * p_x1) / RESOLUTION_XIB_HEIGHT;
 x2 = (RESOLUTION_IPHONE_HEIGHT * p_x2) / RESOLUTION_XIB_HEIGHT;
 y1 = (RESOLUTION_IPHONE_WIDTH * p_y1) / RESOLUTION_XIB_WIDTH;
 y2 = (RESOLUTION_IPHONE_WIDTH * p_y2) / RESOLUTION_XIB_WIDTH;
 }
 //
 cranRectangle(coordinates, x1, y1, x2, y2);
 //
 *p_coordinates = *coordinates;
 
 cranRectangleFree(coordinates);
 #endif
 }
 
 
 void cranGetCurrentPath()
 {
 #ifdef WINDOWS_ENVIRONMENT
 //
 #elif IPHONE_ENVIRONMENT
 char cCurrentPath[100];
 if (!getcwd(cCurrentPath, sizeof(cCurrentPath)))
 {
 //printf("\n- Error listando la carpeta actual: \n");
 } else {
 DIR *dp;
 struct dirent *ep;
 //
 dp = opendir (".");
 if (dp != NULL)
 {
 //printf("\n- Contenido de la carpeta actual: \n");
 while (ep = readdir (dp))
 {
 puts (ep->d_name);
 }
 (void) closedir (dp);
 }
 }
 #endif
 }
 */
