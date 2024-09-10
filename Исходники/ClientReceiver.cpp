void CClientReceiver::Stop(void)
{
	// Kill the thread
	if( m_pCriticalSection != NULL )
	{
		WSASetEvent( m_pThreadData->m_aReservedEvents[0] );
		m_pCriticalSection = NULL;
	}

	// Wait for the thread to die
	if( m_pThread != NULL )
	{
		WaitForSingleObject( m_pThread->m_hThread, 5000 );
		m_pThread = NULL;
	}

	// Destroy message window
	this->DestroyWindow();
}