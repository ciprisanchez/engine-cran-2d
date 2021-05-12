#ifdef IPHONE_ENVIRONMENT

#ifndef __IOS_BUFFER_H__
#define __IOS_BUFFER_H__

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

#import "crOsIosInterface.h"

@class EAGLContext;

@interface Cran_Ios_Buffer: UIView {
@private
    // The pixel dimensions of the CAEAGLLayer.
    GLint framebufferWidth;
    GLint framebufferHeight;
    
    // The OpenGL ES names for the framebuffer and renderbuffer used to render to this view.
    GLuint defaultFramebuffer, colorRenderbuffer;
}

@property (nonatomic, retain) EAGLContext *context;
@property (nonatomic, retain) CAEAGLLayer *mLayer;

+(Cran_Ios_Buffer *)getInstance;
- (void)setContext:(EAGLContext *)p_newContext:(CAEAGLLayer*)p_layer;

@end
#endif
#endif