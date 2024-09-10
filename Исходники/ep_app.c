void
ep_app_abort(
	const char *fmt,
	...)
{
	va_list av;

	va_start(av, fmt);
	printmessage("ABORT", EpVid->vidfgyellow, EpVid->vidbgred, fmt, av);
	va_end(av);

	if (EP_UT_BITSET(EP_APP_FLAG_LOGABORTS, OperationFlags))
	{
		va_start(av, fmt);
		ep_logv(EP_STAT_ABORT, fmt, av);
		va_end(av);
	}

	fprintf(stderr, "\n\t(exiting)\n");
	abort();
	/*NOTREACHED*/
}