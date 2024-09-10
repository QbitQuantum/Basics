void CSimpleMutex::Init(void)
{
#if defined(WINDOWS_PHONE_8) || defined(WINDOWS_STORE_RT)
	InitializeCriticalSectionEx(&criticalSection,0,CRITICAL_SECTION_NO_DEBUG_INFO);
#elif defined(_WIN32)
	//	hMutex = CreateMutex(NULL, FALSE, 0);
	//	RakAssert(hMutex);
	InitializeCriticalSection(&criticalSection);

#else
	int error = pthread_mutex_init(&hMutex, 0);
	(void) error;
	RakAssert(error==0);
#endif

}