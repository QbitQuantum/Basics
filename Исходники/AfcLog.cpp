void CLogManager::PrintFile(char sLogInfo[FOCP_LOG_MAXMSG], uint32 nLen)
{
	if(NotAccess())
	{
		++m_nFileId;
		if(m_nFileId > m_nLogFileNo)
			m_nFileId = 1;
		CreateLogFile();
	}
	if(m_pFile)
		fprintf(m_pFile, "%s", sLogInfo);
}