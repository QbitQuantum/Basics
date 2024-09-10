bool
CNdasService::Impl::StartWorkItems(DWORD& nStarted)
{
	nStarted = 0;
	if (!QueueUserWorkItem(m_wiHeartbeatListener, m_cHeartbeatListener)) 
	{
		return false;
	}
	++nStarted;
	if (!QueueUserWorkItem(m_wiAutoRegProcess, m_cAutoRegProcessor)) 
	{
		return false;
	}
	++nStarted;
	if (!QueueUserWorkItem(m_wiIXBCaster, m_cIXBCaster)) 
	{
		return false;
	} 
	++nStarted;
	if (!QueueUserWorkItem(m_wiIXServer, m_cIXServer)) 
	{
		return false;
	}
	++nStarted;
	if (!QueueUserWorkItem(m_wiHIXServer, m_cHIXServer)) 
	{
		return false;
	} 
	++nStarted;
	if (!QueueUserWorkItem(m_wiEventMonitor, m_cEventMonitor)) 
	{
		return false;
	}
	++nStarted;
	if (!QueueUserWorkItem(m_wiEventPublisher, m_cEventPublisher)) 
	{
		return false;
	}
	++nStarted;
	return true;
}