qtimestamp getTimestamp()
{
#ifdef Q_OS_WINCE
    // This implementation is based on code found here:
    // http://social.msdn.microsoft.com/Forums/en/vssmartdevicesnative/thread/74870c6c-76c5-454c-8533-812cfca585f8
    HANDLE currentThread = GetCurrentThread();
    FILETIME creationTime, exitTime, kernalTime, userTime;
    GetThreadTimes(currentThread, &creationTime, &exitTime, &kernalTime, &userTime);

    ULARGE_INTEGER uli;
    uli.LowPart = userTime.dwLowDateTime;
    uli.HighPart = userTime.dwHighDateTime;
    ULONGLONG systemTimeInMS = uli.QuadPart/10000;
    return static_cast<qtimestamp>(systemTimeInMS);
#else
    return clock();
#endif
}