INT64 RDTSCTimer::calcTicksPerSecond()
{
	// raise the priority for accurate timing
	int priClass = GetPriorityClass(GetCurrentProcess());
	SetPriorityClass(GetCurrentProcess(), REALTIME_PRIORITY_CLASS);
	int priority = GetThreadPriority(GetCurrentThread());
	SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_TIME_CRITICAL);

	// wait for 0.25 seconds
	INT64 begin = RDTSCTimer::getTime();

	Sleep(1000/4);

	INT64 end = RDTSCTimer::getTime();

	// restore the previous priority
	SetPriorityClass(GetCurrentProcess(), priClass);
	SetThreadPriority(GetCurrentThread(), priority);

	return (end - begin)*4;
}