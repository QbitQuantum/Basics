static F64 calculate_cpu_frequency(U32 measure_msecs)
{
	if(measure_msecs == 0)
	{
		return 0;
	}

	// After that we declare some vars and check the frequency of the high
	// resolution timer for the measure process.
	// If there"s no high-res timer, we exit.
	unsigned __int64 starttime, endtime, timedif, freq, start, end, dif;
	if (!QueryPerformanceFrequency((LARGE_INTEGER *) &freq))
	{
		return 0;
	}

	// Now we can init the measure process. We set the process and thread priority
	// to the highest available level (Realtime priority). Also we focus the
	// first processor in the multiprocessor system.
	HANDLE hProcess = GetCurrentProcess();
	HANDLE hThread = GetCurrentThread();
	unsigned long dwCurPriorityClass = GetPriorityClass(hProcess);
	int iCurThreadPriority = GetThreadPriority(hThread);
	unsigned long dwProcessMask, dwSystemMask, dwNewMask = 1;
	GetProcessAffinityMask(hProcess, &dwProcessMask, &dwSystemMask);

	SetPriorityClass(hProcess, REALTIME_PRIORITY_CLASS);
	SetThreadPriority(hThread, THREAD_PRIORITY_TIME_CRITICAL);
	SetProcessAffinityMask(hProcess, dwNewMask);

	//// Now we call a CPUID to ensure, that all other prior called functions are
	//// completed now (serialization)
	//__asm cpuid
	int cpu_info[4] = {-1};
	__cpuid(cpu_info, 0);

	// We ask the high-res timer for the start time
	QueryPerformanceCounter((LARGE_INTEGER *) &starttime);

	// Then we get the current cpu clock and store it
	start = __rdtsc();

	// Now we wart for some msecs
	_Delay(measure_msecs);
	//	Sleep(uiMeasureMSecs);

	// We ask for the end time
	QueryPerformanceCounter((LARGE_INTEGER *) &endtime);

	// And also for the end cpu clock
	end = __rdtsc();

	// Now we can restore the default process and thread priorities
	SetProcessAffinityMask(hProcess, dwProcessMask);
	SetThreadPriority(hThread, iCurThreadPriority);
	SetPriorityClass(hProcess, dwCurPriorityClass);

	// Then we calculate the time and clock differences
	dif = end - start;
	timedif = endtime - starttime;

	// And finally the frequency is the clock difference divided by the time
	// difference. 
	F64 frequency = (F64)dif / (((F64)timedif) / freq);

	// At last we just return the frequency that is also stored in the call
	// member var uqwFrequency - converted to MHz
	return frequency  / (F64)1000000;
}