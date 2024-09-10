void ParseArgs (int argc, char * const argv[],
                AudioFileTypeID	&	outFormat,
                Float64	&			outSampleRate,
                OSType	&			outFileType,
                CFURLRef&			outInputFileURL,
                CFURLRef&			outOutputFileURL,
                UInt32  &			outBitDepth,
                UInt32  &			outBitRate)
{
	if (argc < 2) {
		printf ("No Input File specified\n");
		UsageString(1);
	}
	
	// support "ConvertFile -h" usage
	if (argc == 2 && !strcmp("-h", argv[1])) {
		UsageString(0);
	}
	
	// first validate our initial condition
	const char* inputFileName = argv[1];
	
	outInputFileURL = CFURLCreateFromFileSystemRepresentation (kCFAllocatorDefault, (const UInt8 *)inputFileName, strlen(inputFileName), false);
	if (!outInputFileURL) {
		printf ("* * Bad input file path\n");
		UsageString(1);
    }
	
	outBitRate = 0;
	outBitDepth = 0;
	
	// look to see if a format or different file output has been specified
	for (int i = 2; i < argc; ++i) {
		if (!strcmp ("-d", argv[i])) {
			str2OSType (argv[++i], outFormat);
			outSampleRate = 0;
		}
		else if (!strcmp ("-r", argv[i])) {
			sscanf (argv[++i], "%lf", &outSampleRate);
			outFormat = 0;
		}
		else if (!strcmp("-bd", argv[i])) {
			int temp;
			sscanf (argv[++i], "%d", &temp);
			outBitDepth = temp;
		}
		else if (!strcmp ("-f", argv[i])) {
			str2OSType (argv[++i], outFileType);
		}
		else if (!strcmp ("-b", argv[i])) {
			int temp;
			sscanf (argv[++i], "%u", &temp);
			outBitRate = temp;
		}
		else if (!strcmp ("-h", argv[i])) {
			UsageString(0);
		}
		else {
			printf ("* * Unknown command: %s\n", argv[i]);
			UsageString(1);
		}
	}
	
    // output file
	UInt32 size = sizeof(CFArrayRef);
	CFArrayRef extensions;
	OSStatus err = AudioFileGetGlobalInfo(kAudioFileGlobalInfo_ExtensionsForType,
                                          sizeof(OSType), &outFileType,
                                          &size, &extensions);
	XThrowIfError (err, "Getting the file extensions for file type");
    
	// just take the first extension
	CFStringRef ext = (CFStringRef)CFArrayGetValueAtIndex(extensions, 0);
	char extstr[32];
	Boolean res = CFStringGetCString(ext, extstr, 32, kCFStringEncodingUTF8);
	XThrowIfError (!res, "CFStringGetCString");
	
	// release the array as we're done with this now
	CFRelease (extensions);
    
	char outFname[256];
#if TARGET_OS_WIN32
	char drive[3], dir[256];
	_splitpath_s(inputFileName, drive, 3, dir, 256, NULL, 0, NULL, 0);
	_makepath_s(outFname, 256, drive, dir, "outfile", extstr);
#else
    //	char outFname[64];
	sprintf (outFname, "/tmp/outfile.%s", extstr);
#endif
	outOutputFileURL = CFURLCreateFromFileSystemRepresentation (kCFAllocatorDefault, (const UInt8 *)outFname, strlen(outFname), false);
	if (!outOutputFileURL) {
		printf ("* * Bad output file path\n");
		UsageString(1);
    }
}