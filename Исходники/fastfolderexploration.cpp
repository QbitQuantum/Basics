static inline QDateTime fileTimeToQDateTime(const FILETIME *time)
{
    QDateTime ret;
    SYSTEMTIME sTime, lTime;
    FileTimeToSystemTime(time, &sTime);
    SystemTimeToTzSpecificLocalTime(0, &sTime, &lTime);
    ret.setDate(QDate(lTime.wYear, lTime.wMonth, lTime.wDay));
    ret.setTime(QTime(lTime.wHour, lTime.wMinute, lTime.wSecond, lTime.wMilliseconds));
    return ret;
}