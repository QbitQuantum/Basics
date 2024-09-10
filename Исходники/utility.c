/* Catches calls to the POSIX gmtime_r and converts them to a related WIN32 version. */
struct tm *gmtime_r (time_t *t, struct tm *gmt)
{
	gmtime_s (gmt, t);

	return gmt;
}