wfInfo* wf_info_init()
{
	wfInfo* wfi;

	wfi = (wfInfo*) malloc(sizeof(wfInfo));
	ZeroMemory(wfi, sizeof(wfInfo));

	if (wfi != NULL)
	{
		HKEY hKey;
		LONG status;
		DWORD dwType;
		DWORD dwSize;
		DWORD dwValue;

		wfi->mutex = CreateMutex(NULL, FALSE, NULL);

		if (wfi->mutex == NULL) 
		{
			WLog_ERR(TAG, "CreateMutex error: %d", GetLastError());
		}

		wfi->updateSemaphore = CreateSemaphore(NULL, 0, 32, NULL);

		wfi->updateThread = CreateThread(NULL, 0, wf_update_thread, wfi, CREATE_SUSPENDED, NULL);

		if (!wfi->updateThread)
		{
			WLog_ERR(TAG, "Failed to create update thread");
		}

		wfi->peers = (freerdp_peer**) malloc(sizeof(freerdp_peer*) * WF_INFO_MAXPEERS);
		memset(wfi->peers, 0, sizeof(freerdp_peer*) * WF_INFO_MAXPEERS);

		//Set FPS
		wfi->framesPerSecond = WF_INFO_DEFAULT_FPS;

		status = RegOpenKeyEx(HKEY_LOCAL_MACHINE, _T("Software\\FreeRDP\\Server"), 0, KEY_READ | KEY_WOW64_64KEY, &hKey);
		if (status == ERROR_SUCCESS)
		{
			if (RegQueryValueEx(hKey, _T("FramesPerSecond"), NULL, &dwType, (BYTE*) &dwValue, &dwSize) == ERROR_SUCCESS)
				wfi->framesPerSecond = dwValue;		
		}
		RegCloseKey(hKey);

		//Set input toggle
		wfi->input_disabled = FALSE;

		status = RegOpenKeyEx(HKEY_LOCAL_MACHINE, _T("Software\\FreeRDP\\Server"), 0, KEY_READ | KEY_WOW64_64KEY, &hKey);
		if (status == ERROR_SUCCESS)
		{
			if (RegQueryValueEx(hKey, _T("DisableInput"), NULL, &dwType, (BYTE*) &dwValue, &dwSize) == ERROR_SUCCESS)
			{
				if (dwValue != 0)
					wfi->input_disabled = TRUE;
			}
		}
		RegCloseKey(hKey);
	}

	return wfi;
}