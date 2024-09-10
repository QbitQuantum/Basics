__time64_t CLogCacheStatistics::GetTime (FILETIME& fileTime)
{
    SYSTEMTIME systemTime = { 0 };
    FileTimeToSystemTime (&fileTime, &systemTime);

    tm time = {0,0,0, 0,0,0, 0,0,0};
    time.tm_year = systemTime.wYear - 1900;
    time.tm_mon = systemTime.wMonth - 1;
    time.tm_mday = systemTime.wDay;
    time.tm_hour = systemTime.wHour;
    time.tm_min = systemTime.wMinute;
    time.tm_sec = systemTime.wSecond;

    return _mkgmtime64 (&time)*1000000 + systemTime.wMilliseconds * 1000;
}