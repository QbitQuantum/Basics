void CPipeServer::Close()
{
	// close thread handle
	EnterCriticalSection(&m_sInitSafe);
	m_bWorking= false;

	DWORD dwRes= WAIT_OBJECT_0 +1;
	if (m_hThread)
	{
		if (m_hDone)
			dwRes= SignalObjectAndWait(m_hDone, m_hThread, 2000, FALSE);
		if (dwRes != WAIT_OBJECT_0)
		{
			TerminateThread(m_hThread, 0);
			DeleteCriticalSection(&m_sPipeSafe);	// we do this so that we can enter cc after close, in case it was terminated in cc.
			InitializeCriticalSection(&m_sPipeSafe);
		}
	}
	for (size_t i= 0; i<m_aPipes.size();++i)
	{
		m_pcMemPool->PoolRelease(m_aPipes[i]->pRead);
		DecreaseQueue(m_aPipes[i]->ClearQueue());
		delete m_aPipes[i];
	}
	m_aPipes.clear();
	if (m_hDone) CloseHandle(m_hDone);
	if (m_hThread) CloseHandle(m_hThread);
	m_hThread= NULL;
	m_hDone= NULL;
	m_pcDevice= NULL;
	m_pcLogBuffer= NULL;
	m_sStream.str(_T(""));
	LeaveCriticalSection(&m_sInitSafe);
}