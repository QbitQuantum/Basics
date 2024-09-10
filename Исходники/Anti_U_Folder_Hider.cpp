BOOL ScanUDisk(IN LPCTSTR lpUDisk,IN BOOL bDelSuspicious)
{
	size_t dwLen = 0;
	size_t dwDirNameLen = 0;

	LPTSTR lpSearchDisk = NULL;		//The U Disk to search
	LPTSTR lpDirName = NULL;		//Full file path
	LPTSTR lpFileName = NULL;		//File with the same name as a directory, but has a ".exe" type extension

	HANDLE hFind = INVALID_HANDLE_VALUE;
	WIN32_FIND_DATA FindFileData;

	//Build the search string
	StringCchLength(lpUDisk,20/*set this to 4 later*/,&dwLen);
	lpSearchDisk = (LPTSTR)LocalAlloc(LPTR,(dwLen+2) * sizeof(TCHAR));
	StringCchPrintf(lpSearchDisk,dwLen+3,TEXT("%s%s"),lpUDisk,TEXT("*"));

	hFind = FindFirstFile(lpSearchDisk, &FindFileData);
	if (hFind != INVALID_HANDLE_VALUE)
	{
		do
		{
			if ( IsDotsDirectory(FindFileData.cFileName) )
				continue;

			//construct the directory or file full path
			StringCchLength(FindFileData.cFileName,MAX_PATH,&dwDirNameLen);	//get the directory name length
			dwDirNameLen += dwLen + 2;
			lpDirName = (LPTSTR)LocalAlloc(LPTR,dwDirNameLen * sizeof(TCHAR));	
			StringCchPrintf(lpDirName,LocalSize((HLOCAL)lpDirName),TEXT("%s%s"),lpUDisk,FindFileData.cFileName);
			
			//construct the full suspicious file path
			lpFileName = (LPTSTR)LocalAlloc(LPTR,(dwDirNameLen + 4) * sizeof(TCHAR));
			StringCchPrintf(lpFileName,LocalSize((HLOCAL)lpFileName),TEXT("%s.exe"),lpDirName);

			if ( (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == FILE_ATTRIBUTE_DIRECTORY )
			{
				//it's a directory
				SetFileAttributes(lpDirName,FindFileData.dwFileAttributes & ~FILE_ATTRIBUTE_HIDDEN & ~FILE_ATTRIBUTE_SYSTEM);
				
				if( bDelSuspicious )
				{
					//delete suspicious file
					DelSuspiciousFile(lpFileName,FindFileData.dwFileAttributes);
				}
			}
			else		//it's a file
			{	
				if( bDelSuspicious )
				{
					//delete "autorun.inf"
					if( !_tcsicmp(FindFileData.cFileName,TEXT("autorun.inf")) )
						DelSuspiciousFile(lpDirName,FILE_ATTRIBUTE_NORMAL);
						
					//delete other malicious files
					if( IsFileMalicious(FindFileData.cFileName) )
					{						
						DelSuspiciousFile(lpDirName,FindFileData.dwFileAttributes);
					}
				}
			}

		} while (FindNextFile(hFind, &FindFileData));
	}
	FindClose(hFind);
	hFind = NULL;

	LocalFree((HLOCAL)lpDirName);
	LocalFree((HLOCAL)lpSearchDisk);
	lpSearchDisk = NULL;
	lpDirName = NULL;	
	
	return TRUE;
}