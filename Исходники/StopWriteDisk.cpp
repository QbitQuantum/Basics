	BOOL WriteFileData( LPCVOID lpBuffer, CONST DWORD nNumberOfBytesToWrite,LPDWORD lpNumberOfBytesWritten,CONST ULONGLONG ulFilePointer  )
	{
		if(FALSE==CheckSafe()) return FALSE;
		m_rwLock.wlock();

		ULONGLONG ulPreMemLen = m_ulMemLen;

		ULONGLONG dwNeedExLen = 0;
		if ( m_ulMemLen < ulFilePointer+nNumberOfBytesToWrite )
		{
			dwNeedExLen = ulFilePointer+nNumberOfBytesToWrite - m_ulMemLen;
		}

		if ( dwNeedExLen > 0 )
		{
			if ( NULL == m_pMemBuf )
			{
				ULONGLONG ulAllocLen = ( dwNeedExLen/4096+1)*4096;
				m_pMemBuf = (BYTE *)malloc(ulAllocLen);
				m_ulMemLen = ulAllocLen;
			}
			else
			{
				ULONGLONG ulAllocLen = ( dwNeedExLen/4096+1)*4096+m_ulMemLen;
				m_pMemBuf = (BYTE *)realloc(m_pMemBuf,ulAllocLen);
				m_ulMemLen = ulAllocLen;
			}	
		}


		g_DebugLock.Lock();

		nCurMemUse+=(m_ulMemLen-ulPreMemLen);
		if (nCurMemUse > nMaxMemUse)
		{
			nMaxMemUse = nCurMemUse;
		}

#ifdef DEBUG
		CString strMsgOut;
		strMsgOut.Format(L"当前内存占用 %u 最大内存占用 %u\r\n",nCurMemUse,nMaxMemUse);
		OutputDebugStringW(strMsgOut);
		
		strMsgOut.Format(L"%d",GetCurrentProcessId());
		CString strTemp;
		strTemp.Format(L"%ul",nMaxMemUse);
		WritePrivateProfileStringW(L"MaxMemUse",strMsgOut,strTemp,L"C:\\MatrixDebug.log");
#endif
		g_DebugLock.UnLock();

		memcpy_s(m_pMemBuf+ulFilePointer,nNumberOfBytesToWrite,lpBuffer,nNumberOfBytesToWrite);

		m_ulFileLen = ulFilePointer+nNumberOfBytesToWrite;

		if(lpNumberOfBytesWritten)
		{
			*lpNumberOfBytesWritten = nNumberOfBytesToWrite;
		}

		m_rwLock.unlock();


		return TRUE;
	}