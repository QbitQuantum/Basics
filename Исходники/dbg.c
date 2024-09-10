int dbg_printf(DBG * d, const char *fmt, ...)
{
	char *buf;
	va_list ap;
	int l, size;
	size_t i;
	pspTime tm;
	char timestr[80];
	int timelen;

	if (!d)
		return -1;
	if (!d->on)
		return 0;

	va_start(ap, fmt);

	sceRtcGetCurrentClockLocalTime(&tm);

	SPRINTF_S(timestr, "%u-%u-%u %02u:%02u:%02u", tm.year, tm.month, tm.day, tm.hour, tm.minutes, tm.seconds);

	timelen = strlen(timestr);

	size = DBG_BUFSIZE;
	buf = malloc(size + timelen + 2);
	strcpy_s(buf, size + timelen + 2, timestr);
	strcat_s(buf, size + timelen + 2, ": ");
	l = vsnprintf(buf + timelen + 2, size, fmt, ap);
	buf[size + timelen + 2 - 1] = '\0';
	while (strlen(buf) == size - 1) {
		size *= 2 + 16;
		buf = safe_realloc(buf, size + timelen + 2);
		if (!buf)
			return 0;
		strcpy_s(buf, size + timelen + 2, timestr);
		strcat_s(buf, size + timelen + 2, ": ");
		l = vsnprintf(buf + timelen + 2, size, fmt, ap);
		buf[size + timelen + 2 - 1] = '\0';
	}
	strcat_s(buf, size + timelen + 2, "\n");
	va_end(ap);
	for (i = 0; i < d->otsize; ++i) {
		if (d->ot[i].write)
			(*d->ot[i].write) (d->ot[i].arg, buf);
	}
	free(buf);
	return l;
}