CGitStatusCache::CGitStatusCache(void)
{
	#define forever DWORD(-1)
	AutoLocker lock(m_NoWatchPathCritSec);
	TCHAR path[MAX_PATH] = { 0 };
	SHGetFolderPath(NULL, CSIDL_COOKIES, NULL, 0, path);
	m_NoWatchPaths[CTGitPath(CString(path))] = forever;
	SecureZeroMemory(path, sizeof(path));
	SHGetFolderPath(NULL, CSIDL_HISTORY, NULL, 0, path);
	m_NoWatchPaths[CTGitPath(CString(path))] = forever;
	SecureZeroMemory(path, sizeof(path));
	SHGetFolderPath(NULL, CSIDL_INTERNET_CACHE, NULL, 0, path);
	m_NoWatchPaths[CTGitPath(CString(path))] = forever;
	SecureZeroMemory(path, sizeof(path));
	SHGetFolderPath(NULL, CSIDL_SYSTEM, NULL, 0, path);
	m_NoWatchPaths[CTGitPath(CString(path))] = forever;
	SecureZeroMemory(path, sizeof(path));
	SHGetFolderPath(NULL, CSIDL_WINDOWS, NULL, 0, path);
	m_NoWatchPaths[CTGitPath(CString(path))] = forever;
	if (SysInfo::Instance().IsVistaOrLater())
	{
		CAutoLibrary hShell = AtlLoadSystemLibraryUsingFullPath(_T("shell32.dll"));
		if (hShell)
		{
			typedef HRESULT STDAPICALLTYPE SHGetKnownFolderPathFN(__in REFKNOWNFOLDERID rfid, __in DWORD dwFlags, __in_opt HANDLE hToken, __deref_out PWSTR *ppszPath);
			SHGetKnownFolderPathFN *pfnSHGetKnownFolderPath = (SHGetKnownFolderPathFN*)GetProcAddress(hShell, "SHGetKnownFolderPath");
			if (pfnSHGetKnownFolderPath)
			{
				KNOWNFOLDERID folderids[] = { FOLDERID_Cookies, FOLDERID_History, FOLDERID_InternetCache, FOLDERID_Windows, FOLDERID_CDBurning, FOLDERID_Fonts, FOLDERID_RecycleBinFolder }; //FOLDERID_SearchHistory
				for (KNOWNFOLDERID folderid : folderids)
				{
					PWSTR pszPath = NULL;
					if (pfnSHGetKnownFolderPath(folderid, KF_FLAG_CREATE, NULL, &pszPath) != S_OK)
						continue;

					m_NoWatchPaths[CTGitPath(CString(pszPath))] = forever;
					CoTaskMemFree(pszPath);
				}
			}
		}
	}
	m_bClearMemory = false;
	m_mostRecentExpiresAt = 0;
}