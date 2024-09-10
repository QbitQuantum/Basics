BOOL CFileMove::MoveFile(LPCTSTR lpExistingFileName, LPCTSTR lpNewFileName, DWORD dwFlags)
{
	if (lpExistingFileName == NULL)
	{
		::SetLastError(ERROR_INVALID_PARAMETER);
		return FALSE;
	}

	// 去掉只读属性
	RemoveReadonlyAttribute(lpExistingFileName);
	RemoveReadonlyAttribute(lpNewFileName);

	if (!m_bIsWow64)
	{
		return MoveFileEx(lpExistingFileName, lpNewFileName, dwFlags);
	}

	TCHAR szSystemWow64[MAX_PATH] = {0};
	if (!GetWow64Directory(szSystemWow64, countof(szSystemWow64)))
	{
		return FALSE;
	}

	TCHAR szSystem32[MAX_PATH] = {0};
	if (!GetSystemDirectory(szSystem32, countof(szSystem32)))
	{
		return FALSE;
	}

	TCHAR szSysNative[MAX_PATH] = {0};
	if (!GetWindowsDirectory(szSysNative, countof(szSysNative)))
	{
		return FALSE;
	}

	StringCchCat(szSysNative, countof(szSysNative), _T("\\Sysnative"));

	TCHAR szExistingFileName[MAX_PATH] = {0};
	TCHAR szNewFileName[MAX_PATH] = {0};
	TCHAR * pNewMoveFileName = NULL;

	RevertFsRedirection(lpExistingFileName, szSystem32, szSystemWow64,
		szExistingFileName, countof(szExistingFileName));

	RevertFsRedirection(szExistingFileName, szSysNative, szSystem32,
		szExistingFileName, countof(szExistingFileName));

	if (lpNewFileName != NULL)
	{
		RevertFsRedirection(lpNewFileName, szSystem32, szSystemWow64,
			szNewFileName, countof(szNewFileName));

		RevertFsRedirection(szNewFileName, szSysNative, szSystem32,
			szNewFileName, countof(szNewFileName));

		pNewMoveFileName = szNewFileName;
	}

	// 关闭32位程序在64位系统下的自动重定向功能

	PVOID pOldValue = NULL;
	if (!Wow64DisableWow64FsRedirection(&pOldValue))
	{
		return FALSE;
	}

	DWORD dwLastError = ERROR_SUCCESS;
	BOOL bMoveFile = MoveFileEx(szExistingFileName, pNewMoveFileName, dwFlags);
	if (!bMoveFile)
	{
		dwLastError = ::GetLastError();
	}

	// 恢复32位程序在64位系统下的自动重定向功能
	if (!Wow64RevertWow64FsRedirection(pOldValue))
	{
		return FALSE;
	}

	::SetLastError(dwLastError);
	return bMoveFile;
}