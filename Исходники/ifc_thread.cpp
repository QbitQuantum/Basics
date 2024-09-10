CThread::~CThread()
{
	// If the thread is still running.
	if (m_nThreadId != 0 && !m_bFinished)
	{
		Terminate();
		WaitFor();
	}

	if (m_nThreadId != 0)
		CloseHandle(m_hHandle);
}