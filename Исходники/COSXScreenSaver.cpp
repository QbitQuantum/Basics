COSXScreenSaver::COSXScreenSaver(void* eventTarget) :
	m_eventTarget(eventTarget),
	m_enabled(true)
{
	m_autoReleasePool       = screenSaverUtilCreatePool();
	m_screenSaverController = screenSaverUtilCreateController();

	// install launch/termination event handlers
	EventTypeSpec launchEventTypes[2];
	launchEventTypes[0].eventClass = kEventClassApplication;
	launchEventTypes[0].eventKind  = kEventAppLaunched;
	launchEventTypes[1].eventClass = kEventClassApplication;
	launchEventTypes[1].eventKind  = kEventAppTerminated;
	
	EventHandlerUPP launchTerminationEventHandler =
		NewEventHandlerUPP(launchTerminationCallback);
	InstallApplicationEventHandler(launchTerminationEventHandler, 2,
								launchEventTypes, this,
								&m_launchTerminationEventHandlerRef);
	DisposeEventHandlerUPP(launchTerminationEventHandler);
	
	m_screenSaverPSN.highLongOfPSN = 0;
	m_screenSaverPSN.lowLongOfPSN  = 0;

	// test if screensaver is running and find process number
	if (isActive()) {
		ProcessInfoRec	procInfo;
		Str31			procName;	// pascal string. first byte holds length.
		memset(&procInfo, 0, sizeof(procInfo));
		procInfo.processName       = procName;
		procInfo.processInfoLength = sizeof(ProcessInfoRec);

		ProcessSerialNumber	psn;
		OSErr err = GetNextProcess(&psn);
		while (err == 0) {
			memset(procName, 0, sizeof(procName));
			err = GetProcessInformation(&psn, &procInfo);
			if (err != 0) {
				break;
			}
			if (strcmp("ScreenSaverEngine", (const char*)&procName[1]) == 0) {
				m_screenSaverPSN = psn;
				break;
			}
			err = GetNextProcess(&psn);
		}
	}
}