/*****************************************************************************
DWORD WriteSfvHeader(CONST HANDLE hFile)
hFile		: (IN) handle to an open file

Return Value:
- returns NOERROR or GetLastError()
*****************************************************************************/
DWORD WriteFileComment(CONST HANDLE hFile, CONST FILEINFO *pFileInfo, UINT startChar)
{
    TCHAR szLine[MAX_LINE_LENGTH];
#ifdef UNICODE
    CHAR szLineAnsi[MAX_LINE_LENGTH];
#endif
    DWORD dwNumberOfBytesWritten;
    size_t stStringLength;
    VOID *szOutLine=szLine;

    SYSTEMTIME st;
    FILETIME ft;
    TCHAR szTimeStamp[50];

    FileTimeToLocalFileTime( &pFileInfo->ftModificationTime, &ft );
    FileTimeToSystemTime( &ft, &st );
    int chars = GetTimeFormat( LOCALE_USER_DEFAULT, 0, &st, TEXT("HH':'mm'.'ss"), szTimeStamp, 50 );
    GetDateFormat( LOCALE_USER_DEFAULT, 0, &st, TEXT("' 'yyyy'-'MM'-'dd"), szTimeStamp + chars - 1, 50 - chars );
    StringCbPrintf(szLine, MAX_LINE_LENGTH, TEXT(";%13I64d  %s %s%s"), pFileInfo->qwFilesize, szTimeStamp, pFileInfo->szFilename.GetString() + startChar,
                   g_program_options.bCreateUnixStyle ? TEXT("\n") : TEXT("\r\n"));
    StringCbLength(szLine, MAX_LINE_LENGTH, & stStringLength);


#ifdef UNICODE
    if(!g_program_options.bCreateUnicodeFiles) {
        if(!WideCharToMultiByte(CP_ACP, 0, szLine, -1, szLineAnsi, MAX_UTF8_PATH, NULL, NULL) )
            return GetLastError();
        StringCbLengthA(szLineAnsi, MAX_LINE_LENGTH, & stStringLength);
        szOutLine=szLineAnsi;
    } else if(g_program_options.iUnicodeSaveType == UTF_8 || g_program_options.iUnicodeSaveType==UTF_8_BOM) {
        if(!WideCharToMultiByte(CP_UTF8, 0, szLine, -1, szLineAnsi, MAX_UTF8_PATH, NULL, NULL) )
            return GetLastError();
        StringCbLengthA(szLineAnsi, MAX_LINE_LENGTH, & stStringLength);
        szOutLine=szLineAnsi;
    }
#endif

    if(!WriteFile(hFile, szOutLine, (DWORD)stStringLength, & dwNumberOfBytesWritten, NULL) )
        return GetLastError();

    return NOERROR;
}