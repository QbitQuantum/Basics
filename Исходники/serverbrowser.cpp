void CGNetUpdater::Cleanup()
{
	if(m_pMasterServer)
	{
		if(m_dwMasterServerCookie)
		{
			AtlUnadvise(m_pMasterServer, IID_IRemoteMasterServerEvents, m_dwMasterServerCookie);
			m_dwMasterServerCookie = NULL;
		}

		if(m_dwMasterServerCookie2)
		{
			AtlUnadvise(m_pMasterServer, IID_IGameEvents, m_dwMasterServerCookie2);
			m_dwMasterServerCookie2 = NULL;
		}

		m_pMasterServer.Release();
	}
}