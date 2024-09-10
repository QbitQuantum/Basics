void rfc822::mkdate_cst(time_t t, char *buf, size_t size)
{
	struct tm *p;
	int offset = 0;

#ifdef	WIN32
# if _MSC_VER >= 1500
	struct tm tm_buf;
	long s;
	p = &tm_buf;
	if (localtime_s(p, &t) != 0)
		p = NULL;
# else
	p = localtime(&t);
# endif
#else
	struct tm tm_buf;
	p = localtime_r(&t, &tm_buf);
#endif

	buf[0] = 0;
	if (p == NULL)
		return;

#if	USE_TIME_ALTZONE

	offset = -_timezone;

	if (p->tm_isdst > 0)
		offset = -altzone;

	if (offset % 60)
	{
		offset = 0;
#ifdef	WIN32
# if _MSC_VER >= 1500
		p = &tm_buf;
		if (gmtime_s(p, &t) != 0)
			p = NULL;
# else
		p = gmtime(&t);
# endif
#else
		p = gmtime_r(&t, &tm_buf);
#endif
	}
	offset /= 60;
#else
#if	USE_TIME_DAYLIGHT

#ifdef WIN32
# if _MSC_VER >= 1500
	if ( _get_timezone(&s) != 0)
		s = 0;
	offset =- s;
# else
	offset = - _timezone;
# endif
#elif !defined(ACL_FREEBSD)  // XXX -zsx
	offset = - timezone;
#endif

	if (p == NULL)
		return;

	if (p->tm_isdst > 0)
		offset += 60 * 60;
	if (offset % 60) {
		offset = 0;
#ifdef	WIN32
# if _MSC_VER >= 1500
		p = &tm_buf;
		if (gmtime_s(p, &t) != 0)
			p = NULL;
# else
		p = gmtime(&t);
# endif
#else
		p = gmtime_r(&t, &tm_buf);
#endif
	}
	offset /= 60;
#else
#if	USE_TIME_GMTOFF
	offset = p->tm_gmtoff;

	if (offset % 60) {
		offset = 0;
#ifdef	WIN32
# if _MSC_VER >= 1500
		p = &tm_buf;
		if (gmtime_s(p, &t) != 0)
			p = NULL;
# else
		p = gmtime(&t);
# endif
#else
		p = gmtime_r(&t, &tm_buf);
#endif
	}
	offset /= 60;
#else
#ifdef	WIN32
# if _MSC_VER >= 1500
	p = &tm_buf;
	if (gmtime_s(p, &t) != 0)
		p = NULL;
# else
	p = gmtime(&t);
# endif
#else
	p = gmtime_r(&t, &tm_buf);
#endif
	offset = 0;
#endif
#endif
#endif

	offset = (offset % 60) + offset / 60 * 100;

#if defined(WIN32) && _MSC_VER >= 1500
	_snprintf_s(buf, size, size, "%s, %02d %s %04d %02d:%02d:%02d %+05d (CST)",
		wdays[p->tm_wday],
		p->tm_mday,
		months[p->tm_mon],
		p->tm_year + 1900,
		p->tm_hour,
		p->tm_min,
		p->tm_sec,
		offset);
#else
	snprintf(buf, size, "%s, %02d %s %04d %02d:%02d:%02d %+05d (CST)",
		wdays[p->tm_wday],
		p->tm_mday,
		months[p->tm_mon],
		p->tm_year + 1900,
		p->tm_hour,
		p->tm_min,
		p->tm_sec,
		offset);
#endif
}