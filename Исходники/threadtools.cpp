void CThread::Stop(int exitCode)
{
	if ( !IsAlive() )
		return;

	if ( GetCurrentCThread() == this )
	{
		m_result = exitCode;
		if ( !( m_flags & SUPPORT_STOP_PROTOCOL ) )
		{
			OnExit();
			g_pCurThread = NULL;

#ifdef _WIN32
			CloseHandle( m_hThread );
			m_hThread = NULL;
#endif
			m_threadId = 0;
		}
		throw exitCode;
	}
	else
		AssertMsg( 0, "Only thread can stop self: Use a higher-level protocol");
}