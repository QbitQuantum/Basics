void
ut_suppress_errmsg()
{
	ErrMode = GetErrorMode();
	SetErrorMode(ErrMode | SEM_NOGPFAULTERRORBOX |
		SEM_FAILCRITICALERRORS);
	AbortBehave = _set_abort_behavior(0, _WRITE_ABORT_MSG |
		_CALL_REPORTFAULT);
	Suppressed = TRUE;
}