unsigned long long
timespec_to_usec_ull(struct timespec *ts)
{
	return llround((ts->tv_sec * 1E9 + ts->tv_nsec) / 1000.0);
}