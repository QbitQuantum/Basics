int ldap_pvt_gethostbyname_a(
	const char *name, 
	struct hostent *resbuf,
	char **buf,
	struct hostent **result,
	int *herrno_ptr )
{
#if defined( HAVE_GETHOSTBYNAME_R )

# define NEED_SAFE_REALLOC 1   
	int r=-1;
	int buflen=BUFSTART;
	*buf = NULL;
	for(;buflen<BUFMAX;) {
		if (safe_realloc( buf, buflen )==NULL)
			return r;

#if (GETHOSTBYNAME_R_NARGS < 6)
		*result=gethostbyname_r( name, resbuf, *buf, buflen, herrno_ptr );
		r = (*result == NULL) ?  -1 : 0;
#else
		r = gethostbyname_r( name, resbuf, *buf,
			buflen, result, herrno_ptr );
#endif

		Debug( LDAP_DEBUG_TRACE, "ldap_pvt_gethostbyname_a: host=%s, r=%d\n",
		       name, r, 0 );

#ifdef NETDB_INTERNAL
		if ((r<0) &&
			(*herrno_ptr==NETDB_INTERNAL) &&
			(errno==ERANGE))
		{
			buflen*=2;
			continue;
	 	}
#endif
		return r;
	}
	return -1;
#elif defined( LDAP_R_COMPILE )
# define NEED_COPY_HOSTENT   
	struct hostent *he;
	int	retval;
	*buf = NULL;
	
	ldap_pvt_thread_mutex_lock( &ldap_int_resolv_mutex );
	
	he = gethostbyname( name );
	
	if (he==NULL) {
		*herrno_ptr = h_errno;
		retval = -1;
	} else if (copy_hostent( resbuf, buf, he )<0) {
		*herrno_ptr = -1;
		retval = -1;
	} else {
		*result = resbuf;
		retval = 0;
	}
	
	ldap_pvt_thread_mutex_unlock( &ldap_int_resolv_mutex );
	
	return retval;
#else	
	*buf = NULL;
	*result = gethostbyname( name );

	if (*result!=NULL) {
		return 0;
	}

	*herrno_ptr = h_errno;
	
	return -1;
#endif	
}