int pthread_cond_timedwait (pthread_cond_t* cv, pthread_mutex_t* external_mutex, timespec* abstime)
{
	int last_waiter;

	DWORD timeout = 0;

	//struct timeval now;
	//timespec timenow;
	//gettimeofday(&now, NULL);
	//timenow.tv_sec = now.tv_sec; 
	//timenow.tv_nsec = now.tv_usec * 1000;
    //timeout = (DWORD)((abstime->tv_sec - timenow.tv_sec) * 1000 + (abstime->tv_nsec - timenow.tv_nsec) / 1000000 + 5);

	timeout = (DWORD)((abstime->tv_sec) * 1000 + (abstime->tv_nsec) / 1000000 + 5);  

	EnterCriticalSection (&cv->waiters_count_lock_);
	cv->waiters_count_++;
	LeaveCriticalSection (&cv->waiters_count_lock_);

	SignalObjectAndWait (*external_mutex, cv->sema_, timeout, FALSE);
	EnterCriticalSection (&cv->waiters_count_lock_);
	cv->waiters_count_--;
	last_waiter = (cv->was_broadcast_ && cv->waiters_count_ == 0);
	LeaveCriticalSection (&cv->waiters_count_lock_);

	if (last_waiter)
		SignalObjectAndWait (cv->waiters_done_, *external_mutex, INFINITE, FALSE);
	else
		WaitForSingleObject (*external_mutex, INFINITE);
}