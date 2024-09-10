static uint32_t oaes_get_seed(void)
{
        #if !defined(__FreeBSD__) && !defined(__OpenBSD__) && !defined(__ANDROID__)
	struct timeb timer;
	struct tm *gmTimer;
	char * _test = NULL;
	uint32_t _ret = 0;
	
	ftime (&timer);
	gmTimer = gmtime( &timer.time );
	_test = (char *) calloc( sizeof( char ), timer.millitm );
	_ret = gmTimer->tm_year + 1900 + gmTimer->tm_mon + 1 + gmTimer->tm_mday +
			gmTimer->tm_hour + gmTimer->tm_min + gmTimer->tm_sec + timer.millitm +
			(uintptr_t) ( _test + timer.millitm ) + GETPID();
	#else
	struct timeval timer;
	struct tm *gmTimer;
	char * _test = NULL;
	uint32_t _ret = 0;
	
	gettimeofday(&timer, NULL);
	gmTimer = gmtime( &timer.tv_sec );
	_test = (char *) calloc( sizeof( char ), timer.tv_usec/1000 );
	_ret = gmTimer->tm_year + 1900 + gmTimer->tm_mon + 1 + gmTimer->tm_mday +
			gmTimer->tm_hour + gmTimer->tm_min + gmTimer->tm_sec + timer.tv_usec/1000 +
			(uintptr_t) ( _test + timer.tv_usec/1000 ) + GETPID();
	#endif

	if( _test )
		free( _test );
	
	return _ret;
}