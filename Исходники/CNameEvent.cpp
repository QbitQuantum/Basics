BOOL CNameEvent::OpenEvent()
{
	assert(ISNULL(m_hEvent));
	if (ISNOTNULL(m_hEvent))
	{
		DOLOG("the Event already opened!");
		return FALSE;
	}
	
	m_hEvent = OpenEventA(EVENT_MODIFY_STATE, FALSE, m_cbEventName);
	
	assert(ISNOTNULL(m_hEvent));
	if (ISNULL(m_hEvent))
	{
		DOLOG("open Event failed! " + GetLastError());
		return FALSE;
	}

	return TRUE;
}