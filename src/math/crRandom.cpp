#include "math/crRandom.h"

using namespace Cran::Math;

void Random::initOnTime()
{
#ifdef IPHONE_ENVIRONMENT
	struct tm *tlocal;
	int seed;
	// *** Get local time
	time_t tiempo = time(0);
	// *** Parse local time to a struct
	tlocal = localtime(&tiempo);
	// *** Get random seed base on actual time
	seed = (((tlocal->tm_min * 60) + tlocal->tm_sec) * tiempo)/2;
	//
	srand ( seed );
#endif
#ifdef ANDROID_ENVIRONMENT
	struct tm *tlocal;
	int seed;
	// *** Get local time
	time_t tiempo = time(0);
	// *** Parse local time to a struct
	tlocal = localtime(&tiempo);
	// *** Get random seed base on actual time
	seed = (((tlocal->tm_min * 60) + tlocal->tm_sec) * tiempo)/2;
	//
	srand ( seed );
#endif
#ifdef WINDOWS_ENVIRONMENT
	struct tm newtime;
	errno_t error;
	int seed;
	// *** Get local time
	time_t tiempo = time(0);
	// *** Parse local time to a struct
	error = localtime_s(&newtime, &tiempo);
	localtime_s(&newtime, &tiempo);
	// *** Get random seed base on actual time
	seed = (int)( (((newtime.tm_min * 60) + newtime.tm_sec) * tiempo)/2);
	//
	std::srand ( seed );
#endif
}

void Random::init( int p_seed )
{
	srand( p_seed );
}

CRint Random::getNumberInRange(CRint p_min, CRint p_range)
{
	// The random number is obtained from (p_min) to (p_min + p_range).
	CRint number;
	number = rand() % p_range + p_min;
	return number;
}
