	virtual ~LocalizationDirectoryMonitorThread()
	{
		Terminate();

		DWORD aWaitResult = WaitForSingleObject(myHandle, 5000);	//wait 5 seconds

		if (aWaitResult != WAIT_OBJECT_0)
			TerminateThread(myHandle, 1);

		CloseHandle(myTerminateEvent);
	}