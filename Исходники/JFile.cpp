long CJFile::Read(void* pBuf, long lSize)
{
	m_lockRW.Lock();
	if(NULL == m_pFile)
	{
		m_lockRW.Unlock();
		return -1;
	}

	DWORD dwTime = GetTickCount();
	DWORD dwReded = 0;
	DWORD iErrTick = 0;
	while(dwReded < (DWORD)lSize)
	{
		if(GetTickCount() - dwTime > (DWORD)m_lTimeOut)
		{
			break;
		}

		size_t uRet = fread((BYTE*)pBuf + dwReded, 1, lSize - dwReded, m_pFile);
		if(uRet > 0)
		{
			dwReded += uRet;
		}
		else
		{
			iErrTick++;
			if(iErrTick > 3)
			{
				m_lErrCode = *_errno();
			}
		}
	}

	m_lockRW.Unlock();
	return dwReded;
}