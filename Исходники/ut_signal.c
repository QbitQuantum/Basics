/*
 * ut_sigaction -- a sigaction that cannot return < 0
 */
int
ut_sigaction(const char *file, int line, const char *func,
		int signum, struct sigaction *act, struct sigaction *oldact)
{
#ifndef _WIN32
	int retval = sigaction(signum, act, oldact);
	if (retval != 0)
		ut_fatal(file, line, func, "!sigaction: %s", strsignal(signum));
	return retval;
#else
	if (signum == SIGABRT) {
		DWORD dwMode = GetErrorMode();
		SetErrorMode(dwMode | SEM_NOGPFAULTERRORBOX |
			SEM_FAILCRITICALERRORS);
		_set_abort_behavior(0, _WRITE_ABORT_MSG | _CALL_REPORTFAULT);
	}
	if (signum == SIGSEGV) {
		Sa_handler = act->sa_handler;
		Signum = signum;
		AddVectoredExceptionHandler(0, exception_handler);
	}

	_crt_signal_t retval = signal(signum, act->sa_handler);
	if (retval == SIG_ERR)
		ut_fatal(file, line, func, "!signal: %d", signum);

	if (oldact != NULL) {
		oldact->sa_handler = retval;
	}
	return 0;
#endif
}