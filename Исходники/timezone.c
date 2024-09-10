/*
 * @implemented
 */
DWORD
WINAPI
GetTimeZoneInformation(LPTIME_ZONE_INFORMATION lpTimeZoneInformation)
{
    RTL_TIME_ZONE_INFORMATION TimeZoneInformation;
    NTSTATUS Status;

    DPRINT("GetTimeZoneInformation()\n");

    Status = NtQuerySystemInformation(SystemCurrentTimeZoneInformation,
                                      &TimeZoneInformation,
                                      sizeof(RTL_TIME_ZONE_INFORMATION),
                                      NULL);
    if (!NT_SUCCESS(Status))
    {
        BaseSetLastNTError(Status);
        return TIME_ZONE_ID_INVALID;
    }

    lpTimeZoneInformation->Bias = TimeZoneInformation.Bias;

    wcsncpy(lpTimeZoneInformation->StandardName,
            TimeZoneInformation.StandardName,
            ARRAYSIZE(lpTimeZoneInformation->StandardName));
    lpTimeZoneInformation->StandardDate.wYear = TimeZoneInformation.StandardDate.Year;
    lpTimeZoneInformation->StandardDate.wMonth = TimeZoneInformation.StandardDate.Month;
    lpTimeZoneInformation->StandardDate.wDay = TimeZoneInformation.StandardDate.Day;
    lpTimeZoneInformation->StandardDate.wHour = TimeZoneInformation.StandardDate.Hour;
    lpTimeZoneInformation->StandardDate.wMinute = TimeZoneInformation.StandardDate.Minute;
    lpTimeZoneInformation->StandardDate.wSecond = TimeZoneInformation.StandardDate.Second;
    lpTimeZoneInformation->StandardDate.wMilliseconds = TimeZoneInformation.StandardDate.Milliseconds;
    lpTimeZoneInformation->StandardDate.wDayOfWeek = TimeZoneInformation.StandardDate.Weekday;
    lpTimeZoneInformation->StandardBias = TimeZoneInformation.StandardBias;

    wcsncpy(lpTimeZoneInformation->DaylightName,
            TimeZoneInformation.DaylightName,
            ARRAYSIZE(lpTimeZoneInformation->DaylightName));
    lpTimeZoneInformation->DaylightDate.wYear = TimeZoneInformation.DaylightDate.Year;
    lpTimeZoneInformation->DaylightDate.wMonth = TimeZoneInformation.DaylightDate.Month;
    lpTimeZoneInformation->DaylightDate.wDay = TimeZoneInformation.DaylightDate.Day;
    lpTimeZoneInformation->DaylightDate.wHour = TimeZoneInformation.DaylightDate.Hour;
    lpTimeZoneInformation->DaylightDate.wMinute = TimeZoneInformation.DaylightDate.Minute;
    lpTimeZoneInformation->DaylightDate.wSecond = TimeZoneInformation.DaylightDate.Second;
    lpTimeZoneInformation->DaylightDate.wMilliseconds = TimeZoneInformation.DaylightDate.Milliseconds;
    lpTimeZoneInformation->DaylightDate.wDayOfWeek = TimeZoneInformation.DaylightDate.Weekday;
    lpTimeZoneInformation->DaylightBias = TimeZoneInformation.DaylightBias;

    return TIME_ZoneID(lpTimeZoneInformation);
}