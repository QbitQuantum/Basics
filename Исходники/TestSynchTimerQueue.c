int TestSynchTimerQueue(int argc, char* argv[])
{
	int index;
	HANDLE hTimerQueue;
	HANDLE hTimers[TIMER_COUNT];
	APC_DATA apcData[TIMER_COUNT];

	g_Event = CreateEvent(NULL, TRUE, FALSE, NULL);

	hTimerQueue = CreateTimerQueue();

	if (!hTimerQueue)
	{
		printf("CreateTimerQueue failed (%d)\n", (int) GetLastError());
		return -1;
	}

	for (index = 0; index < TIMER_COUNT; index++)
	{
		apcData[index].TimerId = index;
		apcData[index].StartTime = GetTickCount();
		apcData[index].DueTime = (index * 100) + 500;
		apcData[index].Period = 1000;
		apcData[index].FireCount = 0;

		if (!CreateTimerQueueTimer(&hTimers[index], hTimerQueue, (WAITORTIMERCALLBACK) TimerRoutine,
				&apcData[index], apcData[index].DueTime, apcData[index].Period, 0))
		{
			printf("CreateTimerQueueTimer failed (%d)\n", (int) GetLastError());
			return -1;
		}
	}

	if (WaitForSingleObject(g_Event, INFINITE) != WAIT_OBJECT_0)
	{
		printf("WaitForSingleObject failed (%d)\n", (int) GetLastError());
		return -1;
	}

	for (index = 0; index < TIMER_COUNT; index++)
	{
		if (!DeleteTimerQueueTimer(hTimerQueue, hTimers[index], NULL))
		{
			printf("DeleteTimerQueueTimer failed (%d)\n", (int) GetLastError());
			return -1;
		}
	}
	
	if (!DeleteTimerQueue(hTimerQueue))
	{
		printf("DeleteTimerQueue failed (%d)\n", (int) GetLastError());
		return -1;
	}

	CloseHandle(g_Event);

	return 0;
}