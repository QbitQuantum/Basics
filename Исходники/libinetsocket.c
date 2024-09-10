//	 		       Socket    Src string      Src str len          Src service        Src service len         NUMERIC?
int accept_inet_stream_socket(int sfd, char* src_host, size_t src_host_len, char* src_service, size_t src_service_len, int flags, int accept_flags)
{
    struct sockaddr_storage client_info;
    int client_sfd;

# ifndef _TRADITIONAL_RDNS
    int retval;
# endif

# ifdef _TRADITIONAL_RDNS
    struct sockaddr_storage oldsockaddr;
    socklen_t oldsockaddrlen = sizeof(struct sockaddr_storage);
    struct hostent* he;
    void* addrptr;
    size_t in_addrlen;
    uint16_t sport = 0;
# endif

# ifdef VERBOSE
    const char* errstr;
# endif
    socklen_t addrlen = sizeof(struct sockaddr_storage);

    // Portable behavior
# if LIBSOCKET_LINUX
    if ( -1 == check_error((client_sfd = accept4(sfd,(struct sockaddr*)&client_info,&addrlen,accept_flags)))) // blocks
	return -1;
# else
    if ( -1 == check_error((client_sfd = accept(sfd,(struct sockaddr*)&client_info,&addrlen)))) // blocks
	return -1;
# endif

    if ( src_host_len > 0 || src_service_len > 0 ) // If one of the things is wanted. If you give a null pointer with a positive _len parameter, you won't get the address.
    {
	if ( flags == LIBSOCKET_NUMERIC )
	{
	    flags = NI_NUMERICHOST | NI_NUMERICSERV;
	} else
	{
	    flags = 0; // To prevent errors: Unknown flags are ignored
	}

# ifndef _TRADITIONAL_RDNS
	if ( 0 != (retval = getnameinfo((struct sockaddr*)&client_info,sizeof(struct sockaddr_storage),src_host,src_host_len,src_service,src_service_len,flags)) ) // Write information to the provided memory
	{
# ifdef VERBOSE
	    errstr = gai_strerror(retval);
	    debug_write(errstr);
# endif
	    return -1;
	}
# endif

# ifdef _TRADITIONAL_RDNS
	if ( -1 == check_error(getsockname(sfd,(struct sockaddr*)&oldsockaddr,&oldsockaddrlen)) )
	    return -1;

	if ( oldsockaddrlen > sizeof(struct sockaddr_storage) ) // If getsockname truncated the struct
	    return -1;

	if ( oldsockaddr.ss_family == AF_INET )
	{
	    addrptr = &(((struct sockaddr_in*)&client_info)->sin_addr);
	    in_addrlen = sizeof(struct in_addr);
	    sport = ntohs(((struct sockaddr_in*)&client_info)->sin_port);
	} else if ( oldsockaddr.ss_family == AF_INET6 )
	{
	    addrptr = &(((struct sockaddr_in6*)&client_info)->sin6_addr);
	    in_addrlen = sizeof(struct in6_addr);
	    sport = ntohs(((struct sockaddr_in6*)&client_info)->sin6_port);
	}

	if ( NULL == (he = gethostbyaddr(addrptr,in_addrlen,oldsockaddr.ss_family) ) )
	{
	    check_error(-1);
	    return -1;
	}

	strncpy(src_host,he->h_name,src_host_len);
	snprintf(src_service,src_service_len,"%u",sport);
# endif
    }

    return client_sfd;
}