void jsInit()
{
#ifdef DEBUG_OUTPUT
	g_pDebugLog = fopen("JS_DEBUG.log", "w");
#endif 

	//find number of cores
	SYSTEM_INFO sysInfo = { 0 };
	GetSystemInfo(&sysInfo);
	g_numProcessors = sysInfo.dwNumberOfProcessors;


	//spawn fibers
	for (int i = 0; i < NUM_FIBERS; ++i)
	{
		g_fibers[i].fiber = CreateFiber(FIBER_STACK_SIZE, fiberRoutine, g_fibers + i);
		g_fibers[i].pNextInWaitList = NULL;
		g_fibers[i].status = UNUSED;
		g_pFiberPool[NUM_FIBERS - 1 - i] = g_fibers + i;
	}


	//init waiting fibers
	memset(g_waitingFibers, 0, sizeof(g_waitingFibers));
	g_waitingFiberHead = 0;
	g_waitListTail.pFiber = NULL;
	g_waitListTail.pNextWaitingFiber = NULL;
	g_waitListTail.time = 0;

	//get performance frequency
	QueryPerformanceFrequency((LARGE_INTEGER*)&g_performanceFrequency);

	//init jobs
	for (int i = 2; i < MAX_JOBS; ++i)
	{
		g_jobs[i - 1].pNextJob = g_jobs + i;
	}
	g_pFreeJob = g_jobs + 1;
	g_pJobQueueHead = g_jobs;
	g_dummyJob.threadId = 0x0;
	g_dummyJob.pNextJob = g_pJobQueueHead;
	g_dummyJob.pName = "__dummy";

	//spawn threads
	g_threadData = TlsAlloc();

	for (int i = 0; i < g_numProcessors; ++i)
	{
		//create thread
		if (i == 0)
		{
			g_threads[0].handle = GetCurrentThread();
		}
		else
		{
			g_threads[i].handle = CreateThread(NULL, 0, threadStart, g_threads + i, 0, NULL);
		}

		g_threads[i].id = 0x1 << i;
		g_threads[i].ppJobQueueTail = &(g_dummyJob.pNextJob);



		//lock thread to specific cpu
		SetThreadAffinityMask(g_threads[i].handle, 1 << i);
	}
	TlsSetValue(g_threadData, g_threads + 0);

	initCounterAllocator();

#ifdef DEBUG_OUTPUT
	fprintf(g_pDebugLog, "%lld \t jobsystem started\n", time(NULL));
#endif

}