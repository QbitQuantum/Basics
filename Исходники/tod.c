NTSTATUS
timesvc_RemoteTimeOfDay(
    OUT LPTIME_OF_DAY_INFO  *lpTimeOfDayInfo
    )

/*++

Routine Description:

    This routine calls the Win32 and NT base timer APIs to get the
    relevant time/date information. It also calls the Rtl routine to
    convert the time elapsed since 1-1-1970.

    The routine allocates a buffer to contain the time of day information
    and returns a pointer to that buffer to the caller.

Arguments:

    lpTimeOfDayInfo        - Location of where to place pointer to buffer.

Return Value:

    NTSTATUS - STATUS_SUCCESS or reason for failure.

--*/

{
    SYSTEMTIME SystemTime;
    LARGE_INTEGER Time;
    DWORD TickCount;
    LPTIME_OF_DAY_INFO        lpTimeOfDay;
    LONG LocalTimeZoneOffsetSecs;  // offset (+ for West of GMT, etc).

    if (lpTimeOfDayInfo == NULL) {
        return (STATUS_INVALID_PARAMETER);
    }

    //
    // Call the appropriate routines to collect the time information
    //

    GetSystemTime(&SystemTime);

    //
    // Get number of seconds from UTC.  Positive values for west of Greenwich,
    // negative values for east of Greenwich.
    //
    LocalTimeZoneOffsetSecs = NetpLocalTimeZoneOffset();

    //
    // Allocate a TimeOfDay_INFO structure that is to be returned to the
    // caller and fill it with the relevant data.
    //

    *lpTimeOfDayInfo = (TIME_OF_DAY_INFO *) MIDL_user_allocate(
                            sizeof (struct _TIME_OF_DAY_INFO)
                            );

    if (*lpTimeOfDayInfo == NULL) {
        SS_PRINT((
                "SRVSVC: timesvc_RemoteTimeOfDay"
                "got NULL from MIDL_user_allocate!\n" ));
        return(STATUS_NO_MEMORY);
    }

    lpTimeOfDay = (LPTIME_OF_DAY_INFO)(*lpTimeOfDayInfo);

    lpTimeOfDay->tod_hours         = SystemTime.wHour;
    lpTimeOfDay->tod_mins         = SystemTime.wMinute;
    lpTimeOfDay->tod_secs         = SystemTime.wSecond;
    lpTimeOfDay->tod_hunds         = SystemTime.wMilliseconds/10;
    lpTimeOfDay->tod_tinterval = TOD_DEFAULT_INTERVAL;
    lpTimeOfDay->tod_day         = SystemTime.wDay;
    lpTimeOfDay->tod_month         = SystemTime.wMonth;
    lpTimeOfDay->tod_year         = SystemTime.wYear;
    lpTimeOfDay->tod_weekday         = SystemTime.wDayOfWeek;

    // tod_timezone is + for west of GMT, - for east of it.
    // tod_timezone is in minutes.
    lpTimeOfDay->tod_timezone    = LocalTimeZoneOffsetSecs / 60;

    // Get the 64-bit system time.
    // Convert the system time to the number of miliseconds
    // since 1-1-1970.
    //

    NtQuerySystemTime(&Time);
    RtlTimeToSecondsSince1970(&Time,
                              &(lpTimeOfDay->tod_elapsedt)
                             );

    // Get the free running counter value
    //
    TickCount = GetTickCount();
    lpTimeOfDay->tod_msecs = TickCount;

    return(STATUS_SUCCESS);

} // timesvc_RemoteTimeOfDay