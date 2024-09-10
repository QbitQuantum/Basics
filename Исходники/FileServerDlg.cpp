CString CFileServerDlg::GetLastFileDialogPath()
{
	try
	{
		char lpszDefaultDir[MAX_PATH];
		::GetCurrentDirectory(MAX_PATH, lpszDefaultDir);

		char szDocument[MAX_PATH]={0};   
		memset(lpszDefaultDir,0,_MAX_PATH);   

		LPITEMIDLIST pidl = NULL;   
		SHGetSpecialFolderLocation(NULL, CSIDL_PERSONAL, &pidl);   
		if (pidl && SHGetPathFromIDList(pidl, szDocument))   
		{   
			//GetShortPathName(szDocument, lpszDefaultDir, _MAX_PATH);   
			lstrcpy(lpszDefaultDir, szDocument);
		}

		char lpszPath[MAX_PATH];
		ProgramConfig pConfig;
		pConfig.SetConfigFileName("FileSetting.ini");
		pConfig.ReadStringConfigParameter("File Setting", "LastFileDialogPath", lpszPath, lpszDefaultDir);

		CString strPath;
		strPath = lpszPath;
		return strPath;
	}
	catch(...)
	{
		if (gl_pLogger) gl_pLogger->log_error("CFileServerDlg::GetLastFileDialogPath unknown exception");
	}
	return "";
}