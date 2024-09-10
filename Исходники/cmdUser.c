static
BOOL
ParseDate(
    PWSTR s,
    PULONG pSeconds)
{
    SYSTEMTIME SystemTime = {0};
    FILETIME LocalFileTime, FileTime;
    LARGE_INTEGER Time;
    INT nDateFormat = 0;
    PWSTR p = s;

    if (!*s)
        return FALSE;

    GetLocaleInfoW(LOCALE_USER_DEFAULT,
                   LOCALE_IDATE,
                   (PWSTR)&nDateFormat,
                   sizeof(INT));

    switch (nDateFormat)
    {
        case 0: /* mmddyy */
        default:
            if (!ReadNumber(&p, &SystemTime.wMonth))
                return FALSE;
            if (!ReadSeparator(&p))
                return FALSE;
            if (!ReadNumber(&p, &SystemTime.wDay))
                return FALSE;
            if (!ReadSeparator(&p))
                return FALSE;
            if (!ReadNumber(&p, &SystemTime.wYear))
                return FALSE;
            break;

        case 1: /* ddmmyy */
            if (!ReadNumber(&p, &SystemTime.wDay))
                return FALSE;
            if (!ReadSeparator(&p))
                return FALSE;
            if (!ReadNumber(&p, &SystemTime.wMonth))
                return FALSE;
            if (!ReadSeparator(&p))
                return FALSE;
            if (!ReadNumber(&p, &SystemTime.wYear))
                return FALSE;
            break;

        case 2: /* yymmdd */
            if (!ReadNumber(&p, &SystemTime.wYear))
                return FALSE;
            if (!ReadSeparator(&p))
                return FALSE;
            if (!ReadNumber(&p, &SystemTime.wMonth))
                return FALSE;
            if (!ReadSeparator(&p))
                return FALSE;
            if (!ReadNumber(&p, &SystemTime.wDay))
                return FALSE;
            break;
    }

    /* if only entered two digits: */
    /*   assume 2000's if value less than 80 */
    /*   assume 1900's if value greater or equal 80 */
    if (SystemTime.wYear <= 99)
    {
        if (SystemTime.wYear >= 80)
            SystemTime.wYear += 1900;
        else
            SystemTime.wYear += 2000;
    }

    if (!SystemTimeToFileTime(&SystemTime, &LocalFileTime))
        return FALSE;

    if (!LocalFileTimeToFileTime(&LocalFileTime, &FileTime))
        return FALSE;

    Time.u.LowPart = FileTime.dwLowDateTime;
    Time.u.HighPart = FileTime.dwHighDateTime;

    if (!RtlTimeToSecondsSince1970(&Time, pSeconds))
        return FALSE;

    return TRUE;
}