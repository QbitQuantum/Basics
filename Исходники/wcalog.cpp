/********************************************************************
 WcaLog() - outputs trace and log info

*******************************************************************/
extern "C" void __cdecl WcaLog(
    __in LOGLEVEL llv,
    __in_z __format_string PCSTR fmt, 
    ...
    )
{
    static char szFmt[LOG_BUFFER];
    static char szBuf[LOG_BUFFER];
    static bool fInLogPrint = false;

    // prevent re-entrant logprints.  (recursion issues between assert/logging code)
    if (fInLogPrint)
        return;
    fInLogPrint = true;

    if (LOGMSG_STANDARD == llv || 
        (LOGMSG_VERBOSE == llv && IsVerboseLoggingLite())
#ifdef DEBUG
        || LOGMSG_TRACEONLY == llv
#endif
        )
    {
        va_list args;
        va_start(args, fmt);

        LPCSTR szLogName = WcaGetLogName();
        if (szLogName[0] != 0)
            StringCchPrintfA(szFmt, countof(szFmt), "%s:  %s", szLogName, fmt);
        else
            StringCchCopyA(szFmt, countof(szFmt), fmt);

        StringCchVPrintfA(szBuf, countof(szBuf), szFmt, args);
        va_end(args);

#ifdef DEBUG
        // always write to the log in debug
#else
        if (llv == LOGMSG_STANDARD || (llv == LOGMSG_VERBOSE && IsVerboseLoggingLite()))
#endif
        {
            PMSIHANDLE hrec = MsiCreateRecord(1);

            ::MsiRecordSetStringA(hrec, 0, szBuf);
            // TODO:  Recursion on failure.  May not be safe to assert from here.
            WcaProcessMessage(INSTALLMESSAGE_INFO, hrec);
        }

#if DEBUG
        StringCchCatA(szBuf, countof(szBuf), "\n");
        OutputDebugStringA(szBuf);
#endif
    }

    fInLogPrint = false;
    return;
}