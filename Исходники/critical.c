BOOL InitializeCriticalSectionEx(LPCRITICAL_SECTION lpCriticalSection, DWORD dwSpinCount, DWORD Flags)
{
	/**
	 * See http://msdn.microsoft.com/en-us/library/ff541979(v=vs.85).aspx
	 * - The LockCount field indicates the number of times that any thread has
	 *   called the EnterCriticalSection routine for this critical section,
	 *   minus one. This field starts at -1 for an unlocked critical section.
	 *   Each call of EnterCriticalSection increments this value; each call of
	 *   LeaveCriticalSection decrements it.
	 * - The RecursionCount field indicates the number of times that the owning
	 *   thread has called EnterCriticalSection for this critical section.
	 */
	if (Flags != 0)
	{
		WLog_WARN(TAG, "Flags unimplemented");
	}

	lpCriticalSection->DebugInfo = NULL;
	lpCriticalSection->LockCount = -1;
	lpCriticalSection->SpinCount = 0;
	lpCriticalSection->RecursionCount = 0;
	lpCriticalSection->OwningThread = NULL;
	lpCriticalSection->LockSemaphore = (winpr_sem_t*) malloc(sizeof(winpr_sem_t));
#if defined(__APPLE__)
	semaphore_create(mach_task_self(), lpCriticalSection->LockSemaphore, SYNC_POLICY_FIFO, 0);
#else
	sem_init(lpCriticalSection->LockSemaphore, 0, 0);
#endif
	SetCriticalSectionSpinCount(lpCriticalSection, dwSpinCount);
	return TRUE;
}