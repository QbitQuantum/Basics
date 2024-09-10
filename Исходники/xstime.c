/*! \brief Retrieves the date and time (platform-independent)
	\param date : if non-zero the local (!) date and time is stored in the tm struct this parameter points to
	\returns The UTC date and time as seconds since 1970
*/
int64_t XsTime_getDateTime(struct tm *date)
{
#ifdef _WIN32
	__time64_t t;
	_time64(&t);	//lint !e534 return value is stored in t
	if (date != 0)
		_localtime64_s(date, &t);	//lint !e534
	return (int64_t)t;
#else
	time_t t;
	time(&t);
	if(date != 0)
	{
		struct tm *result = localtime(&t);
		memcpy(date, result, sizeof(struct tm));
	}
	return (int64_t)t;
#endif
}