struct tm* MMatchGetLocalTime()
{
	__time64_t long_time;

	_time64( &long_time );


	/* Obtain coordinated universal time: */
	return _localtime64( &long_time );
}