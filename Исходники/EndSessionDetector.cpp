void EndSessionDetector::Destroy()
{
	if (!m_isDestroyed)
	{
		m_isDestroyed = true;
		WTSUnRegisterSessionNotification(getLightpackApp()->getMainWindowHandle());
	}
}