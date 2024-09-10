void VirtualOHT::DestoryTimer(void)
{
	if (m_nTimerID > 0)
	{
		timeKillEvent(m_nTimerID);
		timeEndPeriod(1);
		m_nTimerID = 0;
	}
}