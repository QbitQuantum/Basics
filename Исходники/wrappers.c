int select123(int nfds, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, 
					 const struct timeval *timeout)
{
	if(readfds == NULL && writefds == NULL && exceptfds == NULL)
	{
		// is this highest-res?
		LARGE_INTEGER liDueTime;
		liDueTime.QuadPart = -(LONGLONG)(timeout->tv_sec*1e7 + timeout->tv_usec*10);

		// Set a timer to wait
		if (!SetWaitableTimer(hTimer, &liDueTime, 0, NULL, NULL, 0))
		{
			printf("SetWaitableTimer failed (%d)\n", GetLastError());
			return -1;
		}
		// Wait for the timer.
		if (WaitForSingleObject(hTimer, INFINITE) != WAIT_OBJECT_0)
			printf("WaitForSingleObject failed (%d)\n", GetLastError());

		return 0;
	}
	else
	{
		return select(nfds, readfds, writefds, exceptfds, timeout);
	}
}