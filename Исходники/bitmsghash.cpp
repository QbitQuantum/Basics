void getnumthreads()
{
#ifdef _WIN32
	DWORD_PTR dwProcessAffinity, dwSystemAffinity;
#elif __linux__
	cpu_set_t dwProcessAffinity;
#else
	int dwProcessAffinity = 0;
	int32_t core_count = 0;
#endif
	size_t len = sizeof(dwProcessAffinity);
	if (numthreads > 0)
		return;
#ifdef _WIN32
	GetProcessAffinityMask(GetCurrentProcess(), &dwProcessAffinity, &dwSystemAffinity);
#elif __linux__
	sched_getaffinity(0, len, &dwProcessAffinity);
#else
	if (sysctlbyname("hw.logicalcpu", &core_count, &len, 0, 0) == 0)
		numthreads = core_count;
#endif
	for (unsigned int i = 0; i < len * 8; i++)
#if defined(_WIN32)
		if (dwProcessAffinity & (1i64 << i)) {
#elif defined __linux__
		if (CPU_ISSET(i, &dwProcessAffinity)) {
#else
		if (dwProcessAffinity & (1 << i)) {
#endif
			numthreads++;
			printf("Detected core on: %u\n", i);
		}
	printf("Number of threads: %i\n", (int)numthreads);
}

extern "C" EXPORT unsigned long long BitmessagePOW(unsigned char * starthash, unsigned long long target)
{
	successval = 0;
	max_val = target;
	getnumthreads();
	initialHash = (unsigned char *)starthash;
#   ifdef _WIN32
	HANDLE* threads = (HANDLE*)calloc(sizeof(HANDLE), numthreads);
#   else
	pthread_t* threads = (pthread_t*)calloc(sizeof(pthread_t), numthreads);
	struct sched_param schparam;
	schparam.sched_priority = 0;
#   endif
	unsigned int *threaddata = (unsigned int *)calloc(sizeof(unsigned int), numthreads);
	for (unsigned int i = 0; i < numthreads; i++) {
		threaddata[i] = i;
#   ifdef _WIN32
		threads[i] = CreateThread(NULL, 0, threadfunc, (LPVOID)&threaddata[i], 0, NULL);
		SetThreadPriority(threads[i], THREAD_PRIORITY_IDLE);
#   else
		pthread_create(&threads[i], NULL, threadfunc, (void*)&threaddata[i]);
#   ifdef __linux__
		pthread_setschedparam(threads[i], SCHED_IDLE, &schparam);
#   else
		pthread_setschedparam(threads[i], SCHED_RR, &schparam);
#   endif
#   endif
	}
#   ifdef _WIN32
	WaitForMultipleObjects(numthreads, threads, TRUE, INFINITE);
#   else
	for (unsigned int i = 0; i < numthreads; i++) {
		pthread_join(threads[i], NULL);
	}
#   endif
	free(threads);
	free(threaddata);
	return successval;
}