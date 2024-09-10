std::string FiletimeAsString( const FILETIME &ft )
{
	SYSTEMTIME stUTC, st;
	FILETIME localFt;
	FileTimeToSystemTime (&ft, &stUTC);
	SystemTimeToTzSpecificLocalTime(NULL, &stUTC, &st);
	SystemTimeToFileTime(&st, &localFt);
	return  boost::posix_time::to_simple_string(boost::posix_time::from_ftime<boost::posix_time::ptime>(localFt));
}