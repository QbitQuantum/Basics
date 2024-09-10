static void
stime_darg(const char *arg, struct timeval *tvp)
{
	struct tm t = { .tm_sec = 0 };
	const char *fmt, *colon;
	char *p;
	int val, isutc = 0;

	tvp[0].tv_usec = 0;
	t.tm_isdst = -1;
	colon = strchr(arg, ':');
	if (colon == NULL || strchr(colon + 1, ':') == NULL)
		goto bad;
	fmt = strchr(arg, 'T') != NULL ? "%Y-%m-%dT%H:%M:%S" :
	    "%Y-%m-%d %H:%M:%S";
	p = strptime(arg, fmt, &t);
	if (p == NULL)
		goto bad;
	/* POSIX: must have at least one digit after dot */
	if ((*p == '.' || *p == ',') && isdigit((unsigned char)p[1])) {
		p++;
		val = 100000;
		while (isdigit((unsigned char)*p)) {
			tvp[0].tv_usec += val * (*p - '0');
			p++;
			val /= 10;
		}
	}
	if (*p == 'Z') {
		isutc = 1;
		p++;
	}
	if (*p != '\0')
		goto bad;

	tvp[0].tv_sec = isutc ? timegm(&t) : mktime(&t);

	tvp[1] = tvp[0];
	return;

bad:
	errx(1, "out of range or illegal time specification: YYYY-MM-DDThh:mm:SS[.frac][tz]");
}

/* Calculate a time offset in seconds, given an arg of the format [-]HHMMSS. */
int
timeoffset(const char *arg)
{
	int offset;
	int isneg;

	offset = 0;
	isneg = *arg == '-';
	if (isneg)
		arg++;
	switch (strlen(arg)) {
	default:				/* invalid */
		errx(1, "Invalid offset spec, must be [-][[HH]MM]SS");

	case 6:					/* HHMMSS */
		offset = ATOI2(arg);
		/* FALLTHROUGH */
	case 4:					/* MMSS */
		offset = offset * 60 + ATOI2(arg);
		/* FALLTHROUGH */
	case 2:					/* SS */
		offset = offset * 60 + ATOI2(arg);
	}
	if (isneg)
		return (-offset);
	else
		return (offset);
}