static PHYSFS_sint64 FileTimeToPhysfsTime(const FILETIME *ft)
{
	SYSTEMTIME st_utc;
	SYSTEMTIME st_localtz;
	TIME_ZONE_INFORMATION tzi;
	DWORD tzid;
	PHYSFS_sint64 retval;
	struct tm tm;
	BOOL rc;

	BAIL_IF_MACRO(!FileTimeToSystemTime(ft, &st_utc), errcodeFromWinApi(), -1);
	tzid = GetTimeZoneInformation(&tzi);
	BAIL_IF_MACRO(tzid == TIME_ZONE_ID_INVALID, errcodeFromWinApi(), -1);
	rc = SystemTimeToTzSpecificLocalTime(&tzi, &st_utc, &st_localtz);
	BAIL_IF_MACRO(!rc, errcodeFromWinApi(), -1);

	/* Convert to a format that mktime() can grok... */
	tm.tm_sec = st_localtz.wSecond;
	tm.tm_min = st_localtz.wMinute;
	tm.tm_hour = st_localtz.wHour;
	tm.tm_mday = st_localtz.wDay;
	tm.tm_mon = st_localtz.wMonth - 1;
	tm.tm_year = st_localtz.wYear - 1900;
	tm.tm_wday = -1 /*st_localtz.wDayOfWeek*/;
	tm.tm_yday = -1;
	tm.tm_isdst = -1;

	/* Convert to a format PhysicsFS can grok... */
	retval = (PHYSFS_sint64)mktime(&tm);
	BAIL_IF_MACRO(retval == -1, PHYSFS_ERR_OS_ERROR, -1);
	return retval;
} /* FileTimeToPhysfsTime */