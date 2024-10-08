// generic error handler - if err is nonzero, prints error message and exits program.
void CheckError(OSStatus error, const char *operation) {
	if (error == noErr) return;
	
	char str[20];
	// see if it appears to be a 4-char-code
	*(UInt32 *)(str + 1) = CFSwapInt32HostToBig(error);
	if (isprint(str[1]) && isprint(str[2]) && isprint(str[3]) && isprint(str[4])) {
		str[0] = str[5] = '\'';
		str[6] = '\0';
	} else {
		// no, format it as an integer
		sprintf(str, "%d", (int)error);
	}
	fprintf(stderr, "Error: %s (%s)\n", operation, str);
    
    
    // from Audio Unit Processing Graph Services Reference
    switch(error) {
        case kAUGraphErr_NodeNotFound:
            fprintf(stderr, "Error:kAUGraphErr_NodeNotFound \n");
            break;
        case kAUGraphErr_OutputNodeErr:
            fprintf(stderr, "Error:kAUGraphErr_OutputNodeErr \n");
            break;
        case kAUGraphErr_InvalidConnection:
            fprintf(stderr, "Error:kAUGraphErr_InvalidConnection \n");
            break;
        case kAUGraphErr_CannotDoInCurrentContext:
            fprintf(stderr, "Error:kAUGraphErr_CannotDoInCurrentContext \n");
            break;
        case kAUGraphErr_InvalidAudioUnit:
            fprintf(stderr, "Error:kAUGraphErr_InvalidAudioUnit \n");
            break;
        case kMIDIInvalidClient :
            fprintf(stderr, "kMIDIInvalidClient ");
            break;
            
        case kMIDIInvalidPort :
            fprintf(stderr, "kMIDIInvalidPort ");
            break;
            
        case kMIDIWrongEndpointType :
            fprintf(stderr, "kMIDIWrongEndpointType"); 
            break;
            
        case kMIDINoConnection :
            fprintf(stderr, "kMIDINoConnection ");
            break;
            
        case kMIDIUnknownEndpoint :
            fprintf(stderr, "kMIDIUnknownEndpoint ");
            break;
            
        case kMIDIUnknownProperty :
            fprintf(stderr, "kMIDIUnknownProperty ");
            break;
            
        case kMIDIWrongPropertyType :
            fprintf(stderr, "kMIDIWrongPropertyType ");
            break;
            
        case kMIDINoCurrentSetup :
            fprintf(stderr, "kMIDINoCurrentSetup ");
            break;
            
        case kMIDIMessageSendErr :
            fprintf(stderr, "kMIDIMessageSendErr ");
            break;
            
        case kMIDIServerStartErr :
            fprintf(stderr, "kMIDIServerStartErr ");
            break;
            
        case kMIDISetupFormatErr :
            fprintf(stderr, "kMIDISetupFormatErr ");
            break;
            
        case kMIDIWrongThread :
            fprintf(stderr, "kMIDIWrongThread ");
            break;
            
        case kMIDIObjectNotFound :
            fprintf(stderr, "kMIDIObjectNotFound ");
            break;
            
        case kMIDIIDNotUnique :
            fprintf(stderr, "kMIDIIDNotUnique ");
            break;
            
        case kAudioToolboxErr_InvalidSequenceType :
            fprintf(stderr, " kAudioToolboxErr_InvalidSequenceType ");
            break;
            
        case kAudioToolboxErr_TrackIndexError :
            fprintf(stderr, " kAudioToolboxErr_TrackIndexError ");
            break;
            
        case kAudioToolboxErr_TrackNotFound :
            fprintf(stderr, " kAudioToolboxErr_TrackNotFound ");
            break;
            
        case kAudioToolboxErr_EndOfTrack :
            fprintf(stderr, " kAudioToolboxErr_EndOfTrack ");
            break;
            
        case kAudioToolboxErr_StartOfTrack :
            fprintf(stderr, " kAudioToolboxErr_StartOfTrack ");
            break;
            
        case kAudioToolboxErr_IllegalTrackDestination	:
            fprintf(stderr, " kAudioToolboxErr_IllegalTrackDestination");
            break;
            
        case kAudioToolboxErr_NoSequence 		:
            fprintf(stderr, " kAudioToolboxErr_NoSequence ");
            break;
            
        case kAudioToolboxErr_InvalidEventType		:
            fprintf(stderr, " kAudioToolboxErr_InvalidEventType");
            break;
            
        case kAudioToolboxErr_InvalidPlayerState	:
            fprintf(stderr, " kAudioToolboxErr_InvalidPlayerState");
            break;
            
//        case kAudioToolboxErr_CannotDoInCurrentContext	:
//            fprintf(stderr, " kAudioToolboxErr_CannotDoInCurrentContext");
//            break;
            
        case kAudioUnitErr_InvalidProperty		:
            fprintf(stderr, " kAudioUnitErr_InvalidProperty");
            break;
            
        case kAudioUnitErr_InvalidParameter		:
            fprintf(stderr, " kAudioUnitErr_InvalidParameter");
            break;
            
        case kAudioUnitErr_InvalidElement		:
            fprintf(stderr, " kAudioUnitErr_InvalidElement");
            break;
            
        case kAudioUnitErr_NoConnection			:
            fprintf(stderr, " kAudioUnitErr_NoConnection");
            break;
            
        case kAudioUnitErr_FailedInitialization		:
            fprintf(stderr, " kAudioUnitErr_FailedInitialization");
            break;
            
        case kAudioUnitErr_TooManyFramesToProcess	:
            fprintf(stderr, " kAudioUnitErr_TooManyFramesToProcess");
            break;
            
        case kAudioUnitErr_InvalidFile			:
            fprintf(stderr, " kAudioUnitErr_InvalidFile");
            break;
            
        case kAudioUnitErr_FormatNotSupported		:
            fprintf(stderr, " kAudioUnitErr_FormatNotSupported");
            break;
            
        case kAudioUnitErr_Uninitialized		:
            fprintf(stderr, " kAudioUnitErr_Uninitialized");
            break;
            
        case kAudioUnitErr_InvalidScope			:
            fprintf(stderr, " kAudioUnitErr_InvalidScope");
            break;
            
        case kAudioUnitErr_PropertyNotWritable		:
            fprintf(stderr, " kAudioUnitErr_PropertyNotWritable");
            break;
            
        case kAudioUnitErr_InvalidPropertyValue		:
            fprintf(stderr, " kAudioUnitErr_InvalidPropertyValue");
            break;
            
        case kAudioUnitErr_PropertyNotInUse		:
            fprintf(stderr, " kAudioUnitErr_PropertyNotInUse");
            break;
            
        case kAudioUnitErr_Initialized			:
            fprintf(stderr, " kAudioUnitErr_Initialized");
            break;
            
        case kAudioUnitErr_InvalidOfflineRender		:
            fprintf(stderr, " kAudioUnitErr_InvalidOfflineRender");
            break;
            
        case kAudioUnitErr_Unauthorized			:
            fprintf(stderr, " kAudioUnitErr_Unauthorized");
            break;
	}
	exit(1);
}