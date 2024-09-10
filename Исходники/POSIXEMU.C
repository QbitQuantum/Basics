int posixemu_utime( const char *name, struct utimbuf *time )
{
    int result = -1;
    long days, mins, ticks;

    get_time( time->actime, &days, &mins, &ticks );

    if( setfiletime( name, days, mins, ticks ) )
        result = 0;

	return result;
}