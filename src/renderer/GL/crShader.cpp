#include "render/crShader.h"

using namespace Cran::Util;

std::string VERTEX_SHADER_2D = "                                            \
    attribute vec4 position;                                                \
    attribute vec2 textureCoordIn;                                          \
    varying vec2 vTextureCoordOut;                                          \
    uniform mediump mat4 modelViewMatrix;                                   \
    void main()                                                             \
    {                                                                       \
        gl_Position = modelViewMatrix * position;                           \
        vTextureCoordOut = textureCoordIn;                                  \
    }";

std::string FRAGMENT_SHADER_2D = "                                          \
    varying mediump vec2 vTextureCoordOut;                                  \
    uniform sampler2D sampler;                                              \
    void main()                                                             \
    {                                                                       \
        gl_FragColor = texture2D(sampler, vTextureCoordOut);                \
    }";

std::string VERTEX_SHADER_COLOR_2D = "                                      \
    attribute vec4 position;                                                \
    attribute vec4 color;                                                   \
    attribute vec2 textureCoordIn;                                          \
    varying vec2 vTextureCoordOut;                                          \
    varying vec4 vfColor;                                                   \
    uniform mediump mat4 modelViewMatrix;                                   \
    void main()                                                             \
    {                                                                       \
        gl_Position = modelViewMatrix * position;                           \
        vfColor = color;                                                    \
        vTextureCoordOut = textureCoordIn;                                  \
    }";

std::string FRAGMENT_SHADER_COLOR_2D = "                                    \
    varying lowp vec4 vfColor;                                              \
    varying mediump vec2 vTextureCoordOut;                                  \
    uniform sampler2D sampler;                                              \
    void main()                                                             \
    {                                                                       \
        gl_FragColor = texture2D(sampler, vTextureCoordOut);                \
        if (gl_FragColor.a > 0.0)                                           \
        {                                                                   \
            gl_FragColor = vfColor;                                         \
        }                                                                   \
    }";


CranShader::CranShader()
{
	//
	_program = 0;
	_activeUniforms = 0;
	_maxLenNameUniform = 0;
	_vertexShader = 0;
	_fragmentShader = 0;
	_shader = CR_SHADER_NONE;
	//
    addToResourceManager(CRAN_SHADER);
}

CranShader::~CranShader()
{
    Cran::Render::GLES2::crGlDetachShader(_program, _vertexShader);
	Cran::Render::GLES2::crGlDetachShader(_program, _fragmentShader);
	Cran::Render::GLES2::crGlDeleteShader(_vertexShader);
	Cran::Render::GLES2::crGlDeleteShader(_fragmentShader);
	Cran::Render::GLES2::crGlDeleteProgram(_program);
}

void CranShader::updateMatrix4fv(GLuint p_program, const char* p_matrixName, float *p_modelViewMatrix)
{	
    Cran::Render::GLES2::crGlUniformMatrix4fv(p_program, p_matrixName, p_modelViewMatrix);	

}

void CranShader::load(int p_shader)
{
	const char* vertexShaderSource;
	const char* fragmentShaderSource;
	//
	if (p_shader == CR_SHADER_2D){
		vertexShaderSource = VERTEX_SHADER_2D.c_str();
		fragmentShaderSource = FRAGMENT_SHADER_2D.c_str();
    
    } else if (p_shader == CR_SHADER_COLOR){
        vertexShaderSource = VERTEX_SHADER_COLOR_2D.c_str();
		fragmentShaderSource = FRAGMENT_SHADER_COLOR_2D.c_str();
        
    } else {
        vertexShaderSource = VERTEX_SHADER_2D.c_str();
		fragmentShaderSource = FRAGMENT_SHADER_2D.c_str();
    }
    //
    _program = loadExt(vertexShaderSource, fragmentShaderSource);
    _shader = p_shader;
}

void CranShader::useProgram(){
    
    Cran::Render::GLES2::crGlUseProgram(_program);
}

CRuint CranShader::loadExt(const char* p_vertexShaderSource, const char* p_fragmentShaderSource)
{
	CRuint programHandle = createProgram(p_vertexShaderSource, p_fragmentShaderSource);
	if (programHandle != CR_FALSE){
		Log::writeLogDebug("CranShader - loadExt - OK");
		return programHandle;
	} else {
		Log::writeLogError("CranShader - loadExt - Not program handler created");
		return CR_FALSE;
	}
}

CRuint CranShader::createProgram(const char* p_vertexShaderSource, const char* p_fragmentShaderSource)
{	
	//
	GLuint programHandle = Cran::Render::GLES2::crGlCreateProgram(); 
	//
	GLuint vertexShader = Cran::Render::GLES2::crGlCreateShader(p_vertexShaderSource, GL_VERTEX_SHADER); 
	GLuint fragmentShader = Cran::Render::GLES2::crGlCreateShader(p_fragmentShaderSource, GL_FRAGMENT_SHADER);

	_vertexShader = vertexShader;
	_fragmentShader = fragmentShader;
	//
	Cran::Render::GLES2::crGlAttachShader(programHandle, vertexShader);
	Cran::Render::GLES2::crGlAttachShader(programHandle, fragmentShader);
	//
	Cran::Render::GLES2::crGlBindAttribLocation(programHandle, CR_ATTRIB_POSITION_INDEX, CR_ATTRIB_POSITION);
	Cran::Render::GLES2::crGlBindAttribLocation(programHandle, CR_ATTRIB_COLOR_INDEX, CR_ATTRIB_COLOR);
	Cran::Render::GLES2::crGlBindAttribLocation(programHandle, CR_ATTRIB_TEXCOORD0_INDEX, CR_ATTRIB_TEXCOORD0); 
	/*
	glBindAttribLocation(programHandle, CR_ATTRIB_POSITION_INDEX, CR_ATTRIB_POSITION);
	glBindAttribLocation(programHandle, CR_ATTRIB_COLOR_INDEX, CR_ATTRIB_COLOR);
	glBindAttribLocation(programHandle, CR_ATTRIB_TEXCOORD0_INDEX, CR_ATTRIB_TEXCOORD0); 
	*/
	//
	programHandle = Cran::Render::GLES2::crGlLinkProgram(programHandle);
	if (programHandle == GL_FALSE){
		return CR_FALSE;
	} else {
		GLuint validation = Cran::Render::GLES2::crGlValidateProgram(programHandle);
		if (validation){
			return programHandle;
		} else {
			return CR_FALSE;
		}
	}
}
