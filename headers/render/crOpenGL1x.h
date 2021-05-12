#ifdef WINDOWS_ENVIRONMENT
#ifndef __CRAN_AGL1X_H__
#define __CRAN_AGL1X_H__

#include "crPrerequisites.h"
extern "C"{
	#include "commons.h"
}

typedef enum { CR_PRIMITIVE_TRIANGLE, CR_PRIMITIVE_QUAD} CR_PRIMITIVE;

namespace Cran {
	namespace Render {
		class GL1x{
			
			// **** VIEW
			void crGl1LoadIdentity();
			void crGl1IdentityProjection();
			void crGl1IdentityModelview();
			void crGl1Perspective(double p_fieldOfView, double p_aspect, double p_zNear, double p_zFar);

			// **** CAPABILITIES
			void crGl1Enable2DTextures();
			void crGl1Disable2DTextures();

			// **** RENDER
			void crGl1Render2f( CR_PRIMITIVE p_primitive, float *p_data, float *p_color, float *p_texture_data);

		};
	}
}

#endif
#endif