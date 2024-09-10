BOOL 
CPuLog::Init()
{
	if (FALSE == CCriticalClient::IsActive())
	{
		return FALSE;
	}

	//
	CSmartLock cLock(static_cast<CCriticalClient*>(this));

	//
	if (NULL != m_pfpFile)
	{
		return TRUE;
	}

	//
	char achLogFile[MAX_PATH + 1];
	char achBackupLogFile[MAX_PATH + 1];

	GetPuCfgInstance().GetLogFileName(achLogFile);
	GetPuCfgInstance().GetBackupLogFileName(achBackupLogFile);

	//
	if ('\0' == achLogFile[0] || '\0' == achBackupLogFile[0])
	{
		return FALSE;
	}

	//
	remove(achBackupLogFile);
	rename(achLogFile, achBackupLogFile);

	//
	m_pfpFile = fopen(achLogFile, "a");
	if (NULL == m_pfpFile)
	{
		return FALSE;
	}

	return TRUE;
}