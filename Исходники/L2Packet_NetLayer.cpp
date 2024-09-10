char *L2PNet_inet_ntoa( struct in_addr in )
{
	char b[10];
	char *p = l2pnet_static_inet_ntoa_buffer;
	_itoa( in.S_un.S_addr & 0xFF, b, 10 );
	strcpy( p, b );
	_itoa( (in.S_un.S_addr >> 8) & 0xFF, b, 10 );
	strcat( p, "." );
	strcat( p, b );
	_itoa( (in.S_un.S_addr >> 16) & 0xFF, b, 10 );
	strcat( p, "." );
	strcat( p, b );
	_itoa( (in.S_un.S_addr >> 24) & 0xFF, b, 10 );
	strcat( p, "." );
	strcat( p, b );

    return l2pnet_static_inet_ntoa_buffer;
}