FILE *popen( const char *s, const char *m )
{
#ifdef __DOS__
    return( NULL );
#else
    return( _popen( s, m ) );
#endif
}