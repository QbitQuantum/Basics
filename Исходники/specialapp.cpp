BOOL CSpecialApp::ScanXunleiSearch(int iType)
{
	KSearchSoftwareStruct sss;
	std::vector<std::wstring>::iterator it;
	WCHAR szPath[MAX_PATH] = {0};
	sss.pszMainFileName      = TEXT( "Program\\thunder.exe" );
	sss.hRegRootKey          = HKEY_LOCAL_MACHINE;
	sss.pszRegSubKey         = TEXT( "SOFTWARE\\Thunder Network\\ThunderOem\\thunder_backwnd" );
	sss.pszPathValue      	 = TEXT( "dir" );
	sss.bFolder              = TRUE;
	BOOL bRet = FALSE;
	std::wstring str;
	std::wstring strPath;
	std::wstring strTemp;
	bRet = SearchSoftwarePath( &sss, strPath);
	wcscpy_s(szPath, MAX_PATH - 1, strPath.c_str());
	PathRemoveFileSpec(szPath);
	PathRemoveFileSpec(szPath);
	PathAppend(szPath, L"Profiles\\GougouSearch\\history.history");
	strPath  = szPath;
	if (GetFileAttributes(strPath.c_str()) == INVALID_FILE_ATTRIBUTES)
	{
		WCHAR* pEnv = NULL;
		WCHAR  szPath[MAX_PATH] = {0};
		pEnv = _wgetenv(_T("public"));
		if (pEnv != NULL)
		{
			wcscpy(szPath, pEnv);
			PathAppend(szPath, L"Documents\\Thunder Network\\Thunder\\Profiles\\GougouSearch\\history.history");
			strPath = szPath;
		}
		else
		{
			return TRUE;
		}
	}

	g_fnScanFile(g_pMain, BEGINPROC(XUNLEI7_DOWNLOADER), 0, 0, 0);
	for (it = g_listProcessName.begin(); it != g_listProcessName.end(); it++ )
	{
		str = *it;
		transform(str.begin(), str.end(), str.begin(), towlower);
		if (str == L"thunder.exe")
		{
			str = L"正在运行，跳过";
			goto clean0;
		}
	}
	str = L"";
	if (m_bScan)
	{
		ModifyTxtData(iType, strPath.c_str());
//		m_appHistory.CommfunFile(KUWOMUSIC_PLAYER, strPath.c_str(), vec_file);
	}
clean0:
	g_fnScanFile(g_pMain, ENDPROC(XUNLEI7_DOWNLOADER), str.c_str(), 0, 0);

	return TRUE;
}