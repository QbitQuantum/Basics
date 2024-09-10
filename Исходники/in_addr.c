char *
InAddr_to_string ( in_addr_t x )
{
	struct in_addr y;
	char * retval = ( char * ) Malloc ( INET_ADDRSTRLEN );

	y.s_addr = x;
	Inet_ntop ( AF_INET, ( const void* ) &y, retval, INET_ADDRSTRLEN );

	return retval;;
}