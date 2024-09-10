int getCurrentDateTimeStringWithSeparator(char *dateString, char dateSeparator, char *timeString, char timeSeparator)
{
    static const char *wday[] = { "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };
    time_t t;
    struct tm tmobj;

    time(&t);
    localtime_s(&tmobj, &t);

    if (dateString)
    {
        if (dateSeparator == '\0')
        {
            sprintf_s(dateString, TIMESTRING_BUFFER_SIZE, "%04d%02d%02d",
                (1900 + tmobj.tm_year),
                (1 + tmobj.tm_mon),
                tmobj.tm_mday);
        }
        else {
            sprintf_s(dateString, TIMESTRING_BUFFER_SIZE, "%04d%c%02d%c%02d",
                (1900 + tmobj.tm_year), dateSeparator,
                (1 + tmobj.tm_mon), dateSeparator,
                tmobj.tm_mday);
        }
    }

    if (timeString)
    {
        if (timeSeparator == '\0')
        {
            sprintf_s(timeString, TIMESTRING_BUFFER_SIZE, "%02d%02d%02d",
                tmobj.tm_hour,
                tmobj.tm_min,
                tmobj.tm_sec);
        }
        else {
            sprintf_s(timeString, TIMESTRING_BUFFER_SIZE, "%02d%c%02d%c%02d",
                tmobj.tm_hour, timeSeparator,
                tmobj.tm_min, timeSeparator,
                tmobj.tm_sec);
        }
    }

    return 1;
}