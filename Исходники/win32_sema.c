/*
 * PGSemaphoreLock
 *
 * Lock a semaphore (decrement count), blocking if count would be < 0.
 * Serve the interrupt if interruptOK is true.
 */
void
PGSemaphoreLock(PGSemaphore sema, bool interruptOK)
{
	DWORD		ret;
	HANDLE		wh[2];

	/*
	 * Note: pgwin32_signal_event should be first to ensure that it will be
	 * reported when multiple events are set.  We want to guarantee that
	 * pending signals are serviced.
	 */
	wh[0] = pgwin32_signal_event;
	wh[1] = *sema;

	/*
	 * As in other implementations of PGSemaphoreLock, we need to check for
	 * cancel/die interrupts each time through the loop.  But here, there is
	 * no hidden magic about whether the syscall will internally service a
	 * signal --- we do that ourselves.
	 */
	do
	{
		ImmediateInterruptOK = interruptOK;
		CHECK_FOR_INTERRUPTS();

		ret = WaitForMultipleObjectsEx(2, wh, FALSE, INFINITE, TRUE);

		if (ret == WAIT_OBJECT_0)
		{
			/* Signal event is set - we have a signal to deliver */
			pgwin32_dispatch_queued_signals();
			errno = EINTR;
		}
		else if (ret == WAIT_OBJECT_0 + 1)
		{
			/* We got it! */
			errno = 0;
		}
		else
			/* Otherwise we are in trouble */
			errno = EIDRM;

		ImmediateInterruptOK = false;
	} while (errno == EINTR);

	if (errno != 0)
		ereport(FATAL,
				(errmsg("could not lock semaphore: error code %lu", GetLastError())));
}