DWORD CFileDownloader::Download( LPCTSTR lpszURL, LPCTSTR lpszFilename, LPCTSTR lpszRefererUrl, LPVOID pUserData, BOOL bUseCache, BOOL bUseProxyConfig )
{
	m_Stopped = FALSE;
	if(!SplitDownloadUrl( lpszURL, m_strHostname, m_strHostPath, m_strHostFilename ))
		return FALSE;
	
	m_pUserData = pUserData;
	m_strDownloadURL = lpszURL;
	m_strDownloadFile = lpszFilename;

	// Check the tmp file 
	m_strDownloadFileTemp = m_strDownloadFile + _T(".tmp");
	m_strDownloadFileInfo = m_strDownloadFile + _T(".nfo");		
	
	// Check if file exists 
	if( bUseCache && IsFileExist(m_strDownloadFile) )
	{
		return TRUE;
	}
	else if(!bUseCache)
	{
		DeleteFile(m_strDownloadFileTemp);
		DeleteFile(m_strDownloadFileInfo);
		DeleteFile(m_strDownloadFile);
	}
	
	CPubConfig::T_ProxySetting proxyconfig;
	CPubConfig pubconfig;
	pubconfig.LoadProxyConfig(proxyconfig);	
	SetProxySetting(proxyconfig);


	INT64 lContentSize = 0;
	INT64 lFileSize = 0;
	if( IsFileExist(m_strDownloadFileTemp) && IsFileExist(m_strDownloadFileInfo) )
	{
		CString strLastModified;
		BOOL notModified = FALSE;
		if( file_get_contents(m_strDownloadFileInfo, strLastModified) )		
		{
			LPCTSTR lpszLengthTag = _T("; length=");
			LPCTSTR pszLen = _tcsstr(strLastModified, lpszLengthTag);
			if(pszLen)
			{
				pszLen+= _tcslen(lpszLengthTag);
				lContentSize = _ttoi64(pszLen);
			}

			// 检查文件是否完全下载完成了 
			lFileSize = file_get_size( m_strDownloadFileTemp );
			if(lFileSize>0 && lFileSize==lContentSize)
			{
				MoveFile(m_strDownloadFileTemp, m_strDownloadFile);
				DeleteFile(m_strDownloadFileInfo);
				return TRUE;
			}

			if( _CheckIfModifiedSince(lpszURL, strLastModified, bUseProxyConfig, notModified) && notModified )
			{
			}
			else
			{
				lFileSize = 0;
			}
		}
	}
	// 如果文件已经过期, 或者文件的信息文件不存在, 都删除旧下载临时文件 
	if(lFileSize==0)
	{
		DeleteFile(m_strDownloadFileTemp);
		DeleteFile(m_strDownloadFileInfo);
	}
	
	// Prepare file 
	_CloseFileHandler();
	m_hFile = CreateFile(m_strDownloadFileTemp, GENERIC_WRITE, 0, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if( m_hFile==INVALID_HANDLE_VALUE )
		return FALSE;
	SetFilePointer( m_hFile, lFileSize, 0, FILE_BEGIN );
	
	if(m_pBuffer==NULL)
		m_pBuffer = new BYTE[HTTP_BUFFER_SIZE];	
	INT nRetry = HTTP_DEFAULT_RETYR;
	INT nRetried = 0;
	do 
	{
		INT iRet = _DownloadFileFrom(lFileSize, lContentSize, bUseProxyConfig);
		DEBUG_TRACE(_T("FD:_DownloadFileFrom %I64d/%I64d LastError:%d Ret:%d"), lFileSize, lContentSize, GetLastError(), iRet);
		_Cleanup();

		if(iRet>0)
		{
			// 考虑socket 被主动关闭 
			if(lFileSize>=lContentSize)
				break;
			nRetry = HTTP_DEFAULT_RETYR;
		}
		else if(iRet==0)
		{
			--nRetry;
		}
		else if(iRet==-1)
		{
			// 文件长度不匹配! 需要删了文件, 然后重新下载 
			_CloseFileHandler();
			DeleteFile(m_strDownloadFileTemp);
			DeleteFile(m_strDownloadFileInfo);
			lFileSize = lContentSize = 0;
			
			m_hFile = CreateFile(m_strDownloadFileTemp, GENERIC_WRITE, 0, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
			if( m_hFile==INVALID_HANDLE_VALUE )
				break;
			--nRetry;
		}
		else if(iRet==-2)
		{
			// 写入文件失败, 直接返回
			break;
		}
		else
		{
			ATLASSERT(FALSE);
			break;
		}
		++ nRetried;
	} while (!m_Stopped && nRetry>0 && nRetried<HTTP_DEFAULT_MAXRETYR);
	
	_CloseFileHandler();
	BOOL bFileDone = FALSE;
	if(lContentSize==0)
	{
		// 163.com 等页面
		if(lFileSize==0)
		{
			DeleteFile(m_strDownloadFileTemp);
		}
		else if(!m_Stopped)
		{
			bFileDone = TRUE;
		}
	}
	else
	{
		bFileDone = lFileSize>=lContentSize;
	}
	if(bFileDone)
	{
		MoveFile(m_strDownloadFileTemp, m_strDownloadFile);
		DeleteFile(m_strDownloadFileInfo);
	}
	BOOL bRet = PathFileExists(m_strDownloadFile);
	_FireFileDownloaderEvent(bRet ? IFileDownloaderObserver::DOWNLOAD_COMPLETE : IFileDownloaderObserver::DOWNLOAD_ERROR);
	return bRet;
}