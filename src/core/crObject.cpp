#include "cran.h"
#include "core/crObject.h"
#include "util/crString.h"

using namespace Cran::Util;

// *** Constructor
CranObject::CranObject()
{
    String::init(&_filename);
}

// *** Destructor
CranObject::~CranObject()
{
    delete _filename;
}

void CranObject::getPathResource(const char* p_filename)
{
	#ifdef IPHONE_ENVIRONMENT
		Cran::Util::String::copy(_filename, CRAN_STRING_BLANK);
	    Cran::Util::String::concat(_filename, CranEngine::Instance()->getPathResource());
	    Cran::Util::String::concat(_filename, p_filename);
	#endif
	#ifdef ANDROID_ENVIRONMENT
	    Cran::Util::String::copy(_filename, CRAN_STRING_BLANK);
	    Cran::Util::String::concat(_filename, p_filename);
	#endif
}

// *** Attribute id
CRuint CranObject::getId()
{
	return _id;
}

void CranObject::setId(CRuint p_id)
{
	this->_id = p_id;
}

// *** CRAN ENGINE calling methods
void CranObject::updateShader(float *p_modelViewMatrix)
{
    CranEngine::Instance()->updateShader(p_modelViewMatrix);
    //cranEngine->_activeShader->updateMatrix4fv(cranEngine->_activeShader->_program, "modelViewMatrix", modelView);
}

void CranObject::addToResourceManager(int p_type)
{
    CranEngine::Instance()->addResource(p_type, this);
}

void CranObject::removeFromResourceManager(int p_type)
{
    CranEngine::Instance()->removeResource(p_type, this);
}

CranObject* CranObject::getFromResourceManager(int p_type, CRuint p_id)
{
    return CranEngine::Instance()->getResource(p_type, p_id);
}

#ifdef ANDROID_ENVIRONMENT
zip* CranObject::getAPKFile()
{
    return CranEngine::Instance()->getZipFile();
}
#endif
