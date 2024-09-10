void deTimer_disable (deTimer* timer)
{
	if (timer->timer)
	{
		const int	maxTries	= 100;
		HANDLE		waitEvent	= CreateEvent(NULL, FALSE, FALSE, NULL);
		int			tryNdx		= 0;
		DE_ASSERT(waitEvent);

		for (tryNdx = 0; tryNdx < maxTries; tryNdx++)
		{
			BOOL success = DeleteTimerQueueTimer(NULL, timer->timer, waitEvent);
			if (success)
			{
				/* Wait for all callbacks to complete. */
				DWORD res = WaitForSingleObject(waitEvent, INFINITE);
				DE_ASSERT(res == WAIT_OBJECT_0);
				DE_UNREF(res);
				break;
			}
			else
			{
				DWORD err = GetLastError();
				if (err == ERROR_IO_PENDING)
					break; /* \todo [2013-03-21 pyry] Does this mean that callback is still in progress? */
				deYield();
			}
		}

		DE_ASSERT(tryNdx < maxTries);

		CloseHandle(waitEvent);
		timer->timer = 0;
	}
}