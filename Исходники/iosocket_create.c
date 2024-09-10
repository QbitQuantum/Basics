socket_struct *iosocket_create(char *sockaddr, uint4 bfsize, int file_des, boolean_t listen_specified)
{
	socket_struct		*socketptr;
	socket_struct		*prev_socketptr;
	socket_struct		*socklist_head;
	boolean_t		passive = FALSE;
	unsigned short		port;
	int			ii, save_errno, tmplen, errlen, sockaddrlen;
	char 			temp_addr[SA_MAXLITLEN], protocolstr[6], *adptr;
	const char		*errptr;
	struct addrinfo		*ai_ptr;
	struct addrinfo		hints, *addr_info_ptr = NULL;
#ifndef VMS
	struct sockaddr_un	*sa_un_ptr, sa_un_trans;
	mval			localpath;
	mstr			transpath;
	int			trans_status;
#endif
	enum socket_protocol	protocol;
	int			af;
	int			sd;
	int			errcode;
	char			host_buffer[NI_MAXHOST];
	char			port_buffer[NI_MAXSERV];
	int			port_buffer_len;
	int			colon_cnt, protooffset;
	char			*last_2colon = NULL;
	int			addrlen;
	GTM_SOCKLEN_TYPE	tmp_addrlen;

	if (0 > file_des)
	{	/* no socket descriptor yet */
		memset(&hints, 0, SIZEOF(hints));

		protooffset = colon_cnt = 0;
		sockaddrlen = STRLEN(sockaddr);
		for (ii = sockaddrlen - 1; 0 <= ii; ii--)
		{
			if (SEPARATOR == sockaddr[ii])
			{
				colon_cnt++;
				if (1 == colon_cnt)
					protooffset = ii + 1;
				else
				{
					last_2colon = &sockaddr[ii];
					break;
				}
			}
		}
		if (0 == colon_cnt)
		{
			rts_error_csa(CSA_ARG(NULL) VARLSTCNT(1) ERR_INVPORTSPEC);
			return NULL;
		}
		tmplen = sockaddrlen - protooffset;
		if (SIZEOF(protocolstr) <= tmplen)
		{	/* last piece just too big to be valid */
			rts_error_csa(CSA_ARG(NULL) VARLSTCNT(4) ERR_PROTNOTSUP, 2, tmplen , &sockaddr[protooffset]);
			return NULL;
		}
		lower_to_upper((uchar_ptr_t)protocolstr, (uchar_ptr_t)&sockaddr[protooffset], tmplen);
		if (((SIZEOF("TCP") - 1) == tmplen) && (0 == MEMCMP_LIT(protocolstr, "TCP")))
			protocol = socket_tcpip;
#		ifndef VMS
		else if (((SIZEOF("LOCAL") - 1) == tmplen) && (0 == MEMCMP_LIT(protocolstr, "LOCAL")))
			protocol = socket_local;
#		endif
		else
		{
			rts_error_csa(CSA_ARG(NULL) VARLSTCNT(4) ERR_PROTNOTSUP, 2, tmplen , &sockaddr[protooffset]);
			return NULL;
		}
		if (socket_tcpip == protocol)
		{
			if (1 == colon_cnt)
			{	/* for listening socket or broadcasting socket */
				if (!listen_specified || (SSCANF(sockaddr, PORT_PROTO_FORMAT, &port, protocolstr) < 2))
				{
					rts_error_csa(CSA_ARG(NULL) VARLSTCNT(1) ERR_INVPORTSPEC);
					return NULL;
				}
				passive = TRUE;
				/* We always first try using IPv6 address, if supported */
				af = ((GTM_IPV6_SUPPORTED && !ipv4_only) ? AF_INET6 : AF_INET);
				if (-1 == (sd = socket(af, SOCK_STREAM, IPPROTO_TCP)))
				{
					/* Try creating IPv4 socket */
					af = AF_INET;
					if (-1 == (sd = socket(af, SOCK_STREAM, IPPROTO_TCP)))
					{
						save_errno = errno;
						errptr = (char *)STRERROR(save_errno);
						errlen = STRLEN(errptr);
						rts_error_csa(CSA_ARG(NULL) VARLSTCNT(5) ERR_SOCKINIT, 3, save_errno,
							errlen, errptr);
						return NULL;
					}
				}
				SERVER_HINTS(hints, af);
				port_buffer_len = 0;
				I2A(port_buffer, port_buffer_len, port);
				port_buffer[port_buffer_len]='\0';
				if (0 != (errcode = getaddrinfo(NULL, port_buffer, &hints, &addr_info_ptr)))
				{
					close(sd);
					RTS_ERROR_ADDRINFO(NULL, ERR_GETADDRINFO, errcode);
					return NULL;
				}
				SOCKET_ALLOC(socketptr);
				socketptr->local.port = port;
				socketptr->temp_sd = sd;
				socketptr->sd = FD_INVALID;
				ai_ptr = &(socketptr->local.ai);
				memcpy(ai_ptr, addr_info_ptr, SIZEOF(struct addrinfo));
				SOCKET_AI_TO_LOCAL_ADDR(socketptr, addr_info_ptr);
				ai_ptr->ai_addr = SOCKET_LOCAL_ADDR(socketptr);
				ai_ptr->ai_addrlen = addr_info_ptr->ai_addrlen;
				ai_ptr->ai_next = NULL;
				freeaddrinfo(addr_info_ptr);
			} else
			{	/* connection socket */
				assert(2 == colon_cnt);
				if (listen_specified || (SSCANF(last_2colon + 1, PORT_PROTO_FORMAT, &port, protocolstr) < 2))
				{
					rts_error_csa(CSA_ARG(NULL) VARLSTCNT(1) ERR_INVADDRSPEC);
					return NULL;
				}
				/* for connection socket */
				SPRINTF(port_buffer, "%hu", port);
				addrlen = last_2colon - sockaddr;
				if ('[' == sockaddr[0])
				{
					if (NULL == memchr(sockaddr, ']', addrlen))
					{
						rts_error_csa(CSA_ARG(NULL) VARLSTCNT(1) ERR_INVADDRSPEC);
						return NULL;
					}
					addrlen -= 2;
					memcpy(temp_addr, &sockaddr[1], addrlen);
				} else
					memcpy(temp_addr, sockaddr, addrlen);
				temp_addr[addrlen] = 0;
				CLIENT_HINTS(hints);
				if (0 != (errcode = getaddrinfo(temp_addr, port_buffer, &hints, &addr_info_ptr)))
				{
					RTS_ERROR_ADDRINFO(NULL, ERR_GETADDRINFO, errcode);
					return NULL;
				}
				/*  we will test all address families in iosocket_connect() */
				SOCKET_ALLOC(socketptr);
				socketptr->remote.ai_head = addr_info_ptr;
				socketptr->remote.port = port;
				socketptr->sd = socketptr->temp_sd = FD_INVALID; /* don't mess with 0 */
			}
#		ifndef VMS
		} else if (socket_local == protocol)
		{	/* should we get_full_path first */
			/* check protooffset < sizeof sun_path */
			/* protooffset is after colon */
			SOCKET_ALLOC(socketptr);
			socketptr->protocol = socket_local;
			sa_un_ptr = malloc(SIZEOF(struct sockaddr_un));
			sa_un_ptr->sun_family = AF_UNIX;
			MV_INIT_STRING(&localpath, protooffset - 1, sockaddr);
			trans_status = TRANS_LOG_NAME(&localpath.str, &transpath, sa_un_trans.sun_path,
				(int)SIZEOF(sa_un_trans.sun_path), dont_sendmsg_on_log2long);
			if (SS_LOG2LONG == trans_status)
			{	/* if LOG2LONG, returned len not valid so report untranslated length */
				SOCKET_FREE(socketptr);
				rts_error_csa(CSA_ARG(NULL) VARLSTCNT(6) ERR_ADDRTOOLONG, 4, localpath.str.len, localpath.str.addr,
					localpath.str.len, SIZEOF(sa_un_trans.sun_path));
				return NULL;
			}
			memcpy(sa_un_ptr->sun_path, transpath.addr, transpath.len);
			sa_un_ptr->sun_path[transpath.len] = '\0';
			if (listen_specified)
			{
				passive = TRUE;
				socketptr->local.sa = (struct sockaddr *)sa_un_ptr;
				socketptr->local.ai.ai_family = AF_UNIX;
				socketptr->local.ai.ai_socktype = SOCK_STREAM;
				socketptr->local.ai.ai_addrlen = (size_t)((struct sockaddr_un *)0)->sun_path + protooffset;
				if (-1 == (sd = socket(AF_UNIX, SOCK_STREAM, 0)))
				{
					save_errno = errno;
					SOCKET_FREE(socketptr);
					errptr = (char *)STRERROR(save_errno);
					errlen = STRLEN(errptr);
					rts_error_csa(CSA_ARG(NULL) VARLSTCNT(5) ERR_SOCKINIT, 3, save_errno, errlen, errptr);
					return NULL;
				}
				socketptr->temp_sd = sd;
				socketptr->sd = FD_INVALID;
			} else
			{
				socketptr->remote.sa = (struct sockaddr *)sa_un_ptr;
				/* setup remote fields */
				socketptr->remote.ai.ai_family = AF_UNIX;
				socketptr->remote.ai.ai_socktype = SOCK_STREAM;
				socketptr->remote.ai.ai_addrlen = (size_t)((struct sockaddr_un *)0)->sun_path + protooffset;
				socketptr->sd = socketptr->temp_sd = FD_INVALID; /* don't mess with 0 */
			}
#		endif
		} else