CFSMutex::CFSMutex()
{
#if defined (WINRT)
	InitializeCriticalSectionEx(&m_hMutex, 0, 0);
#elif defined (WIN32)
	InitializeCriticalSection(&m_hMutex);
#elif defined (UNIX)
	pthread_mutexattr_t attr;
	pthread_mutexattr_init(&attr);
	pthread_mutex_init(&m_hMutex, &attr);
	pthread_mutexattr_destroy(&attr);
#elif defined (MAC)
	MPCreateCriticalRegion(&m_hMutex);
#endif
}