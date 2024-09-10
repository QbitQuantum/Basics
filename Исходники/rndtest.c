static void
rndtest_report(struct rndtest_state *rsp, int failure, const char *fmt, ...)
{
	char buf[80];
	__va_list ap;

	if (rndtest_verbose == 0)
		return;
	if (!failure && rndtest_verbose == 1)	/* don't report successes */
		return;
	__va_start(ap, fmt);
	kvsnprintf(buf, sizeof (buf), fmt, ap);
	__va_end(ap);
	device_printf(rsp->rs_parent, "rndtest: %s\n", buf);
}