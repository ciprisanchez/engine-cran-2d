#ifdef IPHONE_ENVIRONMENT

#include "cr_Ios_OpenALSupport.h"

ALvoid  alBufferDataStaticProc(const ALint bid, ALenum format, ALvoid* data, ALsizei size, ALsizei freq)
{
	static	alBufferDataStaticProcPtr	proc = NULL;
    
    if (proc == NULL) {
        proc = (alBufferDataStaticProcPtr) alcGetProcAddress(NULL, (const ALCchar*) "alBufferDataStatic");
    }
    
    if (proc)
        proc(bid, format, data, size, freq);
	
    return;
}

void* MyGetOpenALAudioData(CFURLRef inFileURL, ALsizei *outDataSize, ALenum *outDataFormat, ALsizei* outSampleRate)
{
	OSStatus error = noErr;	
	SInt64							theFileLengthInFrames = 0;
	AudioStreamBasicDescription		theFileFormat;
	UInt32							thePropertySize = sizeof(theFileFormat);
	ExtAudioFileRef					extRef = NULL;
	void*							theData = NULL;
	AudioStreamBasicDescription		outputFormat;
	AudioBufferList dataBuffer;

	// Open a file with ExtAudioFileOpen()
	error = ExtAudioFileOpenURL(inFileURL, &extRef);
	if(error) {
		printf("MyGetOpenALAudioData: ExtAudioFileOpenURL FAILED, Error = %ld\n", error);
		return nil;
	}
	
	// Get the audio data format
	error = ExtAudioFileGetProperty(extRef, kExtAudioFileProperty_FileDataFormat, &thePropertySize, &theFileFormat);
	if(error){
		printf("MyGetOpenALAudioData: ExtAudioFileGetProperty(kExtAudioFileProperty_FileDataFormat) FAILED, Error = %ld\n", error);
				return nil;
	}
	if (theFileFormat.mChannelsPerFrame > 2){
		printf("MyGetOpenALAudioData - Unsupported Format, channel count is greater than stereo\n"); 
				return nil;
	}

	// Set the client format to 16 bit signed integer (native-endian) data
	// Maintain the channel count and sample rate of the original source format
	outputFormat.mSampleRate = theFileFormat.mSampleRate;
	outputFormat.mChannelsPerFrame = theFileFormat.mChannelsPerFrame;

	outputFormat.mFormatID = kAudioFormatLinearPCM;
	outputFormat.mBytesPerPacket = 2 * outputFormat.mChannelsPerFrame;
	outputFormat.mFramesPerPacket = 1;
	outputFormat.mBytesPerFrame = 2 * outputFormat.mChannelsPerFrame;
	outputFormat.mBitsPerChannel = 16;
	outputFormat.mFormatFlags = kAudioFormatFlagsNativeEndian | kAudioFormatFlagIsPacked | kAudioFormatFlagIsSignedInteger;
	
	// Set the desired client (output) data format
	error = ExtAudioFileSetProperty(extRef, kExtAudioFileProperty_ClientDataFormat, sizeof(outputFormat), &outputFormat);
	if(error) {
		printf("MyGetOpenALAudioData: ExtAudioFileSetProperty(kExtAudioFileProperty_ClientDataFormat) FAILED, Error = %ld\n", error);
				return nil;
	}
	
	// Get the total frame count
	thePropertySize = sizeof(theFileLengthInFrames);
	error = ExtAudioFileGetProperty(extRef, kExtAudioFileProperty_FileLengthFrames, &thePropertySize, &theFileLengthInFrames);
	if(error){
		printf("MyGetOpenALAudioData: ExtAudioFileGetProperty(kExtAudioFileProperty_FileLengthFrames) FAILED, Error = %ld\n", error);
				return nil;
	}
	
	// Read all the data into memory
	UInt32		dataSize = theFileLengthInFrames * outputFormat.mBytesPerFrame;;
	theData = malloc(dataSize);
	if (theData)
	{
		
		dataBuffer.mNumberBuffers = 1;
		dataBuffer.mBuffers[0].mDataByteSize = dataSize;
		dataBuffer.mBuffers[0].mNumberChannels = outputFormat.mChannelsPerFrame;
		dataBuffer.mBuffers[0].mData = theData;
		
		// Read the data into an AudioBufferList
		error = ExtAudioFileRead(extRef, (UInt32*)&theFileLengthInFrames, &dataBuffer);
		if(error == noErr)
		{
			*outDataSize = (ALsizei)dataSize;
			*outDataFormat = (outputFormat.mChannelsPerFrame > 1) ? AL_FORMAT_STEREO16 : AL_FORMAT_MONO16;
			*outSampleRate = (ALsizei)outputFormat.mSampleRate;
		}
		else 
		{ 
			// failure
			free (theData);
			theData = NULL; // make sure to return NULL
			printf("MyGetOpenALAudioData: ExtAudioFileRead FAILED, Error = %ld\n", error);
            		return nil;
		}	
	}
	

	// Dispose the ExtAudioFileRef, it is no longer needed
	if (extRef) ExtAudioFileDispose(extRef);
	return theData;
}

#endif