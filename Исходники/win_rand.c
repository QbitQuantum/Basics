static BOOL
EnumSystemFiles(Handler func)
{
    PRUnichar szSysDir[_MAX_PATH];
    static const int folders[] = {
    	CSIDL_BITBUCKET,  
	CSIDL_RECENT,
	CSIDL_INTERNET_CACHE, 
	CSIDL_HISTORY,
	0
    };
    int i = 0;
    if (_MAX_PATH > (i = GetTempPathW(_MAX_PATH, szSysDir))) {
        if (i > 0 && szSysDir[i-1] == L'\\')
	    szSysDir[i-1] = L'\0'; // we need to lop off the trailing slash
        EnumSystemFilesInFolder(func, szSysDir, MAX_DEPTH);
    }
    for(i = 0; folders[i]; i++) {
        DWORD rv = SHGetSpecialFolderPathW(NULL, szSysDir, folders[i], 0);
        if (szSysDir[0])
            EnumSystemFilesInFolder(func, szSysDir, MAX_DEPTH);
        szSysDir[0] =  L'\0';
    }
    return PR_TRUE;
}