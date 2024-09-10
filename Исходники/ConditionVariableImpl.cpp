	bool ConditionVariableImpl::Wait(MutexImpl* mutex, UInt32 timeout)
	{
		#if NAZARA_CORE_WINDOWS_VISTA
		return SleepConditionVariableCS(&m_cv, &mutex->m_criticalSection, timeout);
		#else
		m_count++;

		// It's ok to release the mutex here since Win32
		// manual-reset events maintain state when used with SetEvent.
		// This avoids the "lost wakeup" bug...
		LeaveCriticalSection(&mutex->m_criticalSection);

		// Wait for either event to become signaled due to Signal being called or SignalAll being called.
		int result = WaitForMultipleObjects(2, m_events, false, timeout);

		// Some thread called SignalAll
		if (--m_count == 0 && result == WAIT_OBJECT_0 + BROADCAST)
			// We're the last waiter to be notified or to stop waiting, so reset the manual event.
			ResetEvent(m_events[BROADCAST]);

		// Reacquire the mutex.
		EnterCriticalSection(&mutex->m_criticalSection);

		return result != WAIT_TIMEOUT;
		#endif
	}