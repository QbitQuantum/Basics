/*
 * hpgps_receive - receive data from the serial interface
 */
static void
hpgps_receive(
	struct recvbuf *rbufp
	)
{
	register struct hpgpsunit *up;
	struct refclockproc *pp;
	struct peer *peer;
	l_fp trtmp;
	char tcodechar1;        /* identifies timecode format */
	char tcodechar2;        /* identifies timecode format */
	char timequal;          /* time figure of merit: 0-9 */
	char freqqual;          /* frequency figure of merit: 0-3 */
	char leapchar;          /* leapsecond: + or 0 or - */
	char servchar;          /* request for service: 0 = no, 1 = yes */
	char syncchar;          /* time info is invalid: 0 = no, 1 = yes */
	short expectedsm;       /* expected timecode byte checksum */
	short tcodechksm;       /* computed timecode byte checksum */
	int i,m,n;
	int month, day, lastday;
	char *tcp;              /* timecode pointer (skips over the prompt) */
	char prompt[BMAX];      /* prompt in response from receiver */

	/*
	 * Initialize pointers and read the receiver response
	 */
	peer = rbufp->recv_peer;
	pp = peer->procptr;
	up = pp->unitptr;
	*pp->a_lastcode = '\0';
	pp->lencode = refclock_gtlin(rbufp, pp->a_lastcode, BMAX, &trtmp);

#ifdef DEBUG
	if (debug)
	    printf("hpgps: lencode: %d timecode:%s\n",
		   pp->lencode, pp->a_lastcode);
#endif

	/*
	 * If there's no characters in the reply, we can quit now
	 */
	if (pp->lencode == 0)
	    return;

	/*
	 * If linecnt is greater than zero, we are getting information only,
	 * such as the receiver identification string or the receiver status
	 * screen, so put the receiver response at the end of the status
	 * screen buffer. When we have the last line, write the buffer to
	 * the clockstats file and return without further processing.
	 *
	 * If linecnt is zero, we are expecting either the timezone
	 * or a timecode. At this point, also write the response
	 * to the clockstats file, and go on to process the prompt (if any),
	 * timezone, or timecode and timestamp.
	 */


	if (up->linecnt-- > 0) {
		if ((int)(pp->lencode + 2) <= (SMAX - (up->lastptr - up->statscrn))) {
			*up->lastptr++ = '\n';
			memcpy(up->lastptr, pp->a_lastcode, pp->lencode);
			up->lastptr += pp->lencode;
		}
		if (up->linecnt == 0) 
		    record_clock_stats(&peer->srcadr, up->statscrn);
               
		return;
	}

	record_clock_stats(&peer->srcadr, pp->a_lastcode);
	pp->lastrec = trtmp;
            
	up->lastptr = up->statscrn;
	*up->lastptr = '\0';
	up->pollcnt = 2;

	/*
	 * We get down to business: get a prompt if one is there, issue
	 * a clear status command if it contains an error indication.
	 * Next, check for either the timezone reply or the timecode reply
	 * and decode it.  If we don't recognize the reply, or don't get the
	 * proper number of decoded fields, or get an out of range timezone,
	 * or if the timecode checksum is bad, then we declare bad format
	 * and exit.
	 *
	 * Timezone format (including nominal prompt):
	 * scpi > -H,-M<cr><lf>
	 *
	 * Timecode format (including nominal prompt):
	 * scpi > T2yyyymmddhhmmssMFLRVcc<cr><lf>
	 *
	 */

	strlcpy(prompt, pp->a_lastcode, sizeof(prompt));
	tcp = strrchr(pp->a_lastcode,'>');
	if (tcp == NULL)
	    tcp = pp->a_lastcode; 
	else
	    tcp++;
	prompt[tcp - pp->a_lastcode] = '\0';
	while ((*tcp == ' ') || (*tcp == '\t')) tcp++;

	/*
	 * deal with an error indication in the prompt here
	 */
	if (strrchr(prompt,'E') > strrchr(prompt,'s')){
#ifdef DEBUG
		if (debug)
		    printf("hpgps: error indicated in prompt: %s\n", prompt);
#endif
		if (write(pp->io.fd, "*CLS\r\r", 6) != 6)
		    refclock_report(peer, CEVNT_FAULT);
	}

	/*
	 * make sure we got a timezone or timecode format and 
	 * then process accordingly
	 */
	m = sscanf(tcp,"%c%c", &tcodechar1, &tcodechar2);

	if (m != 2){
#ifdef DEBUG
		if (debug)
		    printf("hpgps: no format indicator\n");
#endif
		refclock_report(peer, CEVNT_BADREPLY);
		return;
	}

	switch (tcodechar1) {

	    case '+':
	    case '-':
		m = sscanf(tcp,"%d,%d", &up->tzhour, &up->tzminute);
		if (m != MTZONE) {
#ifdef DEBUG
			if (debug)
			    printf("hpgps: only %d fields recognized in timezone\n", m);
#endif
			refclock_report(peer, CEVNT_BADREPLY);
			return;
		}
		if ((up->tzhour < -12) || (up->tzhour > 13) || 
		    (up->tzminute < -59) || (up->tzminute > 59)){
#ifdef DEBUG
			if (debug)
			    printf("hpgps: timezone %d, %d out of range\n",
				   up->tzhour, up->tzminute);
#endif
			refclock_report(peer, CEVNT_BADREPLY);
			return;
		}
		return;

	    case 'T':
		break;

	    default:
#ifdef DEBUG
		if (debug)
		    printf("hpgps: unrecognized reply format %c%c\n",
			   tcodechar1, tcodechar2);
#endif
		refclock_report(peer, CEVNT_BADREPLY);
		return;
	} /* end of tcodechar1 switch */


	switch (tcodechar2) {

	    case '2':
		m = sscanf(tcp,"%*c%*c%4d%2d%2d%2d%2d%2d%c%c%c%c%c%2hx",
			   &pp->year, &month, &day, &pp->hour, &pp->minute, &pp->second,
			   &timequal, &freqqual, &leapchar, &servchar, &syncchar,
			   &expectedsm);
		n = NTCODET2;

		if (m != MTCODET2){
#ifdef DEBUG
			if (debug)
			    printf("hpgps: only %d fields recognized in timecode\n", m);
#endif
			refclock_report(peer, CEVNT_BADREPLY);
			return;
		}
		break;

	    default:
#ifdef DEBUG
		if (debug)
		    printf("hpgps: unrecognized timecode format %c%c\n",
			   tcodechar1, tcodechar2);
#endif
		refclock_report(peer, CEVNT_BADREPLY);
		return;
	} /* end of tcodechar2 format switch */
           
	/* 
	 * Compute and verify the checksum.
	 * Characters are summed starting at tcodechar1, ending at just
	 * before the expected checksum.  Bail out if incorrect.
	 */
	tcodechksm = 0;
	while (n-- > 0) tcodechksm += *tcp++;
	tcodechksm &= 0x00ff;

	if (tcodechksm != expectedsm) {
#ifdef DEBUG
		if (debug)
		    printf("hpgps: checksum %2hX doesn't match %2hX expected\n",
			   tcodechksm, expectedsm);
#endif
		refclock_report(peer, CEVNT_BADREPLY);
		return;
	}

	/* 
	 * Compute the day of year from the yyyymmdd format.
	 */
	if (month < 1 || month > 12 || day < 1) {
		refclock_report(peer, CEVNT_BADTIME);
		return;
	}

	if ( ! isleap_4(pp->year) ) {				/* Y2KFixes */
		/* not a leap year */
		if (day > day1tab[month - 1]) {
			refclock_report(peer, CEVNT_BADTIME);
			return;
		}
		for (i = 0; i < month - 1; i++) day += day1tab[i];
		lastday = 365;
	} else {
		/* a leap year */
		if (day > day2tab[month - 1]) {
			refclock_report(peer, CEVNT_BADTIME);
			return;
		}
		for (i = 0; i < month - 1; i++) day += day2tab[i];
		lastday = 366;
	}

	/*
	 * Deal with the timezone offset here. The receiver timecode is in
	 * local time = UTC + :PTIME:TZONE, so SUBTRACT the timezone values.
	 * For example, Pacific Standard Time is -8 hours , 0 minutes.
	 * Deal with the underflows and overflows.
	 */
	pp->minute -= up->tzminute;
	pp->hour -= up->tzhour;

	if (pp->minute < 0) {
		pp->minute += 60;
		pp->hour--;
	}
	if (pp->minute > 59) {
		pp->minute -= 60;
		pp->hour++;
	}
	if (pp->hour < 0)  {
		pp->hour += 24;
		day--;
		if (day < 1) {
			pp->year--;
			if ( isleap_4(pp->year) )		/* Y2KFixes */
			    day = 366;
			else
			    day = 365;
		}
	}

	if (pp->hour > 23) {
		pp->hour -= 24;
		day++;
		if (day > lastday) {
			pp->year++;
			day = 1;
		}
	}

	pp->day = day;

	/*
	 * Decode the MFLRV indicators.
	 * NEED TO FIGURE OUT how to deal with the request for service,
	 * time quality, and frequency quality indicators some day. 
	 */
	if (syncchar != '0') {
		pp->leap = LEAP_NOTINSYNC;
	}
	else {
		pp->leap = LEAP_NOWARNING;
		switch (leapchar) {

		    case '0':
			break;
                     
		    /* See http://bugs.ntp.org/1090
		     * Ignore leap announcements unless June or December.
		     * Better would be to use :GPSTime? to find the month,
		     * but that seems too likely to introduce other bugs.
		     */
		    case '+':
			if ((month==6) || (month==12))
			    pp->leap = LEAP_ADDSECOND;
			break;
                     
		    case '-':
			if ((month==6) || (month==12))
			    pp->leap = LEAP_DELSECOND;
			break;
                     
		    default:
#ifdef DEBUG
			if (debug)
			    printf("hpgps: unrecognized leap indicator: %c\n",
				   leapchar);
#endif
			refclock_report(peer, CEVNT_BADTIME);
			return;
		} /* end of leapchar switch */
	}

	/*
	 * Process the new sample in the median filter and determine the
	 * reference clock offset and dispersion. We use lastrec as both
	 * the reference time and receive time in order to avoid being
	 * cute, like setting the reference time later than the receive
	 * time, which may cause a paranoid protocol module to chuck out
	 * the data.
	 */
	if (!refclock_process(pp)) {
		refclock_report(peer, CEVNT_BADTIME);
		return;
	}
	pp->lastref = pp->lastrec;
	refclock_receive(peer);

	/*
	 * If CLK_FLAG4 is set, ask for the status screen response.
	 */
	if (pp->sloppyclockflag & CLK_FLAG4){
		up->linecnt = 22; 
		if (write(pp->io.fd, ":SYSTEM:PRINT?\r", 15) != 15)
		    refclock_report(peer, CEVNT_FAULT);
	}
}