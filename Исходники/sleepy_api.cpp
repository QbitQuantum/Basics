SleepyApi::Impl::~Impl()
{
	if (m_conv)
	{
		DdeDisconnect(m_conv);
		m_conv=NULL;
	}
	if (m_appId)
	{
		DdeFreeStringHandle(m_appId,m_service);
		DdeFreeStringHandle(m_appId,m_topic);
		DdeFreeStringHandle(m_appId,m_paused);
		
		DdeUninitialize(m_appId);
	}
	assert(m_instance==this);
	m_instance=NULL;
}