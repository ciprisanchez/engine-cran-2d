#ifndef __CRAN_GLES2_H__
#define __CRAN_GLES2_H__

#include "crPrerequisites.h"
extern "C"{
#include "commons.h"
}

namespace Cran {
	namespace Render {
		class GLES2{
            
		public:
            
			// LOAD PROGRAM AND SHADERS FUNCTIONS - OPENGL ES 2
			static GLuint crGlCreateProgram();
			static void crGlDeleteProgram(GLuint p_program);
			//
			static GLuint crGlCreateShader( const char*, GLenum );
			static void crGlDeleteShader(GLuint p_shaderHandle);
			//
			static GLuint crGlValidateProgram( GLuint );
			static GLuint crGlLinkProgram( GLuint);
			static void crGlAttachShader( GLuint, GLuint );
			static void crGlDetachShader(GLuint p_program, GLuint p_shader);
			static void crGlUseProgram(GLuint p_programHandle);
			static void crGlGetActiveUniform( GLuint );
			static void crGlUniformMatrix4fv( GLuint , const char* , float* );
			static void crGlBindAttribLocation( GLuint program, GLuint index, const char *name);
		};
	}
}

#endif
