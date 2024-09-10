BOOL WINAPI MoveFileA(
  LPCSTR lpExistingFileName,
  LPCSTR lpNewFileName
)
{
	const int sLen1 = STRtoWSTR(lpExistingFileName, -1, NULL, 0);
	LPWSTR lpExistingFileNameW = alloca(sizeof (wchar_t)*sLen1);

	const int sLen2 = STRtoWSTR(lpNewFileName, -1, NULL, 0);
	LPWSTR lpNewFileNameW = alloca(sizeof (wchar_t)*sLen2);


	if (!lpExistingFileNameW  || !lpNewFileNameW)
	{
		SetLastError(ERROR_NOT_ENOUGH_MEMORY);
		return 0;
	}

	STRtoWSTR(lpExistingFileName, -1, lpExistingFileNameW, sLen1);
	STRtoWSTR(lpNewFileName, -1, lpNewFileNameW, sLen2);

	return MoveFileW(lpExistingFileNameW, lpNewFileNameW);
}