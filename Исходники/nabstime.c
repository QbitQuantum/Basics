void
abstime2tm(AbsoluteTime _time, int *tzp, struct pg_tm * tm, char **tzn)
{
	pg_time_t	time = (pg_time_t) _time;
	struct pg_tm *tx;

	if (tzp != NULL)
		tx = pg_localtime(&time, session_timezone);
	else
		tx = pg_gmtime(&time);

	if (tx == NULL)
		elog(ERROR, "could not convert abstime to timestamp: %m");

	tm->tm_year = tx->tm_year + 1900;
	tm->tm_mon = tx->tm_mon + 1;
	tm->tm_mday = tx->tm_mday;
	tm->tm_hour = tx->tm_hour;
	tm->tm_min = tx->tm_min;
	tm->tm_sec = tx->tm_sec;
	tm->tm_isdst = tx->tm_isdst;

	tm->tm_gmtoff = tx->tm_gmtoff;
	tm->tm_zone = tx->tm_zone;

	if (tzp != NULL)
	{
		*tzp = -tm->tm_gmtoff;	/* tm_gmtoff is Sun/DEC-ism */

		/*
		 * XXX FreeBSD man pages indicate that this should work - tgl 97/04/23
		 */
		if (tzn != NULL)
		{
			/*
			 * Copy no more than MAXTZLEN bytes of timezone to tzn, in case it
			 * contains an error message, which doesn't fit in the buffer
			 */
			StrNCpy(*tzn, tm->tm_zone, MAXTZLEN + 1);
			if (strlen(tm->tm_zone) > MAXTZLEN)
				ereport(WARNING,
						(errcode(ERRCODE_INVALID_PARAMETER_VALUE),
						 errmsg("invalid time zone name: \"%s\"",
								tm->tm_zone)));
		}
	}
	else
		tm->tm_isdst = -1;
}