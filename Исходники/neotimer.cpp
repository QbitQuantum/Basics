NeoTimer::~NeoTimer()
{
#ifdef WIN32
    if (!DeleteTimerQueue(m_hTimerQueue))
        printf("DeleteTimerQueue failed (%d)\n", GetLastError());
#else
    if (m_myEpoll)
    {
    	delete(m_myEpoll);
    	m_myEpoll = NULL;
    }

    map<string, int>::iterator iter;
	for(iter=m_hTimers.begin();iter!=m_hTimers.end();++iter)
	{
		if(iter->second!=0)
			close(iter->second);
	}
#endif
    if(!m_hTimers.empty())
    {
        m_hTimers.clear();
    }
}