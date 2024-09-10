/*
 * util_suppress_errmsg -- suppresses "abort" window on Windows if env variable
 * is set, useful for automatic tests
 */
void
util_suppress_errmsg(void)
{
	if (os_getenv("PMDK_NO_ABORT_MSG") != NULL) {
		DWORD err = GetErrorMode();
		SetErrorMode(err | SEM_NOGPFAULTERRORBOX |
			SEM_FAILCRITICALERRORS);
		_set_abort_behavior(0, _WRITE_ABORT_MSG | _CALL_REPORTFAULT);
	}
}