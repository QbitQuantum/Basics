HRESULT CLTDMFileStream::Open(WCHAR * lpFileName,unsigned long dwDesiredAccess)
{
#ifdef USE_DSTREAM
	Close();

	// make sure file name is not null
	if (lpFileName == NULL)
	{
		return E_FAIL;
	}

	// convert file name to regular characters
	char sFileName[MAX_PATH];
	wcstombs( sFileName, lpFileName, MAX_PATH );

	// create an item in the OpenQueueMgr
	m_pOpenQueueItem = g_LTDMDStreamOpenQueueMgr.Create(sFileName);
	if (m_pOpenQueueItem == NULL)
	{
		return E_FAIL;
	}

	// open the file
	if (m_pOpenQueueItem->Open() != LT_OK)
	{
		LTDMConOutWarning("LTDirectMusic loader failed to open file %s\n", sFileName);

		// destroy the OpenQueue item
		g_LTDMDStreamOpenQueueMgr.Destroy(m_pOpenQueueItem);
		m_pOpenQueueItem = NULL;

		return E_FAIL;
	}

	// make sure we are at the start of the file
	// there is no reason to do this since we just opened the file

	LTDMConOutMsg(5, "CLTDMFileStream::Open FileName=%s\n", sFileName);

	// we succeed
	return S_OK;
#endif

#ifdef USE_REZMGR
	// convert the file name to regular characters from wide
	char sFileName[MAX_PATH];
	wcstombs( sFileName, lpFileName, MAX_PATH );

	// if the loader doesn't exist fail
	if (m_pLoader == NULL)
	{
		LTDMConOutWarning("LTDirectMusic loader failed to open file %s because no directmusic loader exists\n", sFileName);
		return E_FAIL;
	}

	m_pLoader->EnterRezMgrCriticalSection();

	// if the rezmgr is not open then fail
	if (!m_pLoader->GetRezMgr()->IsOpen())
	{
		LTDMConOutWarning("LTDirectMusic loader failed to open file %s because rez file was not open\n", sFileName);
		m_pLoader->LeaveRezMgrCriticalSection();
		return E_FAIL;
	}

	// we don't support write access so fail if it was requested
	if( dwDesiredAccess == GENERIC_WRITE )
	{
		LTDMConOutWarning("LTDirectMusic loader failed to open file %s for writing because writing is not supported\n", sFileName);
		m_pLoader->LeaveRezMgrCriticalSection();
		return DMUS_E_LOADER_FAILEDOPEN;
	}

	// get the rez item
	m_pRezItem = m_pLoader->GetRezMgr()->GetRezFromDosPath(sFileName);

	// if the item was not found we fail
	if (m_pRezItem == NULL)
	{
		LTDMConOutWarning("LTDirectMusic loader failed to open file %s\n", sFileName);
		m_pLoader->LeaveRezMgrCriticalSection();
		return DMUS_E_LOADER_FAILEDOPEN;
	}

	// seek to start of item
//	m_pRezItem->Seek(0);
	m_nCurPos = 0;

	LTDMConOutMsg(5, "CLTDMFileStream::Open FileName=%s\n", sFileName);

	// we succeed
	m_pLoader->LeaveRezMgrCriticalSection();
	return S_OK;
#endif

#ifdef USE_FILE
	Close();
    if( dwDesiredAccess == GENERIC_READ )
    {
		if (g_fIsUnicode)
		{
			m_pFile = _wfsopen( lpFileName, L"rb", _SH_DENYWR );
		}
		else
		{
			char path[MAX_PATH];
			wcstombs( path, lpFileName, MAX_PATH );
			m_pFile = _fsopen( path, "rb", _SH_DENYWR );
		}
	}
    else if( dwDesiredAccess == GENERIC_WRITE )
    {
		if (g_fIsUnicode)
		{
			m_pFile = _wfsopen( lpFileName, L"wb", _SH_DENYNO );
		}
		else
		{
			char path[MAX_PATH];
			wcstombs( path, lpFileName, MAX_PATH );
			m_pFile = _fsopen( path, "wb", _SH_DENYNO );
		}
	}
	if (m_pFile == NULL)
	{
		return DMUS_E_LOADER_FAILEDOPEN;
	}
	return S_OK;
#endif
}