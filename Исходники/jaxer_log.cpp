void CJaxerLog::Log(eLogLevel eLevel, char* pszFormat, ...)
{
    if (eLevel < m_eDefault)
        return;

    if (!m_fp)
        return;

    char szBuffer[0x4000];
    char szTimeBuf[0x64];

    va_list arg_ptr;
    va_start(arg_ptr, pszFormat);
    vsprintf(szBuffer, pszFormat, arg_ptr);
    va_end(arg_ptr);

    time_t rawtime;
	struct tm * timeinfo;

	time ( &rawtime );
	timeinfo = localtime ( &rawtime );

    sprintf(szTimeBuf,
        "%02d:%02d:%02d %02d/%02d/%04d [%s] ",
        timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec,
        timeinfo->tm_mon+1, timeinfo->tm_mday, timeinfo->tm_year+1900,
        sLogLevel[eLevel]);

    
    OVERLAPPED ovlp;
    memset(&ovlp, 0, sizeof(ovlp));
    LockFileEx(m_fp, LOCKFILE_EXCLUSIVE_LOCK, 0, 1, 0, &ovlp);
    DWORD nBytes;
    SetFilePointer(m_fp, 0, 0, FILE_END);
    WriteFile(m_fp, szTimeBuf, (DWORD)strlen(szTimeBuf), &nBytes, NULL);
    WriteFile(m_fp, szBuffer, (DWORD)strlen(szBuffer), &nBytes, NULL);
    WriteFile(m_fp, "\r\n", 2, &nBytes, NULL);
    UnlockFileEx(m_fp, 0, 1, 0, &ovlp);
}