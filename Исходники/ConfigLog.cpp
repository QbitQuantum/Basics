/**
 * @brief Write archive support stuff
 */
void CConfigLog::WriteArchiveSupport()
{
	DWORD registered = VersionOf7z(FALSE);
	DWORD standalone = VersionOf7z(TRUE);
	TCHAR path[MAX_PATH];
	DWORD type = 0;
	DWORD size = sizeof path;

	WriteItem(0, _T("Archive support"));
	WriteItem(1, _T("Enable"),
		AfxGetApp()->GetProfileInt(_T("Merge7z"), _T("Enable"), 0));

	wsprintf(path, _T("%u.%02u"), UINT HIWORD(registered), UINT LOWORD(registered));
	WriteItem(1, _T("7-Zip software installed on your computer"), path);
	static const TCHAR szSubKey[] = _T("Software\\7-Zip");
	static const TCHAR szValue[] = _T("Path");
	SHGetValue(HKEY_LOCAL_MACHINE, szSubKey, szValue, &type, path, &size);
	WriteVersionOf7z(path);

	wsprintf(path, _T("%u.%02u"), UINT HIWORD(standalone), UINT LOWORD(standalone));
	WriteItem(1, _T("7-Zip components for standalone operation"), path);
	GetModuleFileName(0, path, countof(path));
	LPTSTR pattern = PathFindFileName(path);
	PathRemoveFileSpec(path);
	WriteVersionOf7z(path);

	WriteItem(1, _T("Merge7z plugins on path"));
	lstrcpy(pattern, _T("Merge7z*.dll"));
	WriteVersionOf(2, path);
	// now see what's on the path:
	if (DWORD cchPath = GetEnvironmentVariable(_T("path"), 0, 0))
	{
		static const TCHAR cSep[] = _T(";");
		LPTSTR pchPath = new TCHAR[cchPath];
		GetEnvironmentVariable(_T("PATH"), pchPath, cchPath);
		LPTSTR pchItem = pchPath;
		while (int cchItem = StrCSpn(pchItem += StrSpn(pchItem, cSep), cSep))
		{
			if (cchItem < MAX_PATH)
			{
				CopyMemory(path, pchItem, cchItem*sizeof*pchItem);
				path[cchItem] = 0;
				PathAppend(path, _T("Merge7z*.dll"));
				WriteVersionOf(2, path);
			}
			pchItem += cchItem;
		}
		delete[] pchPath;
	}
}