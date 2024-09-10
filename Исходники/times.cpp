double currentTime(void)
{
    double ans = NA_REAL;

#ifdef HAVE_TIMESPEC_GET
    struct timespec tp;
    int res = timespec_get(&tp, TIME_UTC);
    if(res != 0)
	ans = (double) tp.tv_sec + 1e-9 * (double) tp.tv_nsec;
#elif defined(HAVE_CLOCK_GETTIME) && defined(CLOCK_REALTIME)
    /* Has 2038 issue if time_t: tv.tv_sec is 32-bit. */
    struct timespec tp;
    int res = clock_gettime(CLOCK_REALTIME, &tp);
    if(res == 0)
	ans = (double) tp.tv_sec + 1e-9 * (double) tp.tv_nsec;

#elif defined(HAVE_GETTIMEOFDAY)
    /* Mac OS X, mingw.org, used on mingw-w64.
       Has 2038 issue if time_t: tv.tv_sec is 32-bit.
     */
    struct timeval tv;
    int res = gettimeofday(&tv, NULL);
    if(res == 0)
	ans = (double) tv.tv_sec + 1e-6 * (double) tv.tv_usec;

#else
    /* No known current OSes */
    time_t res = time(NULL);
    if(res != (time_t)(-1)) /* -1 must be an error as the real value -1
			       was ca 1969 */
	ans = (double) res;
#endif

#ifndef HAVE_POSIX_LEAPSECONDS
    /* No known current OSes */
    /* Disallowed by POSIX (1988-):
       http://www.mail-archive.com/[email protected]/msg00109.html
       http://en.wikipedia.org/wiki/Unix_time
    */
    if (!ISNAN(ans)) {
	ans -= n_leapseconds;
    }
#endif
    return ans;
}