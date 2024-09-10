DWORD
HXWSAEventWaiter::HelperThread::Live()
{
    while(1)
    {
	/*
	 * Wait until it is time to start waiting.
	 */
	WaitForSingleObjectEx(m_hGoAheadAndWait, INFINITE,
	    FALSE);

	/*
	 * Are we supposed to be exiting?
	 */
	if(m_bPleaseDieNow)
	{
	    return 0;
	}
	/*
	 * Wait on what we are supposed to wait on.
	 */
	m_dwRetVal =
	    WSAWaitForMultipleEvents(m_dwNumEvents,
	    m_pEvents, FALSE, m_dwTimeout, FALSE);

	/*
	 * Reset our state for waiting again.
	 */
	ResetEvent(m_hGoAheadAndWait);
	/*
	 * Raise our hand and say we are done.
	 */
	SetEvent(m_hIAmDone);

    }
    return 0;
}