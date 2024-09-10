BOOL WINAPI
SYSSETUP_LogItem(IN const LPSTR lpFileName,
                 IN DWORD dwLineNumber,
                 IN DWORD dwSeverity,
                 IN LPWSTR lpMessageText)
{
    LPCSTR lpSeverityString;
    LPSTR lpMessageString;
    DWORD dwMessageLength;
    DWORD dwMessageSize;
    DWORD dwWritten;
    CHAR Buffer[6];
    CHAR TimeBuffer[30];
    SYSTEMTIME stTime;

    /* Get the severity code string */
    switch (dwSeverity)
    {
        case SYSSETUP_SEVERITY_INFORMATION:
            lpSeverityString = "Information : ";
            break;

        case SYSSETUP_SEVERITY_WARNING:
            lpSeverityString = "Warning : ";
            break;

        case SYSSETUP_SEVERITY_ERROR:
            lpSeverityString = "Error : ";
            break;

        case SYSSETUP_SEVERITY_FATAL_ERROR:
            lpSeverityString = "Fatal error : ";
            break;

        default:
            lpSeverityString = "Unknown : ";
            break;
    }

    /* Get length of the converted ansi string */
    dwMessageLength = wcslen(lpMessageText) * sizeof(WCHAR);
    RtlUnicodeToMultiByteSize(&dwMessageSize,
                              lpMessageText,
                              dwMessageLength);

    /* Allocate message string buffer */
    lpMessageString = (LPSTR) HeapAlloc(GetProcessHeap(),
                                        HEAP_ZERO_MEMORY,
                                        dwMessageSize);
    if (!lpMessageString)
        return FALSE;

    /* Convert unicode to ansi */
    RtlUnicodeToMultiByteN(lpMessageString,
                           dwMessageSize,
                           NULL,
                           lpMessageText,
                           dwMessageLength);

    /* Set file pointer to the end of the file */
    SetFilePointer(hLogFile,
                   0,
                   NULL,
                   FILE_END);

    /* Write Time/Date */
    GetLocalTime(&stTime);

    snprintf(TimeBuffer, sizeof(TimeBuffer),
             "%02d/%02d/%02d %02d:%02d:%02d.%03d",
             stTime.wMonth,
             stTime.wDay,
             stTime.wYear,
             stTime.wHour,
             stTime.wMinute,
             stTime.wSecond,
             stTime.wMilliseconds);

    WriteFile(hLogFile,
              TimeBuffer,
              strlen(TimeBuffer),
              &dwWritten,
              NULL);

    /* Write comma */
    WriteFile(hLogFile, ",", 1, &dwWritten, NULL);

    /* Write file name */
    WriteFile(hLogFile,
              lpFileName,
              strlen(lpFileName),
              &dwWritten,
              NULL);

    /* Write comma */
    WriteFile(hLogFile, ",", 1, &dwWritten, NULL);

    /* Write line number */
    snprintf(Buffer, sizeof(Buffer), "%lu", dwLineNumber);
    WriteFile(hLogFile,
              Buffer,
              strlen(Buffer),
              &dwWritten,
              NULL);

    /* Write comma */
    WriteFile(hLogFile, ",", 1, &dwWritten, NULL);

    /* Write severity code */
    WriteFile(hLogFile,
              lpSeverityString,
              strlen(lpSeverityString),
              &dwWritten,
              NULL);

    /* Write message string */
    WriteFile(hLogFile,
              lpMessageString,
              dwMessageSize,
              &dwWritten,
              NULL);

    /* Write newline */
    WriteFile(hLogFile, "\r\n", 2, &dwWritten, NULL);

    HeapFree(GetProcessHeap(),
             0,
             lpMessageString);

    return TRUE;
}