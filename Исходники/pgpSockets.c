BOOL WINAPI
SocketsBlockingHook()
{
	PGPEventHandlerProcPtr	eventHandler = NULL;
	PGPUserValue		userValue;
	PGPError			pgpError;
	
	PGPRMWOLockStartReading(&sIdleEventHandlerLock);
	(void) PGPThreadGetSpecific(sIdleEventHandlerIndex, (void**)&eventHandler);
	(void) PGPThreadGetSpecific(sIdleEventHandlerDataIndex, &userValue);
	PGPRMWOLockStopReading(&sIdleEventHandlerLock);
	
	if (eventHandler != NULL) {
		PGPEvent theEvent;
	
		pgpClearMemory(&theEvent, sizeof(theEvent));
		theEvent.type = kPGPEvent_SocketsIdleEvent;
		pgpError = eventHandler(NULL, &theEvent, userValue);
		if (IsPGPError(pgpError)) {
			WSACancelBlockingCall();
		}
		
	}
	
	return FALSE;
}