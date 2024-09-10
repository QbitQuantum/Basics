static const char* dated_local_format(
    const log4c_layout_t*  	a_layout,
    const log4c_logging_event_t*a_event)
{
    static char buffer[1024];

#ifdef LOG4C_POSIX_TIMESTAMP
    struct tm tm;
    time_t t;

    t = a_event->evt_timestamp.tv_sec;
    localtime_r(&t, &tm);
    snprintf(buffer, sizeof(buffer), "%04d%02d%02d %02d:%02d:%02d.%03ld %-8s %s- %s\n",
             tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday,
             tm.tm_hour, tm.tm_min, tm.tm_sec,
             a_event->evt_timestamp.tv_usec / 1000,
             log4c_priority_to_string(a_event->evt_priority),
             a_event->evt_category, a_event->evt_msg);
#else
    SYSTEMTIME stime, ltime;

    if (FileTimeToSystemTime(&a_event->evt_timestamp, &stime) &&
        SystemTimeToTzSpecificLocalTime(NULL, &stime, &ltime)) {
        snprintf(buffer, sizeof(buffer), "%04d%02d%02d %02d:%02d:%02d.%03ld %-8s %s- %s\n",
                 ltime.wYear, ltime.wMonth , ltime.wDay,
                 ltime.wHour, ltime.wMinute, ltime.wSecond,
                 ltime.wMilliseconds,
                 log4c_priority_to_string(a_event->evt_priority),
                 a_event->evt_category, a_event->evt_msg);
    }
#endif
    return buffer;
}