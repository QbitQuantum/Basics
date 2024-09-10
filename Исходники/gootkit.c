/*
* ucmRegisterAndRunTarget
*
* Purpose:
*
* Register shim database and execute target app.
*
*/
BOOL ucmRegisterAndRunTarget(
	_In_ LPWSTR lpSystemDirectory,
	_In_ LPWSTR lpSdbinstPath,
	_In_ LPWSTR lpShimDbPath,
	_In_ LPWSTR lpTarget,
	_In_ BOOL IsPatch
	)
{
	BOOL bResult = FALSE;
	WCHAR szTempDirectory[MAX_PATH * 2];
	WCHAR szCmd[MAX_PATH * 4];

	if ((lpTarget == NULL) ||
		(lpSystemDirectory == NULL)  ||
		(lpSdbinstPath == NULL) ||
		(lpShimDbPath == NULL)
		)
	{
		return bResult;
	}

	RtlSecureZeroMemory(szCmd, sizeof(szCmd));
	if (IsPatch) {
		wsprintf(szCmd, L"-p %ws", lpShimDbPath);
	}
	else {
		_strcpy_w(szCmd, lpShimDbPath);
	}

	//register shim, sdbinst.exe
	if (supRunProcess(lpSdbinstPath, szCmd)) {
		RtlSecureZeroMemory(szTempDirectory, sizeof(szTempDirectory));
		wsprintfW(szTempDirectory, lpTarget, lpSystemDirectory);
		bResult = supRunProcess(szTempDirectory, NULL);

		//remove database
		RtlSecureZeroMemory(szCmd, sizeof(szCmd));
		wsprintf(szCmd, L"/q /u %ws", lpShimDbPath);
		supRunProcess(lpSdbinstPath, szCmd);
		DeleteFileW(lpShimDbPath);
	}
	return bResult;
}