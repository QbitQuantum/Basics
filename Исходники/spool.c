void
SpoolName(const char *const sdir, char *sp, size_t size, int flag, int serial, time_t when)
{
	char sname[64];
	char dstr[32];
	struct tm *ltp;

	if ((when == (time_t) 0) || (when == (time_t) -1))
		(void) time(&when);
	ltp = localtime(&when);
	if (ltp == NULL) {
		/* impossible */
		(void) Strncpy(dstr, "19700101-000000", size);
	} else {
		(void) strftime(dstr, sizeof(dstr), "%Y%m%d-%H%M%S", ltp);
	}
	(void) Strncpy(sp, sdir, size);
	(void) sprintf(sname, "/%c-%010u-%04x-%s",
		flag,
		(unsigned int) getpid(),
		(serial % (16 * 16 * 16 * 16)),
		dstr
	);
	(void) Strncat(sp, sname, size);
}	/* SpoolName */