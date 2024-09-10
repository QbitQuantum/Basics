bool WaitObjectContainer::Wait(unsigned long milliseconds)
{
	if (m_noWait || m_handles.empty())
		return true;

	if (m_handles.size() > MAXIMUM_WAIT_OBJECTS)
	{
		// too many wait objects for a single WaitForMultipleObjects call, so use multiple threads
		static const unsigned int WAIT_OBJECTS_PER_THREAD = MAXIMUM_WAIT_OBJECTS-1;
		unsigned int nThreads = (m_handles.size() + WAIT_OBJECTS_PER_THREAD - 1) / WAIT_OBJECTS_PER_THREAD;
		if (nThreads > MAXIMUM_WAIT_OBJECTS)	// still too many wait objects, maybe implement recursive threading later?
			throw Err("WaitObjectContainer: number of wait objects exceeds limit");
		CreateThreads(nThreads);
		DWORD error = S_OK;
		
		for (unsigned int i=0; i<m_threads.size(); i++)
		{
			WaitingThreadData &thread = *m_threads[i];
			while (!thread.waitingToWait)	// spin until thread is in the initial "waiting to wait" state
				Sleep(0);
			if (i<nThreads)
			{
				thread.waitHandles = &m_handles[i*WAIT_OBJECTS_PER_THREAD];
				thread.count = STDMIN(WAIT_OBJECTS_PER_THREAD, m_handles.size() - i*WAIT_OBJECTS_PER_THREAD);
				thread.error = &error;
			}
			else
				thread.count = 0;
		}

		ResetEvent(m_stopWaiting);
		PulseEvent(m_startWaiting);

		DWORD result = ::WaitForSingleObject(m_stopWaiting, milliseconds);
		if (result == WAIT_OBJECT_0)
		{
			if (error == S_OK)
				return true;
			else
				throw Err("WaitObjectContainer: WaitForMultipleObjects failed with error " + IntToString(error));
		}
		SetEvent(m_stopWaiting);
		if (result == WAIT_TIMEOUT)
			return false;
		else
			throw Err("WaitObjectContainer: WaitForSingleObject failed with error " + IntToString(::GetLastError()));
	}
	else
	{
		DWORD result = ::WaitForMultipleObjects(m_handles.size(), &m_handles[0], FALSE, milliseconds);
		if (result >= WAIT_OBJECT_0 && result < WAIT_OBJECT_0 + m_handles.size())
			return true;
		else if (result == WAIT_TIMEOUT)
			return false;
		else
			throw Err("WaitObjectContainer: WaitForMultipleObjects failed with error " + IntToString(::GetLastError()));
	}
}