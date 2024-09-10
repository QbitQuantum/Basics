struct addrinfo* getaddr( const char* server, const char* service, int fam)
{
	struct addrinfo hints;
	memset( &hints, 0, sizeof( struct addrinfo));
	hints.ai_family = fam; //AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	
	return Getaddrinfo( server, service, &hints);
}