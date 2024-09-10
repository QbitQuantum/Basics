bool KLogFileReader::searchNextLogFile(OUT LogFile* logFile)
{
	KDatetime now;
	KLocalDatetime ldt = now.GetLocalTime();
	ldt.hour = ldt.minute = ldt.second = 0;
	now.SetLocalTime(ldt);

	memset(&ldt, 0, sizeof(ldt));
	ldt.year = m_logFile->yyyymmdd / 10000;
	ldt.month = (m_logFile->yyyymmdd / 100) % 100;
	ldt.day = m_logFile->yyyymmdd % 100;
	KDatetime dt(ldt); dt.AddDay(1);

	*logFile = *m_logFile;
	while(dt <= now)
	{
		ldt = dt.GetLocalTime();
		int year = ldt.year; int month = ldt.month; int day = ldt.day;
		int yyyymmdd = year * 10000 + month * 100 + day;
		logFile->yyyymmdd = yyyymmdd;
		logFile->sequence = 0;
		logFile->readOffset = 0;
		string_512 filePath = g_pApp->m_statusFile.buildLogFilePath(*logFile);
		if(JG_F::KFileUtil::IsFileExists(filePath.c_str()))
			return true;
		dt.AddDay(1);
	}

	return false;
}