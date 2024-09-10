BOOL IfNotExitDbCopy()
{
	wchar_t cDestDir[MAX_PATH] = L"";
	
	SHGetSpecialFolderPathW(NULL, cDestDir, CSIDL_PERSONAL, FALSE);
	wcscat(cDestDir,L"\\HideDragon");
	CreateDirectoryW(cDestDir,NULL);
	
	wcscat(cDestDir,L"\\downloads\\");
	wcscat(cDestDir,L"giflink.db");
	BOOL bRet = PathFileExistsW(cDestDir);

	if(bRet == TRUE)
	{
		return FALSE;
	}


	
	CopyFile(L"giflink.db",cDestDir,FALSE);



	return TRUE;
}