int LOG_ALT(const char *fmt,...)
{
	char buf[102400];
	int len = sizeof(buf)-1;
	int xlen = 0;
    iop_log_service_t *log = g_iop_log_service;
    struct tm t;
	int level = IOP_LOG_ALERT;
    time_t n ;
	int r;
	if(log && (level > log->log_level))
    {
        return -1;
    }
	buf[len] = 0;
	n= time(NULL);
	#ifdef WIN32
		localtime_s(&t,&n);
		r = _snprintf_s(buf,len, len,"[ALT %02d:%02d:%02d] ", 
                t.tm_hour,t.tm_min, t.tm_sec);
	#else
		t = *localtime(&n);
	    r = snprintf(buf,len, "[ALT %02d:%02d:%02d] ", 
                t.tm_hour,t.tm_min, t.tm_sec);
	#endif
	{
	va_list ap;
    va_start(ap, fmt);

#ifdef WIN32
	xlen = vsnprintf_s((char *)buf+r,len-r,len-r, fmt, ap);
#else
	xlen = vsnprintf((char *)buf+r,len-r, fmt, ap);
#endif
	va_end(ap);
	}
    if(xlen + r > len)
    {
        r = len;
    }
    else
    {
        r += xlen;
    }
    return iop_log_write(log,buf, r);

}