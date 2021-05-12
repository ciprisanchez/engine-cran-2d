#ifndef CRAN_SHADER_H
#define CRAN_SHADER_H

#include <string>
#include "crPrerequisites.h"
#include "core/crObject.h"
#include "util/crLog.h"
#include "render/crOpenGLES2.h"
extern "C"{
    #include "commons.h"
}

class CranShader : public CranObject
{
public:
    CranShader();
    ~CranShader();
    
    
    void load(int p_shader);
    void useProgram();
    void updateMatrix4fv(GLuint p_program, const char* p_matrixName, float *p_modelViewMatrix);
    //void update_shader_2d(GLuint p_program, float *p_modelViewMatrix);
	CRuint			_program;				// Compiled program for shader use
	int        _shader;
    
private:
	//
	CRuint			_activeUniforms;		// Number of active uniforms variables in the shader
	CRuint			_maxLenNameUniform;		// Max lenght of name uniform variable
	CRuint			_vertexShader;
	CRuint			_fragmentShader;
	
    //
    CRuint loadExt(const char* p_vertexShaderSource, const char* p_fragmentShaderSource);
    CRuint createProgram(const char* p_vertexShaderSource, const char* p_fragmentShaderSource);
};

#endif
