/* Wait for the specified network event to occur, or cancellation, whichever
 * happens first. On cancellation, return -1; on error, return the error
 * code; on success, return 0. */
int NetworkStream_Win32::WaitForCompletionOrCancellation( int iEvent )
{
	while(1)
	{
		int iRet = WaitForSingleObject( m_hCompletionEvent, INFINITE );
		if( iRet != WAIT_OBJECT_0 )
			continue;

		m_Mutex.Lock();

		// This will reset the event. Do this while we hold the lock.
		WSANETWORKEVENTS events;
		WSAEnumNetworkEvents( m_Socket, m_hCompletionEvent, &events );

		// Was the event signalled due to cancellation?
		if( m_State == STATE_CANCELLED )
		{
			m_Mutex.Unlock();
			return -1;
		}

		m_Mutex.Unlock();

		// If the event didn't actually occur, keep waiting.
		if( (events.lNetworkEvents & (1<<iEvent)) )
			return events.iErrorCode[iEvent];

		/* If the socket was closed while we were waiting, stop. Note that when the
		 * connection closes immediately after sending data, we'll receive both this
		 * message and FD_READ at the same time. Only do this if the event we really
		 * want hasn't happened yet. */
		if( (events.lNetworkEvents & (1<<FD_CLOSE_BIT)) )
			return WSAECONNRESET;
	}
}