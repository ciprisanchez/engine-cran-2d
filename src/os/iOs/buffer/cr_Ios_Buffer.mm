#ifdef IPHONE_ENVIRONMENT

#import <QuartzCore/QuartzCore.h>
#import <OpenGLES/EAGL.h>
#import "cr_Ios_Buffer.h"

using namespace std;

@interface Cran_Ios_Buffer (PrivateMethods)
- (void)setFramebuffer2;
- (BOOL)presentFramebuffer2;
- (void)createFramebuffer2;
- (void)deleteFramebuffer2;
@end

@implementation Cran_Ios_Buffer
@synthesize context;
@synthesize mLayer;
static Cran_Ios_Buffer *_instance = nil;


// The pixel dimensions of the CAEAGLLayer.
GLint framebufferWidth;
GLint framebufferHeight;

// The OpenGL ES names for the framebuffer and renderbuffer used to render to this view.
GLuint defaultFramebuffer, colorRenderbuffer;

GLuint getFrameBufferWidth(){   return framebufferWidth;    }
GLuint getFrameBufferHeight(){  return framebufferHeight;   }
GLuint getDefaultFramebuffer(){ return defaultFramebuffer;  }
GLuint getColorRenderbuffer(){  return colorRenderbuffer;   }

//
void setContext(void *p_newContext, void *eaglLayer)
{
    //[Cran_Ios_Buffer getInstance];
    //EAGLContext *newContext = (EAGLContext*)p_newContext;
    //CAEAGLLayer *layer = (CAEAGLLayer*)eaglLayer;
    //[_instance setContext:newContext:layer];
}

void setFramebuffer()
{
    //[_instance setFramebuffer2];
}

void setPresentFramebuffer()
{
    //[_instance presentFramebuffer2];
}
/*

- (void)setContext:(EAGLContext *)p_newContext:(CAEAGLLayer*)p_layer
{
    mLayer = p_layer;
    if (context != p_newContext) {
        [self deleteFramebuffer2];
        
        [context release];
        context = [p_newContext retain];
        
        [EAGLContext setCurrentContext:nil];
    }
}

- (void)setFramebuffer2
{
    if (context) {
        [EAGLContext setCurrentContext:context];
        
        if (!defaultFramebuffer){
            [self createFramebuffer2];
        }
    }
}

- (BOOL)presentFramebuffer2
{
    BOOL success = FALSE;
    
    if (context) {
        [EAGLContext setCurrentContext:context];
        
        success = [context presentRenderbuffer:GL_RENDERBUFFER];
    }
    
    return success;
}

/*
void setScreenBuffer()
{
    if (context) {
        [EAGLContext setCurrentContext:context];
        
        if (!defaultFramebuffer){
            [self createFramebuffer:crBridge];
		}
    }
}

void flushScreenBuffer()
{
	BOOL success = FALSE;
	//
    if (context) {
		[EAGLContext setCurrentContext:context];
        success = [context presentRenderbuffer:GL_RENDERBUFFER];
    }
}

void createFramebuffer()
{
	if (context && !defaultFramebuffer) {
        [EAGLContext setCurrentContext:context];
        
        // Create default framebuffer object.
        glGenFramebuffers(1, &defaultFramebuffer);
        glBindFramebuffer(GL_FRAMEBUFFER, defaultFramebuffer);
        
        // Create color render buffer and allocate backing store.
        glGenRenderbuffers(1, &colorRenderbuffer);
        glBindRenderbuffer(GL_RENDERBUFFER, colorRenderbuffer);
        [context renderbufferStorage:GL_RENDERBUFFER fromDrawable:(CAEAGLLayer *)self.layer];
        glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_WIDTH, &framebufferWidth);
        glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_HEIGHT, &framebufferHeight);
        
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, colorRenderbuffer);
        
        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
            NSLog(@"Failed to make complete framebuffer object %x", glCheckFramebufferStatus(GL_FRAMEBUFFER));
    }
    //
    crBridge->BRIDGE_CRAN_INIT_BUFFER(defaultFramebuffer, colorRenderbuffer, framebufferWidth, framebufferHeight);
}

void deleteFramebuffer()
{
    if (context) {
        [EAGLContext setCurrentContext:context];
        
        if (defaultFramebuffer) {
            glDeleteFramebuffers(1, &defaultFramebuffer);
            defaultFramebuffer = 0;
        }
        
        if (colorRenderbuffer) {
            glDeleteRenderbuffers(1, &colorRenderbuffer);
            colorRenderbuffer = 0;
        }
    }
}
*/
/*
+(Cran_Ios_Buffer *)getInstance{
    @synchronized([Cran_Ios_Buffer class]){
        if (!_instance) {
            [[self alloc] init];
        }
        return _instance;
    }
}

+(id)alloc
{
	@synchronized([Cran_Ios_Buffer class])
	{
		NSAssert(_instance == nil, @"Attempted to allocate a second instance of a singleton.");
		_instance = [super alloc];
		return _instance;
	}
    
	return nil;
}

-(id)init {
    self = [super init];
	if(self != nil) {

	}
	return self;
}


- (void)createFramebuffer2
{
    if (context && !defaultFramebuffer) {
        [EAGLContext setCurrentContext:context];
        
        // Create default framebuffer object.
        glGenFramebuffers(1, &defaultFramebuffer);
        glBindFramebuffer(GL_FRAMEBUFFER, defaultFramebuffer);
        
        // Create color render buffer and allocate backing store.
        glGenRenderbuffers(1, &colorRenderbuffer);
        glBindRenderbuffer(GL_RENDERBUFFER, colorRenderbuffer);
        [context renderbufferStorage:GL_RENDERBUFFER fromDrawable:mLayer];
        glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_WIDTH, &framebufferWidth);
        glGetRenderbufferParameteriv(GL_RENDERBUFFER, GL_RENDERBUFFER_HEIGHT, &framebufferHeight);
        
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, colorRenderbuffer);
        
        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
            NSLog(@"Failed to make complete framebuffer object %x", glCheckFramebufferStatus(GL_FRAMEBUFFER));
    }
}

- (void)deleteFramebuffer2
{
    if (context) {
        [EAGLContext setCurrentContext:context];
        
        if (defaultFramebuffer) {
            glDeleteFramebuffers(1, &defaultFramebuffer);
            defaultFramebuffer = 0;
        }
        
        if (colorRenderbuffer) {
            glDeleteRenderbuffers(1, &colorRenderbuffer);
            colorRenderbuffer = 0;
        }
    }
}
*/
@end

#endif  