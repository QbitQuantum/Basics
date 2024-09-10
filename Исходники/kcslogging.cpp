void CKcsLogging::ClearLogFileByDays(int nDay /* = 7 */)
{
    CHAR szLogFileName[MAX_PATH * 2] = { 0 };
    WIN32_FIND_DATAA fd = { 0 };
    HANDLE hFile = INVALID_HANDLE_VALUE;

    SHGetSpecialFolderPathA(NULL, szLogFileName, CSIDL_LOCAL_APPDATA, FALSE);

    PathAppendA(szLogFileName, "KSafe\\KClear\\Logs");
    PathAppendA(szLogFileName, "*.*");


    hFile = FindFirstFileA(szLogFileName, &fd);
    if (INVALID_HANDLE_VALUE == hFile)
    {
        goto Clear0;
    }

    do 
    {
        if (0 == stricmp(".", fd.cFileName) || 0 == stricmp("..", fd.cFileName))
            continue;

        time_t lNow = 0;
        time(&lNow);  

        FILETIME localfiletime;    
        FileTimeToLocalFileTime(&(fd.ftLastWriteTime), &localfiletime);

        CTime stSys(lNow);
        CTime stFile(localfiletime);
        CTimeSpan stSPan;

        stSPan =  stSys - stFile;

        if (stSPan.GetDays() >= nDay)
        {           
            CStringA strtemp = szLogFileName ;
            CStringA strFileName = strtemp.Left(strtemp.ReverseFind(L'\\') + 1);
            strFileName += fd.cFileName;                 
            if (::PathFileExistsA(strFileName))
            {
                ::DeleteFileA(strFileName);
            }
        }

    } while (FindNextFileA(hFile, &fd));

Clear0:
    if (hFile != INVALID_HANDLE_VALUE)
    {
        FindClose(hFile);
        hFile = INVALID_HANDLE_VALUE;
    }   
}