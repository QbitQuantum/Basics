void RazerMonitorThread::Execute(void * data) {
	bool rereg = true;
	while(!isTerminated()) {
		if(rereg) {
			LONG lError = RegNotifyChangeKeyValue(hMonitoredKey, true, REG_NOTIFY_CHANGE_LAST_SET, hKeyEvent, true);
			if(lError != ERROR_SUCCESS) {
				ErrorMsg("RegNotifyChangeKeyValue");
				setTerminated(true);
			}
			rereg = false;
		}

		DWORD ret = WaitForSingleObject(hKeyEvent, 1000);
		if(ret != WAIT_FAILED && ret != WAIT_TIMEOUT) {
			for(int i = 0; i < NUM_MONITORED_KEYS; i++)
				keyChangeCallbacks[i]();
			rereg = true;
		}
		else if(ret == WAIT_TIMEOUT) {
			addAPM();
		}
	}

	if(hKeyEvent != NULL)
		CloseHandle(hKeyEvent);
	if(hMonitoredKey != NULL)
		RegCloseKey(hMonitoredKey);
}