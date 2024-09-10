errno_t	ctime_s(char *s, rsize_t maxsize, const time_t *timer)
{
	if(s == NULL || timer == NULL)
	{
		ERR()
		VIOLATION("s or time is NULL")
	}
	if(maxsize < 26)
	{
		ERR()
		VIOLATION("maxsize is less than 26")
	}
	if(maxsize > RSIZE_MAX)
	{
		ERR()
		VIOLATION("maxsize is greater than RSIZE_MAX")
	}
	struct tm date;
	localtime_r(timer, &date);
	return (asctime_s(s, maxsize, &date));
}