/*
 *	timer signal (SIGALRM) handler
 *	SIGALRM  handler - only set during hibernate
 */
static void user_tim_handler (int sig)
{
	int threads = att_val (&enabled_threads);
	
	if (RTS_TRACING) {
		MESSAGE ("USERPROC: Alarm ringing (SIGALRM).\n");
		FFLUSH (stderr);
	}

	while (threads) {
		int n 		= bsf (threads);
		sched_t *s 	= schedulers[n];

		threads &= ~(s->id);

		ccsp_wake_thread (s, SYNC_TIME_BIT);
	}
	
	#if defined(SIGNAL_TYPE_SYSV)
		signal (SIGALRM, user_tim_handler);
	#endif /* SIGNAL_TYPE */
}