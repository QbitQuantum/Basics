static void wait_timeout(struct timespec *timeout, int ms)
{
	ldiv_t div_result;
	long sec, usec, x;

#ifdef WIN32
	{
		struct _timeb now;
		_ftime(&now);
		sec = now.time;
		usec = now.millitm * 1000; /* microsecond precision would be better */
	}
#else
	{
		struct timeval now;
		gettimeofday(&now, NULL);
		sec = now.tv_sec;
		usec = now.tv_usec;
	}
#endif

	/* add current time + millisecond offset */
	div_result = ldiv(ms, 1000);
	timeout->tv_sec = sec + div_result.quot;

	x = usec + (div_result.rem * 1000);

	if (x >= 1000000) {
		timeout->tv_sec++;
		x -= 1000000;
	}

	timeout->tv_nsec = x * 1000;
}