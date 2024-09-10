bool KApplicationStatus::initialize(const char* dataDir)
{
	char filename[512];
	sprintf_k(filename, sizeof(filename), "%s/.appstatus.dat", dataDir);
	
	if(!m_mmap.Initialize(filename, 0, sizeof(ApplicationData)))
		return false;

	m_appData = (ApplicationData*)m_mmap.GetMemory();
	
	KMMap::eFileOpenStatus openStatus = m_mmap.GetOpenStatus();
	switch(openStatus)
	{
	case KMMap::enum_CreateNew:
	case KMMap::enum_ModifyExists:
		{
			memset(m_appData, 0, sizeof(ApplicationData));
			KDatetime nowDate;
			KLocalDatetime ldt = nowDate.GetLocalTime();
			m_appData->yyyy_mm_dd = ldt.year * 10000 + ldt.month * 100 + ldt.day;
			m_appData->expireTime = KDatetime::nextDayFirstSecond((TIME_T)nowDate.Time());
			m_appData->daySequence = 0;
		} break;
	}

	return true;
}