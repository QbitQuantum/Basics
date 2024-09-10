/** Converts a GMT timestamp to local datetime struct
	Adjusts to TZ if possible
 **/
int local_datetime(TIMESTAMP ts, DATETIME *dt)
{

	int64 n;
	TIMESTAMP rem = 0;
	TIMESTAMP local;
	int tsyear;

#ifdef USE_TS_CACHE
	/* allow caching */
	static TIMESTAMP old_ts =0;
	static DATETIME old_dt;
#endif

	if( ts == TS_NEVER || ts==TS_ZERO )
		return 0;

	if( dt==NULL || ts<TS_ZERO || ts>TS_MAX ) /* no buffer or timestamp out of range */
	{
		output_error("local_datetime(ts=%lli,...): invalid local_datetime request",ts);
		return 0;
	}
#ifdef USE_TS_CACHE
	/* check cache */
	if (old_ts == ts && old_ts!=0)
		memcpy(dt,&old_dt,sizeof(DATETIME));
	else
		old_ts = 0;
#endif

	local = LOCALTIME(ts);
	tsyear = timestamp_year(local, &rem);

	if (rem < 0)
	{
		// DPC: note that as of 3.0, the clock is initialized by default, so this error can only
		//      occur when an invalid timestamp is being converted to local time.  It should no
		//      longer occur as a result of a missing clock directive.
		//THROW("local_datetime(ts=%lli, ...): invalid timestamp cannot be converted to local time", ts);
		/*	TROUBLESHOOT
			This is the result of an internal core or module coding error which resulted in an
			invalid UTC clock time being converted to local time.
		*/
		output_error("local_datetime(ts=%lli,...): invalid local_datetime request",ts);
		return 0;
	}

	if(ts < TS_ZERO && ts > TS_MAX){ /* timestamp out of range */
		return 0;
	}
	
	if(ts == TS_NEVER){
		return 0;
	}

	/* ts is valid */
	dt->timestamp = ts;

	/* DST? */
	dt->is_dst = (tzvalid && isdst(ts));

	/* compute year */
	dt->year = tsyear;

	/* yearday and weekday */
	dt->yearday = (unsigned short)(rem / DAY);
	dt->weekday = (unsigned short)((local / DAY + DOW0 + 7) % 7);

	/* compute month */
	dt->month = 0;
	n = daysinmonth[0] * DAY;
	while(rem >= n){
		rem -= n; /* subtract n ticks from ts */
		dt->month++; /* add to month */
		if(dt->month == 12){
			dt->month = 0;
			++dt->year;
		}
		n = (daysinmonth[dt->month] + ((dt->month == 1 && ISLEAPYEAR(dt->year)) ? 1:0)) * 86400 * TS_SECOND;
		if(n < 86400 * 28){ /**/
			output_fatal("Breaking an infinite loop in local_datetime! (ts = %"FMT_INT64"ds", ts);
			/*	TROUBLESHOOT
				An internal protection against infinite loops in the time calculation
				module has encountered a critical problem.  This is often caused by
				an incorrectly initialized timezone system, a missing timezone specification before
				a timestamp was used, or a missing timezone localization in your system.
				Correct the timezone problem and try again.
			 */
			return 0;
		}
	}
	dt->month++; /* Jan=1 */

	/* compute day */
	dt->day = (unsigned short)(rem / DAY + 1);
	rem %= DAY;

	/* compute hour */
	dt->hour = (unsigned short)(rem / HOUR);
	rem %= HOUR;

	/* compute minute */
	dt->minute = (unsigned short)(rem / MINUTE);
	rem %= MINUTE;

	/* compute second */
	dt->second = (unsigned short)rem / TS_SECOND;
	rem %= SECOND;

	/* compute nanosecond */
	dt->nanosecond = (unsigned int)(rem * 1e9);

	/* determine timezone */
	strncpy(dt->tz, tzvalid ? (dt->is_dst ? tzdst : tzstd) : "GMT", sizeof(dt->tz));

	/* timezone offset in seconds */
	dt->tzoffset = tzoffset - (isdst(dt->timestamp)?3600:0);

#ifdef USE_TS_CACHE
	/* cache result */
	old_ts = ts;
	memcpy(&old_dt,dt,sizeof(old_dt));
#endif
	return 1;
}