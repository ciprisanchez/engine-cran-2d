#include "render/crOpenGLES2.h"
#include "stdlib.h"

using namespace Cran::Render;

GLuint GLES2::crGlCreateProgram()
{
	return glCreateProgram();
}

void GLES2::crGlDeleteProgram(GLuint p_program)
{
	glDeleteProgram(p_program);
}

GLuint GLES2::crGlCreateShader(const char* p_source, GLenum p_shaderType)
{
	GLuint shaderHandle = glCreateShader(p_shaderType); 
	glShaderSource(shaderHandle, 1, &p_source, 0); 
	glCompileShader(shaderHandle);
	//
	GLint compileSuccess; 
	glGetShaderiv(shaderHandle, GL_COMPILE_STATUS, &compileSuccess); 
	if (compileSuccess == GL_FALSE) { 
		char messages[256];
		glGetShaderInfoLog(shaderHandle, sizeof(messages), 0, &messages[0]); 
		return 0;
	} else {
		return shaderHandle; 
	}
}

void GLES2::crGlDeleteShader(GLuint p_shaderHandle)
{
	glDeleteShader(p_shaderHandle);
}

GLuint GLES2::crGlValidateProgram(GLuint p_programHandle)
{
	GLint logLength;
    //
    glValidateProgram(p_programHandle);
    glGetProgramiv(p_programHandle, GL_INFO_LOG_LENGTH, &logLength);
    if (logLength > 0)
    {
        char *log = (char *)malloc(logLength);
        glGetProgramInfoLog(p_programHandle, logLength, &logLength, log);
        //printf("Program validate log:\n%s", log);
        //free(log);
    }
    //
	GLint status;
    glGetProgramiv(p_programHandle, GL_VALIDATE_STATUS, &status);
    if (status == 0){
        return GL_FALSE;
    } else {
		return GL_TRUE;
	}
}

GLuint GLES2::crGlLinkProgram(GLuint p_programHandle)
{
	glLinkProgram(p_programHandle);
	//
	GLint status;
	glGetProgramiv(p_programHandle, GL_LINK_STATUS, &status);
	if (status == 0){
		return GL_FALSE;
	} else {
		return p_programHandle;
	}
}

void GLES2::crGlAttachShader(GLuint p_programHandle, GLuint p_shader)
{
	glAttachShader(p_programHandle, p_shader); 
}

void GLES2::crGlDetachShader(GLuint p_program, GLuint p_shader)
{
	glDetachShader(p_program, p_shader);
}

void GLES2::crGlUseProgram(GLuint p_programHandle)
{
	glUseProgram(p_programHandle);
}

void GLES2::crGlGetActiveUniform(GLuint p_programHandle)
{
	int index;
	int size;
	char *uniformName;
	GLint activeUniforms;		// Number of active uniforms variables in the shader
	GLint maxLenNameUniform;	// Max lenght of name uniform variable
	
	// Query on shaders
	glGetProgramiv(p_programHandle, GL_ACTIVE_UNIFORMS, &activeUniforms );
	glGetProgramiv(p_programHandle, GL_ACTIVE_UNIFORM_MAX_LENGTH, &maxLenNameUniform);
	
	// Allocate dynamic memory space for uniform variable name
	uniformName = (char*)malloc(sizeof(char) * maxLenNameUniform);
	
	// Loop into active uniforms variables
	
	for(index = 0; index < activeUniforms; index++)
	{
		GLenum type;
		//int location;	
		// Get the Uniform Info
		//glGetActiveUniform(p_programHandle, index, maxLenNameUniform, NULL, &size, &type, uniformName);
        glGetActiveUniform(p_programHandle, index, maxLenNameUniform, 0, &size, &type, uniformName);
        
		// Get the uniform location
		//location = glGetUniformLocation(p_programHandle, uniformName);
	}
}

void GLES2::crGlUniformMatrix4fv(GLuint p_programHandle, const char* p_name, float *p_matrix)
{
	unsigned int location = glGetUniformLocation(p_programHandle, p_name);
	glUniformMatrix4fv(location, 1, GL_FALSE, p_matrix);
}

void GLES2::crGlBindAttribLocation( GLuint p_program, GLuint p_index, const char *p_name)
{
	glBindAttribLocation(p_program, p_index, p_name);
}

