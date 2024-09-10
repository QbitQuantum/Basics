errno_t __cdecl _localtime64_s( struct tm * _tm, const __time64_t *time )
{
	errno_t retval = EINVAL;
	if( _tm && time && (time < 0) )
	{
		struct tm *tm2 = _localtime64( time );
		if( tm2 )
		{
			*_tm = *tm2;
			retval = 0;
		}
	}
	return retval;
}