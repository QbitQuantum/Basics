void CTreadPool::Clear()
{
	if (m_pTp_callback_environ != NULL)
	{
		DestroyThreadpoolEnvironment(m_pTp_callback_environ);
		m_pTp_callback_environ = NULL;
	}
	if (m_pPool!=NULL)
	{
		CloseThreadpool(m_pPool);
		m_pPool = NULL;
	}
	
	m_nMaxThreads = -1;
	m_nMinThreads = -1;


}