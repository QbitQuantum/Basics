/*
 * init_timer - initialize the timer data structures
 */
void
init_timer(void)
{
# if defined SYS_WINNT & !defined(SYS_CYGWIN32)
	HANDLE hToken = INVALID_HANDLE_VALUE;
	TOKEN_PRIVILEGES tkp;
# endif /* SYS_WINNT */

	/*
	 * Initialize...
	 */
	alarm_flag = 0;
	alarm_overflow = 0;
	adjust_timer = 1;
	stats_timer = 0;
	huffpuff_timer = 0;
	interface_timer = 0;
	current_time = 0;
	timer_overflows = 0;
	timer_xmtcalls = 0;
	timer_timereset = 0;

#if !defined(SYS_WINNT)
	/*
	 * Set up the alarm interrupt.	The first comes 2**EVENT_TIMEOUT
	 * seconds from now and they continue on every 2**EVENT_TIMEOUT
	 * seconds.
	 */
# if !defined(VMS)
#  if defined(HAVE_TIMER_CREATE) && defined(HAVE_TIMER_SETTIME)
	if (timer_create (CLOCK_REALTIME, NULL, &ntpd_timerid) ==
#	ifdef SYS_VXWORKS
		ERROR
#	else
		-1
#	endif
	   )
	{
		fprintf (stderr, "timer create FAILED\n");
		exit (0);
	}
	(void) signal_no_reset(SIGALRM, alarming);
	itimer.it_interval.tv_sec = itimer.it_value.tv_sec = (1<<EVENT_TIMEOUT);
	itimer.it_interval.tv_nsec = itimer.it_value.tv_nsec = 0;
	timer_settime(ntpd_timerid, 0 /*!TIMER_ABSTIME*/, &itimer, NULL);
#  else
	(void) signal_no_reset(SIGALRM, alarming);
	itimer.it_interval.tv_sec = itimer.it_value.tv_sec = (1<<EVENT_TIMEOUT);
	itimer.it_interval.tv_usec = itimer.it_value.tv_usec = 0;
	setitimer(ITIMER_REAL, &itimer, (struct itimerval *)0);
#  endif
# else /* VMS */
	vmsinc[0] = 10000000;		/* 1 sec */
	vmsinc[1] = 0;
	lib$emul(&(1<<EVENT_TIMEOUT), &vmsinc, &0, &vmsinc);

	sys$gettim(&vmstimer);	/* that's "now" as abstime */

	lib$addx(&vmsinc, &vmstimer, &vmstimer);
	sys$setimr(0, &vmstimer, alarming, alarming, 0);
# endif /* VMS */
#else /* SYS_WINNT */
	_tzset();

	/*
	 * Get privileges needed for fiddling with the clock
	 */

	/* get the current process token handle */
	if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken)) {
		msyslog(LOG_ERR, "OpenProcessToken failed: %m");
		exit(1);
	}
	/* get the LUID for system-time privilege. */
	LookupPrivilegeValue(NULL, SE_SYSTEMTIME_NAME, &tkp.Privileges[0].Luid);
	tkp.PrivilegeCount = 1;  /* one privilege to set */
	tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
	/* get set-time privilege for this process. */
	AdjustTokenPrivileges(hToken, FALSE, &tkp, 0, (PTOKEN_PRIVILEGES) NULL, 0);
	/* cannot test return value of AdjustTokenPrivileges. */
	if (GetLastError() != ERROR_SUCCESS) {
		msyslog(LOG_ERR, "AdjustTokenPrivileges failed: %m");
	}

	/*
	 * Set up timer interrupts for every 2**EVENT_TIMEOUT seconds
	 * Under Windows/NT, 
	 */

	WaitableTimerHandle = CreateWaitableTimer(NULL, FALSE, NULL);
	if (WaitableTimerHandle == NULL) {
		msyslog(LOG_ERR, "CreateWaitableTimer failed: %m");
		exit(1);
	}
	else {
		DWORD Period = (1<<EVENT_TIMEOUT) * 1000;
		LARGE_INTEGER DueTime;
		DueTime.QuadPart = Period * 10000i64;
		if (!SetWaitableTimer(WaitableTimerHandle, &DueTime, Period, NULL, NULL, FALSE) != NO_ERROR) {
			msyslog(LOG_ERR, "SetWaitableTimer failed: %m");
			exit(1);
		}
	}

#endif /* SYS_WINNT */
}