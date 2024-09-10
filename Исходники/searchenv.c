void searchenv( const char * name, const char * env, char * buf )
{
    const char 	*src;
	char		*dst;
	char		*tmp;

	src = getenv( env );
    if( src == (char *)0 ) {
	    _searchenv( name, env, buf );
		return;
	}
	strcpy( __pathbuff, FUNKY_ENVNAME "=" );
	dst = &__pathbuff[ FUNKY_ENVNAME_LEN + 1 ];
	for( ;; ) {
	    if( *src == '\0' ) break;
	    if( *src == '%' && *++src != '%' ) {
			tmp = dst;
			for( ;; ) {
				*dst = *src;
				if( *src == '\0' ) break;
				if( *src++ == '%' ) break;
				++dst;
			}
			*dst = '\0';
			dst = getenv( tmp );
			if( dst == (char *)0 ) {
				dst = tmp;
			} else {
				strcpy( tmp, dst );
				dst = &tmp[strlen(tmp)];
			}
		} else {
		    *dst++ = *src++;
		}
	}
	*dst = '\0';
	putenv( __pathbuff );
	_searchenv( name, FUNKY_ENVNAME, buf );
	__pathbuff[ FUNKY_ENVNAME_LEN + 1 ] = '\0';
	putenv( __pathbuff );
}