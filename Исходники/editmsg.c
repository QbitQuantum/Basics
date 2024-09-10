/*
 * Interrupt handler for builtin_editor().
 */
static void builtin_interrupt_handler(int sig)
{
	signal(SIGINT, builtin_interrupt_handler);
	signal(SIGQUIT, builtin_interrupt_handler);

	++builtin_interrupt_count;

#if defined(SIGSET) && defined(HASSIGHOLD)
	/*
	 * During execution of a signal handler set with sigset(),
	 * the originating signal is held.  It must be released or
	 * it cannot recur.
	 */
	sigrelse(sig);
#endif /* SIGSET and HASSIGHOLD */

	LONGJMP(builtin_jmpbuf, 1);
}