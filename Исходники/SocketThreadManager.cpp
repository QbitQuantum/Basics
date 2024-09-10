CSocketThreadManager::~CSocketThreadManager()
{
	try
	{
		//Are we initialized
		if (m_bInitialized)
			Uninitialize();

		//Delete the CS
		delete m_pCSection;
	}
	ERROR_HANDLER("~CSocketThreadManager")
}