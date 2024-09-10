/* private routines */
static void
xstrftime(struct archive_string *as, const char *fmt, time_t t)
{
/** like strftime(3) but for time_t objects */
	struct tm *rt;
#if defined(HAVE_GMTIME_R) || defined(HAVE__GMTIME64_S)
	struct tm timeHere;
#endif
	char strtime[100];
	size_t len;

#ifdef HAVE_GMTIME_R
	if ((rt = gmtime_r(&t, &timeHere)) == NULL)
		return;
#elif defined(HAVE__GMTIME64_S)
	_gmtime64_s(&timeHere, &t);
#else
	if ((rt = gmtime(&t)) == NULL)
		return;
#endif
	/* leave the hard yacker to our role model strftime() */
	len = strftime(strtime, sizeof(strtime)-1, fmt, rt);
	archive_strncat(as, strtime, len);
}