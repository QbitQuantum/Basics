char *wnt_ctime(const time_t *t)
{
	static char future[] = "Fri Dec 31 23:59:59 1999";
	char *buf = _ctime64(t);
	if(!buf) /* Y2.038K bug in 32bit... */
		buf=future;
	else if(buf[8]=='0')
		buf[8]=' ';
	return buf;
}