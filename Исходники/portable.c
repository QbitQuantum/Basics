BOOL WINAPI WaitWriteFile(LPCWSTR ap_path)
{
	BOOL  ret = FALSE;
	WCHAR profile_path[MAX_PATH+1] = {0};
	BOOL  pname = is_thunderbird();
	if (pname)
	{
		_snwprintf(profile_path,MAX_PATH,L"%ls%ls",ap_path,L"\\Thunderbird\\profiles.ini");
	}
	else
	{
		_snwprintf(profile_path,MAX_PATH,L"%ls%ls",ap_path,L"\\Mozilla\\Firefox\\profiles.ini");
	}
	if ( PathFileExistsW(profile_path) )
	{
		if (pname)
		{
			ret = WritePrivateProfileStringW(L"Profile0",L"Path",L"../../",profile_path);
		}
		else
		{
			ret = WritePrivateProfileStringW(L"Profile0",L"Path",L"../../../",profile_path);
		}
	}
	else
	{
		LPWSTR szDir;
		if ( (szDir = (LPWSTR)SYS_MALLOC( sizeof(profile_path) ) ) != NULL )
		{
			wcsncpy (szDir, profile_path, MAX_PATH);
			PathRemoveFileSpecW( szDir );
			SHCreateDirectoryExW(NULL,szDir,NULL);
			SYS_FREE(szDir);
			WritePrivateProfileSectionW(L"General",L"StartWithLastProfile=1\r\n\0",profile_path);
			if (pname)
			{
				ret = WritePrivateProfileSectionW(L"Profile0",L"Name=default\r\nIsRelative=1\r\nPath=../../\r\nDefault=1\r\n\0" \
												,profile_path);
			}
			else
			{
				ret = WritePrivateProfileSectionW(L"Profile0",L"Name=default\r\nIsRelative=1\r\nPath=../../../\r\nDefault=1\r\n\0" \
												,profile_path);
			}
		}
	}
	return ret;
}