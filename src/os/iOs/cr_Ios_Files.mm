#ifdef IPHONE_ENVIRONMENT

#import "cr_Ios_Files.h"
#import <string>

using namespace std;

@implementation Cran_Ios_Files

// Get the resources directory
const char* getSystemPath()
{
	NSString *path = [[NSBundle mainBundle] resourcePath];
    NSMutableString* pathString = [NSMutableString string];
    [pathString appendString:path];
    [pathString appendString:@"/"]; 
    
     
    //return [pathString UTF8String:1];
    return [pathString cStringUsingEncoding:1];
    //return [pathString cStringUsingEncoding:1];
    //return pathString;
    //*********************
}

// Get the document directory, is where we must write our files
const char* getDocumentPath()
{
    NSArray *docPath = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES); 
    NSString *documentsDirectoryPath = [docPath objectAtIndex:0];
    NSMutableString* pathDocString = [NSMutableString string];
    [pathDocString appendString:documentsDirectoryPath];
    [pathDocString appendString:@"/"];
    
    return [pathDocString cStringUsingEncoding:1];
}


@end

#endif