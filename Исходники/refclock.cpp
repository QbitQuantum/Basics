CBaseReferenceClock::~CBaseReferenceClock()
{

    if (m_TimerResolution) timeEndPeriod(m_TimerResolution);

    m_pSchedule->DumpLinkedList();

    if (m_hThread)
    {
        m_bAbort = TRUE;
        TriggerThread();
        WaitForSingleObject( m_hThread, INFINITE );
        EXECUTE_ASSERT( CloseHandle(m_hThread) );
        m_hThread = 0;
        EXECUTE_ASSERT( CloseHandle(m_pSchedule->GetEvent()) );
	delete m_pSchedule;
    }
}