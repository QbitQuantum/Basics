void SystemEventsManager::prevent(int event, bool prevent) {
	if (prevent) {
		prepareLoop();
#if VERSIONWIN
		if (event == SYSTEM_SLEEP)
			SetThreadExecutionState(ES_CONTINUOUS | ES_SYSTEM_REQUIRED);
#endif
	}
    events[event].prevent(prevent);
	if (!prevent) {
		stopLoop();
#if VERSIONWIN
		if (event == SYSTEM_SLEEP)
			SetThreadExecutionState(ES_CONTINUOUS);
#endif
	}
}