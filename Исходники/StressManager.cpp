	CStressManager::~CStressManager()
	{
		m_mapCases.clear();

		if(m_hTimerQueue)
		{
			DeleteTimerQueue(m_hTimerQueue);
			m_hTimerQueue = NULL;
		}
		
		ASockIOFini();
		A_MUTEX_DESTROY(&m_mtxLocker);
	}