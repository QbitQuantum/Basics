BOOL KStasticFluxCacheMgr::OpenCacheFile()
{
	BOOL	bRes = FALSE;
	HANDLE hFile = NULL;

	kws_log(TEXT("KStasticFluxCacheMgr::OpenCacheFile begin"));

	DWORD nWriteSize = 0;
	HANDLE hFileMap = NULL;
	BYTE* pMapBuf = NULL;
	KSecurityDesAcessByAnyone secByAny;

	hFile = ::CreateFile(m_strCacheFile,
		GENERIC_READ | GENERIC_WRITE,
		0, //FILE_SHARE_READ|FILE_SHARE_WRITE, 
		secByAny, 
		OPEN_EXISTING, 
		FILE_ATTRIBUTE_NORMAL, 
		NULL);

	if (hFile == INVALID_HANDLE_VALUE)
	{
		kws_log(TEXT("create file error :%d: %s"), ::GetLastError(), (LPCWSTR)m_strCacheFile);
		goto exit0;
	}

	if (!VerifyCacheFile(hFile))
	{
		kws_log(TEXT("VerifyCacheFile failed:"));
		goto exit0;
	}

	hFileMap = ::CreateFileMapping(hFile, secByAny, PAGE_READWRITE | SEC_COMMIT, 
		0, ::GetFileSize(hFile, NULL), m_strUrlMapName);

	if (NULL == hFileMap)
	{
		kws_log(TEXT("CreateFileMapping failed: %d"), ::GetLastError());
		goto exit0;
	}

	pMapBuf = (BYTE*)::MapViewOfFile(hFileMap, FILE_MAP_READ | FILE_MAP_WRITE, 0, 0, 0);

	m_hFile = hFile;
	m_hFileMap = hFileMap;
	m_pData = pMapBuf;

	SetObjectToLowIntegrity(m_hFile);
	SetObjectToLowIntegrity(m_hFileMap);

	kws_log(TEXT("KStasticFluxCacheMgr::OpenCacheFile end sucess"));
	return TRUE;

exit0:
	if (pMapBuf)
	{
		UnmapViewOfFile(pMapBuf);
		pMapBuf = NULL;
	}
	if (hFileMap)
	{
		::CloseHandle(hFileMap);
		hFileMap = NULL;
	}
	if (hFile)
	{
		::CloseHandle(hFile);
		hFile = NULL;
	}
	return FALSE;
}