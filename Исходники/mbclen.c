/*
 * assume MB_CUR_MAX == 2
 *
 * @implemented
 */
int mblen( const char *s, size_t count )
{
	size_t l;
	if ( s == NULL )
		return 0;

	l =  _mbclen((const unsigned char *)s);
	if ( l < count )
		return -1;
	return l;
}