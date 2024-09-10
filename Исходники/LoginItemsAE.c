static OSStatus FindSystemEvents(ProcessSerialNumber *psnPtr)
	// Finds the "System Events" process or, if it's not 
	// running, launches it.
{
	OSStatus		err;
	Boolean			found = false;
	ProcessInfoRec	info;
	
	assert(psnPtr != NULL);

	psnPtr->lowLongOfPSN	= kNoProcess;
	psnPtr->highLongOfPSN	= kNoProcess;

	do {
		err = GetNextProcess(psnPtr);
		if (err == noErr) {	
			memset(&info, 0, sizeof(info));
			err = GetProcessInformation(psnPtr, &info);
		}
		if (err == noErr) {
			found = (info.processSignature == kSystemEventsCreator);
		}
	} while ( (err == noErr) && ! found );

	if (err == procNotFound) {
		err = LaunchSystemEvents(psnPtr);
	}
	return err;
}