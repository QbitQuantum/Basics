int gettimeofday(struct timeval *tv, struct timezone *tz)
{
	FILETIME        ft;
	LARGE_INTEGER   li;
	__int64         t;
	int             nnested = 0;
	LARGE_INTEGER stamp;
	time_t now;
	TIME_CTX_T *ctx = tls_calloc(sizeof(TIME_CTX_T));

	/* 每个线程调用此函数时都需要进行初始化，但为了防止开机时间太长
	 * 而造成时钟计数归零溢出，所以每隔 1 天校对一次基准时间
	 */
#define DAY_SEC	(3600 * 24)

	time(&now);
	if (now - ctx->last_init > DAY_SEC) {
		ctx->last_init = now;

		/* 获得CPU的时钟频率 */
		if (!QueryPerformanceFrequency(&ctx->frequency))
			acl_msg_fatal("%s(%d): Unable to get System Frequency(%s)",
				__FILE__, __LINE__, acl_last_serror());
		/* 获得系统时间(自 1970 至今) */
		GetSystemTimeAsFileTime(&ft);
		li.LowPart  = ft.dwLowDateTime;
		li.HighPart = ft.dwHighDateTime;
		t  = li.QuadPart;       /* In 100-nanosecond intervals */
		t -= EPOCHFILETIME;     /* Offset to the Epoch time */
		t /= 10;                /* In microseconds */

		/* 转换成本次开机后的基准时间 */
		ctx->tvbase.tv_sec  = (long)(t / 1000000);
		ctx->tvbase.tv_usec = (long)(t % 1000000);

		/* 获得本次开机后到现在的时钟计数 */
		if (!QueryPerformanceCounter(&ctx->stamp))
			acl_msg_fatal("%s(%d): unable to get System time(%s)",
				__FILE__, __LINE__, acl_last_serror());
	}

	/* 开始获得现在的时间截 */

	if (tv) {
		/* 获得本次开机后至现在的时钟计数  */
		if (!QueryPerformanceCounter(&stamp))
			acl_msg_fatal("%s(%d): unable to get System time(%s)",
				__FILE__, __LINE__, acl_last_serror());

		/* 计算当前精确时间截 */
		t = (stamp.QuadPart - ctx->stamp.QuadPart) * 1000000 / ctx->frequency.QuadPart;
		tv->tv_sec = ctx->tvbase.tv_sec + (long)(t / 1000000);
		tv->tv_usec = ctx->tvbase.tv_usec + (long)(t % 1000000);
	}

	if (tz) {
		if (!ctx->tzflag) {
			_tzset();
			ctx->tzflag++;
		}
		tz->tz_minuteswest = _timezone / 60;
		tz->tz_dsttime = _daylight;
	}

	return (0);
}