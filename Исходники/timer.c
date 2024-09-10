DEFINE_SYSCALL(clock_getres, int, clk_id, struct timespec *, res)
{
	log_info("clock_getres(%d, 0x%p)", clk_id, res);
	if (!mm_check_write(res, sizeof(struct timespec)))
		return -L_EFAULT;
	switch (clk_id)
	{
	case CLOCK_REALTIME:
	{
		ULONG coarse, fine, actual;
		NtQueryTimerResolution(&coarse, &fine, &actual);
		uint64_t ns = (uint64_t)actual * NANOSECONDS_PER_TICK;
		res->tv_sec = ns / NANOSECONDS_PER_SECOND;
		res->tv_nsec = ns % NANOSECONDS_PER_SECOND;
		return 0;
	}
	case CLOCK_MONOTONIC:
	case CLOCK_MONOTONIC_COARSE:
	case CLOCK_MONOTONIC_RAW:
	{
		LARGE_INTEGER freq;
		QueryPerformanceFrequency(&freq);
		uint64_t ns = (double)1. / (double)freq.QuadPart;
		if (ns == 0)
		{
			res->tv_sec = 0;
			res->tv_nsec = 1;
		}
		else
		{
			res->tv_sec = ns / NANOSECONDS_PER_SECOND;
			res->tv_nsec = ns % NANOSECONDS_PER_SECOND;
		}
		return 0;
	}
	default:
		return -L_EINVAL;
	}
}