#include "cran.h"

const char* CR_PATH_APP_DEFAULT = "./";
const char* CR_PATH_DOCS_DEFAULT= "./Documents/";

// *** Init CranEngine as singleton class
CranEngine* CranEngine::_instance = 0;
CRorientation CranEngine::_screenOrientation = CR_ORIENTATION_PORTRAIT;
CRfloat CranEngine::_screenWidth = 0;
CRfloat	CranEngine::_screenHeight = 0;
CRfloat	CranEngine::_screenPixelWidth = 0;
CRfloat	CranEngine::_screenPixelHeight = 0;
CRfloat	CranEngine::_screenTextureWidth = 0;
CRfloat	CranEngine::_screenTextureHeight = 0;
const char* CranEngine::_pathZipFile = "./";

#ifdef ANDROID_ENVIRONMENT
zip* CranEngine::_zipFile = NULL;
JNIEnv* CranEngine::_env;
jobject CranEngine::_assetManager;
#endif

// ********************************************************************** CYCLE OF LIFE
// *******************************************************************************************

// *** Return an instance of the class.
CranEngine* CranEngine::Instance()
{
    if (_instance == 0){
        _instance = new CranEngine();
    }
    return _instance;
    
}

// *** Constructor of the class
CranEngine::CranEngine()
{
    // *** Initialize path variables
#ifdef IPHONE_ENVIRONMENT
    String::init(&_pathResource);
    String::init(&_pathDocuments);
    String::copy(_pathResource, getSystemPath());
    String::copy(_pathDocuments, getDocumentPath());
#endif
#ifdef ANDROID_ENVIRONMENT
    _pathResource = (char*)CR_PATH_APP_DEFAULT;
    _pathDocuments = (char*)CR_PATH_DOCS_DEFAULT;
#endif
    
    // *** Initialize resource manager
    _resourceManager = new CranResource();
}

// *** Destructor
CranEngine::~CranEngine()
{
    free(_pathResource);
    free(_pathDocuments);
    //
    delete _resourceManager;
    //
    _instance = 0;
    delete _instance;
    
#ifdef IPHONE_ENVIRONMENT
    //cranBufferFree();
#endif
    /*
     cranResourceFree();
     //
     cranFreeFT();
     free(cran->_CRANbuffer);
     free(cran);
     */
}



// **************************************************** Init modules
void CranEngine::init()
{
#ifdef CRAN_DEBUG_HIGH
    Log::writeLogDebug("cranInit","START initialization");
#endif
    
	Cran::Math::Random::initOnTime();
	setOrientation(CR_ORIENTATION_PORTRAIT);
	
	// *** Resources
	initGL();
	initSL();
    //initFT();
    
#ifdef CRAN_DEBUG_HIGH
	printf("\n------------------------------------------------ CRAN engine 2D\n");
	printf("Default values loaded: \n" );
	printf("- Environment path	-->     %s\n", ( char * )_pathResource );
	printf("- Orientation		-->		CR_ORIENTATION_PORTRAIT\n");
	printf("- Vertex attributes	-->		CR_VERTEX_ATTRIB_POS | CR_VERTEX_ATTRIB_COLOR\n");
	printf("\n--------------------------------------------------------\n");
    Log::writeLogDebug("cranInit","END initialization");
#endif
}

void CranEngine::initGL()
{
#ifdef CRAN_DEBUG_HIGH
    Log::writeLogDebug("initGL","START GL initialization");
#endif
	GLint gl_texture_size;
    //
	glGetIntegerv(GL_MAX_TEXTURE_SIZE, &gl_texture_size);
	//
#ifdef CRAN_DEBUG_HIGH
	printf("\n------------------------------------------------ OpenGL\n");
	printf("GL_VENDOR:            %s\n", ( char * )glGetString ( GL_VENDOR     ) );
	printf("GL_RENDERER:          %s\n"  , ( char * )glGetString ( GL_RENDERER   ) );
	printf("GL_VERSION:           %s\n"  , ( char * )glGetString ( GL_VERSION    ) );
	printf("GL_EXTENSIONS:        %s\n"  , ( char * )glGetString ( GL_EXTENSIONS ) );
	printf("-\n");
	printf("GL_MAX_TEXTURE_SIZE:        %i\n"  , gl_texture_size );
	printf("\n--------------------------------------------------------\n");
	Log::writeLogDebug("initGL","END GL initialization");
#endif
}

void CranEngine::initSL()
{
#ifdef CRAN_DEBUG_HIGH
    Log::writeLogDebug("initSL","START SL initialization");
#endif
	//
    CranOpenSL::Instance();
	//
#ifdef CRAN_DEBUG_HIGH
	printf("\n------------------------------------------------ OpenSL\n");
	Log::writeLogDebug("initGL","END SL initialization");
#endif
}

void CranEngine::initFT()
{
#ifdef CRAN_DEBUG_HIGH
    Log::writeLogDebug("initFT","START Freetype initialization");
#endif
	FT_Init_FreeType(&_ftlib);
	//
#ifdef CRAN_DEBUG_HIGH
	printf("\n------------------------------------------------ Freetype\n");
	printf("FREETYPE_VERSION:         %s\n", ( char * )CR_FREETYPE_VERSION );
	printf("\n--------------------------------------------------------\n");
	Log::writeLogDebug("initFT","END Freetype initialization");
#endif
}

// **************************************************** Clean
void CranEngine::cleanFT()
{
	FT_Done_FreeType(_ftlib);
}

// **************************************************** Update
void CranEngine::update()
{
}

// **************************************************** Draw
CRbool CranEngine::draw()
{
	CRbool isDrawing = CR_FALSE;
    
	// Draw animations
    
	isDrawing = _resourceManager->drawRenderable();
    //
    _resourceManager->removeRenderable();

	return isDrawing;
}

// ********************************************************************** BUFFERS
// *******************************************************************************************
void CranEngine::initBuffer(GLuint p_mainFB, GLuint p_colorRB, GLint p_widthRB, GLint p_heightRB)
{
    CranBuffer *cb = new CranBuffer();
    cb->cranBufferInit(p_mainFB, p_colorRB, p_widthRB, p_heightRB);
    _activeBufferId = cb->getId();
}

void CranEngine::setViewPortBuffer()
{
    CranBuffer *cb = (CranBuffer*)_resourceManager->get(CRAN_BUFFER, _activeBufferId);
    Cran::Render::GL::crGlViewPort(0, 0, cb->_widthRenderBuffer, cb->_heightRenderBuffer);
}

void CranEngine::beginActiveBuffer()
{
    CranBuffer *cb = (CranBuffer*)_resourceManager->get(CRAN_BUFFER, _activeBufferId);
    cb->cranBufferBindFrameBufferSystem();
}

void CranEngine::endActiveBuffer()
{
    CranBuffer *cb = (CranBuffer*)_resourceManager->get(CRAN_BUFFER, _activeBufferId);
    cb->cranBufferRenderToBufferSystem();
}


void CranEngine::setIosController(void *p_self)
{
    _iosViewController = p_self;
}

// ********************************************************************** SET METHODS
// *******************************************************************************************
FT_Library CranEngine::getFTLibrary()
{
    return _ftlib;
}

void CranEngine::showKeyboardPanel()
{
#ifdef IPHONE_ENVIRONMENT
	cranShowAlert(_iosViewController);
#endif
    
}


void CranEngine::loadShader(int p_shader)
{
#ifdef CRAN_DEBUG_HIGH
    Log::writeLogDebug("loadShader","START loadShader");
#endif
    CranShader *crs = new CranShader();
    crs->load(p_shader);
    _activeShaderId = crs->getId();
#ifdef CRAN_DEBUG_HIGH
    Log::writeLogDebug("loadShader","END loadShader");
#endif
}

void CranEngine::useShader(int p_shader)
{
#ifdef CRAN_DEBUG_HIGH
    Log::writeLogDebug("useShader","START useShader");
#endif
    CranShader *crs = _resourceManager->getShader(p_shader);
    crs->useProgram();
#ifdef CRAN_DEBUG_HIGH
    Log::writeLogDebug("useShader","END useShader");
#endif
}

void CranEngine::updateShader(float *p_modelViewMatrix)
{
#ifdef CRAN_DEBUG_HIGH
    Log::writeLogDebug("updateShader","START updateShader");
#endif
    CranShader *crs = (CranShader*)_resourceManager->get(CRAN_SHADER, _activeShaderId);
    crs->updateMatrix4fv(crs->_program, "modelViewMatrix", p_modelViewMatrix);
#ifdef CRAN_DEBUG_HIGH
    Log::writeLogDebug("updateShader","END updateShader");
#endif
}

void CranEngine::addResource(int p_resource, CranObject *p_object)
{
    _resourceManager->add(p_resource, p_object);
}

void CranEngine::removeResource(int p_resource, CranObject *p_object)
{
    _resourceManager->remove(p_resource, p_object);
}


CranObject* CranEngine::getResource(int p_resource, CRuint p_id)
{
    return _resourceManager->get(p_resource, p_id);
}

const char* CranEngine::getPathDocuments()
{
    return _pathDocuments;
}

const char* CranEngine::getPathResource()
{
    return _pathResource;
}

// ********************************************************************** STATIC METHODS
// *******************************************************************************************
#ifdef ANDROID_ENVIRONMENT
JNIEnv* CranEngine::getJavaEnvironment()
{
	return _env;
}

jobject CranEngine::getAssetManager()
{
	return _assetManager;
}

void CranEngine::setAssetManager(jobject p_assetManager)
{
	_assetManager = p_assetManager;
}

void CranEngine::setJavaEnvironment(JNIEnv* p_env)
{
	_env = p_env;
}

zip* CranEngine::getZipFile()
{
	return _zipFile;
}

void CranEngine::setZipFile(const char* p_filename)
{
	_pathZipFile = p_filename;
	_zipFile = zip_open(_pathZipFile, 0, NULL);
}

void CranEngine::listZipFile()
{
	int numFiles = zip_get_num_files(_zipFile);
	for (int i=0; i<numFiles; i++) {
		const char* name = zip_get_name(_zipFile, i, 0);
		if (name == NULL) {
            Log::writeLogError("Error reading zip file name at index %i : %s", zip_strerror(_zipFile));
			return;
		} else {
            Log::writeLogInfo("File %i : %s\n", i, name);
		}
	}
}
#endif

void CranEngine::setOrientation(int width, int height, CRorientation p_orientation)
{
    _screenOrientation = p_orientation;
	//
	if (p_orientation == CR_ORIENTATION_PORTRAIT){
		// Init screen resolution
#ifdef IPHONE_ENVIRONMENT
        _screenWidth = RESOLUTION_IPHONE_WIDTH;
        _screenHeight = RESOLUTION_IPHONE_HEIGHT;
#endif
#ifdef ANDROID_ENVIRONMENT
        _screenWidth = width;
        _screenHeight = height;
#endif
	} else if (p_orientation == CR_ORIENTATION_LANDSCAPE){
		// Init screen resolution
#ifdef IPHONE_ENVIRONMENT
        _screenWidth = RESOLUTION_IPHONE_HEIGHT;
        _screenHeight = RESOLUTION_IPHONE_WIDTH;
#endif
#ifdef ANDROID_ENVIRONMENT
        _screenWidth = height;
        _screenHeight = width;
#endif
	}

	// Translate screen size(in pixels) to Opengl coordinates(in units from -1.0f to 1.0f).
	_screenPixelWidth = OPENGL_SCREEN_SIZE / _screenWidth;
	_screenPixelHeight = -OPENGL_SCREEN_SIZE / _screenHeight;

    _screenTextureWidth = OPENGL_TEXTURE_SIZE / _screenWidth;
    _screenTextureHeight = OPENGL_TEXTURE_SIZE / _screenWidth;
}

void CranEngine::setOrientation(CRorientation p_orientation)
{
    _screenOrientation = p_orientation;
	//
	if (p_orientation == CR_ORIENTATION_PORTRAIT){
		// Init screen resolution
#ifdef IPHONE_ENVIRONMENT
        _screenWidth = RESOLUTION_IPHONE_WIDTH;
        _screenHeight = RESOLUTION_IPHONE_HEIGHT;
#endif
#ifdef ANDROID_ENVIRONMENT
        _screenWidth = 800;
        _screenHeight = 600;
#endif
	} else if (p_orientation == CR_ORIENTATION_LANDSCAPE){
		// Init screen resolution
#ifdef IPHONE_ENVIRONMENT
        _screenWidth = RESOLUTION_IPHONE_HEIGHT;
        _screenHeight = RESOLUTION_IPHONE_WIDTH;
#endif
#ifdef ANDROID_ENVIRONMENT
        _screenWidth = 800;
        _screenHeight = 600;
#endif
	}
    
	// Translate screen size(in pixels) to Opengl coordinates(in units from -1.0f to 1.0f).
	_screenPixelWidth = OPENGL_SCREEN_SIZE / _screenWidth;
	_screenPixelHeight = -OPENGL_SCREEN_SIZE / _screenHeight;
    
    _screenTextureWidth = OPENGL_TEXTURE_SIZE / _screenWidth;
    _screenTextureHeight = OPENGL_TEXTURE_SIZE / _screenWidth;
}

CRbool CranEngine::isOrientationPortrait()
{
	if (_screenOrientation == CR_ORIENTATION_PORTRAIT){
		return CR_TRUE;
	} else {
		return CR_FALSE;
	}
}

CRbool CranEngine::isOrientationLandscape()
{
	if (_screenOrientation == CR_ORIENTATION_LANDSCAPE){
		return CR_TRUE;
	} else {
		return CR_FALSE;
	}
}

CRfloat CranEngine::convertPxToGl(CRaxis p_axis, CRint p_position)
{
    CRfloat gl_screen_coordinates = 0.0f;
    //
    if (p_axis == CR_AXIS_X){
        gl_screen_coordinates = ((p_position - _screenWidth) * _screenPixelWidth)+1.0f;
    } else if (p_axis == CR_AXIS_Y){
        gl_screen_coordinates = ((p_position - _screenHeight) * _screenPixelHeight)-1.0f;
    }
    //
    return gl_screen_coordinates;
}

CRfloat CranEngine::convertPxToTxGl(CRaxis p_axis, CRint p_position)
{
    CRfloat gl_texture_coordinates = 0.0f;
    //
    if (p_axis == CR_AXIS_X){
        gl_texture_coordinates = p_position * _screenTextureWidth;
    } else if (p_axis == CR_AXIS_Y){
        gl_texture_coordinates = p_position * _screenTextureHeight;
    }
    //
    return gl_texture_coordinates;
}

CRfloat CranEngine::getScreenWidth()
{
    return _screenWidth;
}

CRfloat CranEngine::getScreenHeight()
{
    return _screenHeight;
}

CRfloat CranEngine::getPixelWidth()
{
    return _screenPixelWidth;
}

CRfloat CranEngine::getPixelHeight()
{
    return _screenPixelHeight;
}


