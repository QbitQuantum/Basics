/*
 * pcf_poll - called by the transmit procedure
 */
static void
pcf_poll(
	int unit,
	struct peer *peer
	)
{
	struct refclockproc *pp;
	char buf[LENPCF];
	struct tm tm, *tp;
	time_t t;
	
	pp = peer->procptr;

	buf[0] = 0;
	if (read(pp->io.fd, buf, sizeof(buf)) < (ssize_t)sizeof(buf) || buf[0] != 9) {
		refclock_report(peer, CEVNT_FAULT);
		return;
	}

	ZERO(tm);

	tm.tm_mday = buf[11] * 10 + buf[10];
	tm.tm_mon = buf[13] * 10 + buf[12] - 1;
	tm.tm_year = buf[15] * 10 + buf[14];
	tm.tm_hour = buf[7] * 10 + buf[6];
	tm.tm_min = buf[5] * 10 + buf[4];
	tm.tm_sec = buf[3] * 10 + buf[2];
	tm.tm_isdst = (buf[8] & 1) ? 1 : (buf[8] & 2) ? 0 : -1;

	/*
	 * Y2K convert the 2-digit year
	 */
	if (tm.tm_year < 99)
		tm.tm_year += 100;
	
	t = mktime(&tm);
	if (t == (time_t) -1) {
		refclock_report(peer, CEVNT_BADTIME);
		return;
	}

#if defined(__GLIBC__) && defined(_BSD_SOURCE)
	if ((tm.tm_isdst > 0 && tm.tm_gmtoff != 7200)
	    || (tm.tm_isdst == 0 && tm.tm_gmtoff != 3600)
	    || tm.tm_isdst < 0) {
#ifdef DEBUG
		if (debug)
			printf ("local time zone not set to CET/CEST\n");
#endif
		refclock_report(peer, CEVNT_BADTIME);
		return;
	}
#endif

	pp->lencode = strftime(pp->a_lastcode, BMAX, "%Y %m %d %H %M %S", &tm);

#if defined(_REENTRANT) || defined(_THREAD_SAFE)
	tp = gmtime_r(&t, &tm);
#else
	tp = gmtime(&t);
#endif
	if (!tp) {
		refclock_report(peer, CEVNT_FAULT);
		return;
	}

	get_systime(&pp->lastrec);
	pp->polls++;
	pp->year = tp->tm_year + 1900;
	pp->day = tp->tm_yday + 1;
	pp->hour = tp->tm_hour;
	pp->minute = tp->tm_min;
	pp->second = tp->tm_sec;
	pp->nsec = buf[16] * 31250000;
	if (buf[17] & 1)
		pp->nsec += 500000000;

#ifdef DEBUG
	if (debug)
		printf ("pcf%d: time is %04d/%02d/%02d %02d:%02d:%02d UTC\n",
			unit, pp->year, tp->tm_mon + 1, tp->tm_mday, pp->hour,
			pp->minute, pp->second);
#endif

	if (!refclock_process(pp)) {
		refclock_report(peer, CEVNT_BADTIME);
		return;
	}
	record_clock_stats(&peer->srcadr, pp->a_lastcode);
	if ((buf[1] & 1) && !(pp->sloppyclockflag & CLK_FLAG2))
		pp->leap = LEAP_NOTINSYNC;
	else
		pp->leap = LEAP_NOWARNING;
	pp->lastref = pp->lastrec;
	refclock_receive(peer);
}