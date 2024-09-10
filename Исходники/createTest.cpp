static void
getCurrentOsSched(int *priority, int *policy)
{
#if defined(SPEC_PTHREAD_API) && !defined(J9ZOS390)
	OSTHREAD tid = pthread_self();
	struct sched_param param;

	PTHREAD_VERBOSE(pthread_getschedparam(tid, policy, &param));
	*priority = param.sched_priority;

#elif defined(SPEC_WIN_API)
	OSTHREAD tid = GetCurrentThread();
	*priority = GetThreadPriority(tid);
	*policy = -1;

#else
	*priority = -1;
	*policy = -1;
#endif /* defined(SPEC_PTHREAD_API) */
}