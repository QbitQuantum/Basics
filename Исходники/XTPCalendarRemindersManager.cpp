int CXTPCalendarReminders::Find(CXTPCalendarEvent* pEvent) const
{
	if (!pEvent)
	{
		ASSERT(FALSE);
		return -1;
	}

	CXTPCalendarReminder eventRmd;
	eventRmd.SetEvent(pEvent);

	int nCount = GetCount();
	for (int i = 0; i < nCount; i++)
	{
		CXTPCalendarReminder* pRmdI = GetAt(i, FALSE);
		ASSERT(pRmdI);

		if (pRmdI && eventRmd.IsEqualID(pRmdI))
		{
			return i;
		}
	}
	return -1;
}