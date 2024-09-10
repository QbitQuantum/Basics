asCThreadManager::~asCThreadManager()
{
#ifndef AS_NO_THREADS
	// Deallocate the thread local storage
	#if defined AS_POSIX_THREADS
		pthread_key_delete((pthread_key_t)tlsKey);
	#elif defined AS_WINDOWS_THREADS
		#if defined(_MSC_VER) && (WINAPI_FAMILY & WINAPI_FAMILY_PHONE_APP)
			tld = 0;
		#else
			TlsFree((DWORD)tlsKey);
		#endif
	#endif
#else
	if( tld )
	{
		asDELETE(tld,asCThreadLocalData);
	}
	tld = 0;
#endif
}