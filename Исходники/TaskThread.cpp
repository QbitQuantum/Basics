//+ ----------------------------------------------------------------------------------------
DWORD WINAPI ThreadFunc_Processes(LPVOID lpThreadParameter)
{
	ThreadSync* pThreadSync = (ThreadSync*) lpThreadParameter;
	if (pThreadSync == NULL)
		return -1;

	HookAppReg		AppReg;
	ThreadParam*	pThreadParam = (ThreadParam*) pThreadSync->m_pThreadParam;

	HANDLE hDevice = AppReg.Register();
	if (hDevice == INVALID_HANDLE_VALUE)
		return -1;

	pThreadParam->NewInternalData(hDevice, AppReg.GetAppID());

	HANDLE hStopEvent = pThreadSync->m_hStopEvent;

	SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_TIME_CRITICAL);

	IDriverRegisterInvisibleThread(hDevice, AppReg.GetAppID());

	if (!pThreadParam->AddFilters())
		return -1;

	pThreadSync->SetStartSucceed();

	HANDLE handles[3];
	handles[0] = hStopEvent;
	handles[1] = AppReg.m_hWhistleup;
	handles[2] = AppReg.m_hWFChanged;

	DWORD dwResult = WAIT_TIMEOUT;

	HDSTATE Activity;

	bool bExit = false;
	while (!bExit)
	{
		switch (dwResult)
		{
		case WAIT_OBJECT_0:
			pThreadParam->BeforeExit();
			bExit = true;
			break;

		case WAIT_TIMEOUT:
		case WAIT_OBJECT_0 + 1:
			{
				IDriverGetState(hDevice, AppReg.GetAppID(), &Activity);
				while (Activity.QUnmarkedLen)
				{
					pThreadParam->SingleEvent();
					Activity.QUnmarkedLen--;
				}
			}
			break;
		case WAIT_OBJECT_0 + 2:
			// filters changed
			pThreadParam->FiltersChanged();
			break;
		}

		if (!bExit)
			dwResult = WaitForMultipleObjects(sizeof(handles) / sizeof(handles[0]), handles, FALSE, 1000);
	}

	IDriverUnregisterInvisibleThread(pThreadParam->m_hDevice, pThreadParam->m_AppID);

	HookAppReg::UnregisterApp(pThreadParam->m_hDevice, pThreadParam->m_AppID);
	return 0;
}