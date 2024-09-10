/* Function 28 */
NET_API_STATUS
__stdcall
NetrRemoteTOD(
    SRVSVC_HANDLE ServerName,
    LPTIME_OF_DAY_INFO *BufferPtr)
{
    SYSTEMTIME SystemTime;
    LARGE_INTEGER Time;
    TIME_ZONE_INFORMATION TimeZoneInfo;
    DWORD TimeZoneId;
    LPTIME_OF_DAY_INFO lpTod;

    TRACE("NetrRemoteTOD(%p %p)\n", ServerName, BufferPtr);

    *BufferPtr = midl_user_allocate(sizeof(TIME_OF_DAY_INFO));
    if (*BufferPtr == NULL)
        return ERROR_NOT_ENOUGH_MEMORY;

    lpTod = *BufferPtr;

    /* Set the seconds since 1970 */
    NtQuerySystemTime(&Time);
    RtlTimeToSecondsSince1970(&Time,
                              &lpTod->tod_elapsedt);

    /* Set the tick count */
    lpTod->tod_msecs = GetTickCount();

    /* Set the timezone */
    TimeZoneId = GetTimeZoneInformation(&TimeZoneInfo);

    switch (TimeZoneId)
    {
        case TIME_ZONE_ID_UNKNOWN:
            lpTod->tod_timezone = TimeZoneInfo.Bias;
            break;

        case TIME_ZONE_ID_STANDARD:
            lpTod->tod_timezone = TimeZoneInfo.Bias + TimeZoneInfo.StandardBias;
            break;

        case TIME_ZONE_ID_DAYLIGHT:
            lpTod->tod_timezone = TimeZoneInfo.Bias + TimeZoneInfo.DaylightBias;
            break;

        default:
            lpTod->tod_timezone = 0;
    }

    /* Set the ??? */
    lpTod->tod_tinterval = 310;

    /* Set the date and time */
    GetSystemTime(&SystemTime);
    lpTod->tod_hours = SystemTime.wHour;
    lpTod->tod_mins = SystemTime.wMinute;
    lpTod->tod_secs = SystemTime.wSecond;
    lpTod->tod_hunds = SystemTime.wMilliseconds / 10;
    lpTod->tod_day = SystemTime.wDay;
    lpTod->tod_month = SystemTime.wMonth;
    lpTod->tod_year = SystemTime.wYear;
    lpTod->tod_weekday = SystemTime.wDayOfWeek;

    return NERR_Success;
}