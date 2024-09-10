void CLogArchiver::Process(CLogMsg& oLog)
{
	CString oLogInfo;
	GetLogInfo(oLog, oLogInfo);
	if(NotAccess())
	{
		++m_nLogId;
		if(m_nLogId > m_nLogNo)
		{
			if(m_bNeedArch)
			{
				m_oFile.Redirect(NULL);
				DoArchive();
			}
			m_nLogId = 1;
		}
		CreateLogFile();
	}
	m_oFile.Write(oLogInfo.GetStr(), oLogInfo.GetSize());
}