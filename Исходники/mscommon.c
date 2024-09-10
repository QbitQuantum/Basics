void ms_usleep(uint64_t usec){
#ifdef WIN32
#if WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
	Sleep((DWORD)(usec/1000));
#else
	HANDLE sleepEvent = CreateEventEx(NULL, NULL, CREATE_EVENT_MANUAL_RESET, EVENT_ALL_ACCESS);
	if (!sleepEvent) return;
	WaitForSingleObjectEx(sleepEvent, usec / 1000, FALSE);
#endif
#else
	struct timespec ts,rem;
	int err;
	ts.tv_sec=usec/1000000LL;
	ts.tv_nsec=(usec%1000000LL)*1000;
	do {
		err=nanosleep(&ts,&rem);
		ts=rem;
	}while(err==-1 && errno==EINTR);
#endif
}