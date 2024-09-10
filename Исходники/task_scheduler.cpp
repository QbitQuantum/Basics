void TaskScheduler::Initialize(GlobalArgs *globalArgs) {
	for (uint i = 0; i < FIBER_POOL_SIZE; ++i) {
		m_fiberPool.enqueue(CreateFiberEx(524288, 0, FIBER_FLAG_FLOAT_SWITCH, FiberStart, globalArgs));
	}

	SYSTEM_INFO sysinfo;
	GetSystemInfo(&sysinfo);

	// Create an additional thread for each logical processor
	m_numThreads = sysinfo.dwNumberOfProcessors;
	m_threads = new HANDLE[m_numThreads];
	m_fiberSwitchingFibers = new void *[m_numThreads];
	m_counterWaitingFibers = new void *[m_numThreads];


	// Create a switching fiber for each thread
	for (uint i = 0; i < m_numThreads; ++i) {
		m_fiberSwitchingFibers[i] = CreateFiberEx(32768, 0, FIBER_FLAG_FLOAT_SWITCH, FiberSwitchStart, &globalArgs->TaskScheduler);
		m_counterWaitingFibers[i] = CreateFiberEx(32768, 0, FIBER_FLAG_FLOAT_SWITCH, CounterWaitStart, &globalArgs->TaskScheduler);
	}

	// Set the affinity for the current thread and convert it to a fiber
	SetThreadAffinityMask(GetCurrentThread(), 1);
	ConvertThreadToFiberEx(nullptr, FIBER_FLAG_FLOAT_SWITCH);
	m_threads[0] = GetCurrentThread();
	tls_threadId = 0;
	
	// Create the remaining threads
	for (DWORD i = 1; i < m_numThreads; ++i) {
		ThreadStartArgs *threadArgs = new ThreadStartArgs();
		threadArgs->globalArgs = globalArgs;
		threadArgs->threadId = i;

		HANDLE threadHandle = (HANDLE)_beginthreadex(nullptr, 524288, ThreadStart, threadArgs, CREATE_SUSPENDED, nullptr);
		m_threads[i] = threadHandle;

		DWORD_PTR mask = 1 << i;
		SetThreadAffinityMask(threadHandle, mask);
		ResumeThread(threadHandle);
	}
}