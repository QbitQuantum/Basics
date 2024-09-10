long tcp_connect(bmdnet_handler_ptr handler,char*host,long port)
{
	long status;
#ifndef _WIN32
	char aux[256];
	struct sockaddr_in serv_addr;
	struct hostent hostinfo_buf;
	struct hostent *hostinfo=&hostinfo_buf;
	long one = 1;
	int si_temp; /* to musi byc int - nie zmieniac !!!! */
#else
	struct addrinfo *result = NULL, hints;
	char * portstr=NULL;
#endif
	if (host == NULL || port == 0 || port > 65535)
	{
		return(-1);
	}

	handler->s = (long)socket(AF_INET, SOCK_STREAM,IPPROTO_TCP);
	if (handler->s <= 0)
		return -1;

#ifndef WIN32
	if (setsockopt(handler->s, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(one)))
	{
		return ERR(ERR_net, "Cannot set SO_REUSEADDR flag on socket", "LK");
	}
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons((short)port);

	if( gethostbyname_r(host, &hostinfo_buf, aux, sizeof(aux), &hostinfo, &si_temp) != 0 )
	{
		PRINT_ERROR("gethostbyname_r failed.\n");
		return(-1);
	}
	if (hostinfo==NULL) {
		PRINT_ERROR("Hostname not found.\n");
		return(-1);
	}
	serv_addr.sin_addr=*(struct in_addr *)hostinfo->h_addr;
	status = connect(handler->s, (const struct sockaddr *)&serv_addr,sizeof(serv_addr));
	if (status)
	{
		PRINT_ERROR("Cannot connect to host.\n");
		return(-1);
	}
#else
	ZeroMemory( &hints, sizeof(hints) );
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	portstr = calloc(6,sizeof(char));
	_itoa_s(port, portstr, 6,10);
	status = getaddrinfo(host, portstr, &hints, &result);
	if( status == WSAHOST_NOT_FOUND )
	{
		BMD_FOK(BMD_ERR_NET_RESOLV);
	}
	else
		if( status != 0 )
		{
			BMD_FOK(BMD_ERR_OP_FAILED);
		}
	if (result == NULL)
	{
		BMD_FOK(BMD_ERR_OP_FAILED);
	}
	status = connect(handler->s, result->ai_addr,(long)result->ai_addrlen);
	if (status)
	{
		PRINT_ERROR("Cannot connect to host.\n");
		return(-1);
	}
#endif

	return BMD_OK;
};