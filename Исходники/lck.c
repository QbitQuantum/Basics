void *lck_init(void) {

#ifdef __SINGLE_THREAD
	return NULL;
#else
	TLckData *lck = malloc(sizeof(TLckData));

	if ( lck != NULL ) {

		#ifdef _WIN32
		InitializeCriticalSectionEx(&lck->critSec, 4000, CRITICAL_SECTION_NO_DEBUG_INFO);
		#else
		
		pthread_mutexattr_t    attr;
		pthread_mutexattr_init(&attr);
		pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
		pthread_mutex_init(&lck->mutex, &attr);

		#endif
	}


	return lck;
#endif
}