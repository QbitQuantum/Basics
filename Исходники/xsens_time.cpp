int64_t getDateTime(tm *date)
{
#ifdef _WIN32
	__time64_t t;
	_time64(&t);
	if(date != 0)
		_localtime64_s(date, &t);
	return (int64_t)t;
#else
	time_t t;
	time(&t);
	if(date != 0)
	{
		tm *result = localtime(&t);
		memcpy(date, result, sizeof(tm));
	}
	return (int64_t)t;
#endif
}