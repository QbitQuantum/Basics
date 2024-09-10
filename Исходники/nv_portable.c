time_t
nv_mkgmtime(struct tm *tm)
{
#if NV_MSVC
	return _mkgmtime(tm);
#else	
	time_t ret;
	const char *tz;
	
#  if _OPENMP
#    pragma omp critical (nv_mkgmtime)
#  endif
	{
		tz = nv_getenv("TZ");
		nv_setenv("TZ", "");
		tzset();
		ret = mktime(tm);
		if (tz) {
			nv_setenv("TZ", tz);
		} else {
			nv_unsetenv("TZ");
		}
		tzset();
	}
	
	return ret;
#endif	
}