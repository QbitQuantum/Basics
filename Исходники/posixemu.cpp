int posixemu_utime (const TCHAR *name, struct utimbuf *ttime)
{
	int result = -1, tolocal;
	long days, mins, ticks;
	time_t actime;

	if (!ttime) {
		actime = time (NULL);
		tolocal = 0;
	} else {
		tolocal = 1;
		actime = ttime->actime;
	}
	get_time (actime, &days, &mins, &ticks);

	if (setfiletime (name, days, mins, ticks, tolocal))
		result = 0;

	return result;
}