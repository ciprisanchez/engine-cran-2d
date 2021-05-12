#ifndef __CRAN_OBJECT_H__
#define __CRAN_OBJECT_H__

#include "crPrerequisites.h"
extern "C"{
    #include "commons.h"
}

class CranObject
{
public:
    CranObject();
    ~CranObject();

	CRuint getId();
    void setId(CRuint p_id);

protected:
    //char                _filename[CRAN_STRING_MAX_SIZE];
    char*               _filename;
    zip_file*			_zipfilename;
    
    // *** CranEngine calling methods
	void addToResourceManager(int p_type);
    void removeFromResourceManager(int p_type);
    CranObject* getFromResourceManager(int p_type, CRuint p_id);
    
    void updateShader(float *p_modelViewMatrix);
    void getPathResource(const char* p_filename);
    
    #ifdef ANDROID_ENVIRONMENT
    zip* getAPKFile();
#endif
        
private:
	CRuint          _id;

};

#endif
