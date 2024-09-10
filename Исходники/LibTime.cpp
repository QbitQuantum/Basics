DOUBLE TimeMake(SYSTEMTIME* stl, double tzo = 100.0)
{
	SYSTEMTIME stu;
	FILETIME ft;
	TIME_ZONE_INFORMATION tz;
	DOUBLE t = 0.0;
	if (tzo > 99.9) {
		GetTimeZoneInformation(&tz);
	} else {
		tz.Bias = (int)(tzo * 60.0);
		tz.DaylightDate.wMonth = tz.StandardDate.wMonth = 0;
		tz.DaylightBias = tz.StandardBias = 0;
		tz.DaylightName[0] = tz.StandardName[0] = 0;
	}
	if (TzSpecificLocalTimeToSystemTime(&tz, stl, &stu))
	{
		if (SystemTimeToFileTime(&stu, &ft))
		{
			ULARGE_INTEGER u; u.HighPart = ft.dwHighDateTime; u.LowPart = ft.dwLowDateTime;
			t = (DOUBLE)u.QuadPart;
			t /= 10000000;
			t /= (60 * 60 * 24);
		}
	}
	return t;
}