	TinyApplication* TinyApplication::GetInstance() throw()
	{
		TinyCriticalSection section;
		section.Initialize();
		if (m_pInstance == NULL)
		{
			section.Lock();
			if (m_pInstance == NULL)
			{
				m_pInstance = new TinyApplication();
			}
			section.Unlock();
		}
		section.Uninitialize();
		return m_pInstance;
	}