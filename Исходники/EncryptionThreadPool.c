BOOL EncryptionThreadPoolStart ()
{
	size_t cpuCount, i;

	if (ThreadPoolRunning)
		return TRUE;

#ifdef DEVICE_DRIVER
	cpuCount = GetCpuCount();
#else
	{
		SYSTEM_INFO sysInfo;
		GetSystemInfo (&sysInfo);
		cpuCount = sysInfo.dwNumberOfProcessors;
	}
#endif

	if (cpuCount < 2)
		return TRUE;

	if (cpuCount > TC_ENC_THREAD_POOL_MAX_THREAD_COUNT)
		cpuCount = TC_ENC_THREAD_POOL_MAX_THREAD_COUNT;

	StopPending = FALSE;
	DequeuePosition = 0;
	EnqueuePosition = 0;

#ifdef DEVICE_DRIVER
	KeInitializeEvent (&WorkItemReadyEvent, SynchronizationEvent, FALSE);
	KeInitializeEvent (&WorkItemCompletedEvent, SynchronizationEvent, FALSE);
#else
	WorkItemReadyEvent = CreateEvent (NULL, FALSE, FALSE, NULL);
	if (!WorkItemReadyEvent)
		return FALSE;
	
	WorkItemCompletedEvent = CreateEvent (NULL, FALSE, FALSE, NULL);
	if (!WorkItemCompletedEvent)
	{
		CloseHandle (WorkItemReadyEvent);
		return FALSE;
	}
#endif
	
	TC_INIT_MUTEX (&DequeueMutex);
	TC_INIT_MUTEX (&EnqueueMutex);

	memset (WorkItemQueue, 0, sizeof (WorkItemQueue));

	for (i = 0; i < sizeof (WorkItemQueue) / sizeof (WorkItemQueue[0]); ++i)
	{
		WorkItemQueue[i].State = WorkItemFree;

#ifdef DEVICE_DRIVER
		KeInitializeEvent (&WorkItemQueue[i].ItemCompletedEvent, SynchronizationEvent, FALSE);
#else
		WorkItemQueue[i].ItemCompletedEvent = CreateEvent (NULL, FALSE, FALSE, NULL);
		if (!WorkItemQueue[i].ItemCompletedEvent)
		{
			EncryptionThreadPoolStop();
			return FALSE;
		}
#endif
	}

	for (ThreadCount = 0; ThreadCount < cpuCount; ++ThreadCount)
	{
#ifdef DEVICE_DRIVER
		if (!NT_SUCCESS (TCStartThread (EncryptionThreadProc, NULL, &ThreadHandles[ThreadCount])))
#else
		if (!(ThreadHandles[ThreadCount] = (HANDLE) _beginthreadex (NULL, 0, EncryptionThreadProc, NULL, 0, NULL)))
#endif
		{
			EncryptionThreadPoolStop();
			return FALSE;
		}
	}

	ThreadPoolRunning = TRUE;
	return TRUE;
}