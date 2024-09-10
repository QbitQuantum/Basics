int sanity_run(struct cpuid_state_t *state)
{
	sanity_handler_t *p = handlers;
	unsigned int ret = 0;
#ifdef TARGET_OS_WINDOWS
	TIMECAPS tc;
	timeGetDevCaps(&tc, sizeof(TIMECAPS));
	timeBeginPeriod(tc.wPeriodMin);
#endif
	while (*p) {
		if ((*p++)(state) != 0)
			ret = p - handlers;
	}
#ifdef TARGET_OS_WINDOWS
	timeEndPeriod(tc.wPeriodMin);
#endif
	return ret;
}