int nntp_connect(void)
{
    char                *q, *ipver = NULL, ipstr[INET6_ADDRSTRLEN], servport[10];
    struct addrinfo     hints, *res = NULL, *p;
    int                 rc;

    if (nntpsock != -1)
	return nntpsock;

    if (!strlen(CFG.nntpnode)) {
	WriteError("NNTP: host not configured");
	return -1;
    }
	
    snprintf(servport, 9, "%d", CFG.nntpport);
    Syslog('+', "NNTP: connecting host: %s port %s", CFG.nntpnode, servport);
    memset(&hints, 0, sizeof(hints));
    hints.ai_family   = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    if ((rc = getaddrinfo(CFG.nntpnode, servport, &hints, &res)) != 0) {
        WriteError("getaddrinfo %s:%s %s\n", CFG.nntpnode, servport, gai_strerror(rc));
        return -1;
    }

    for (p = res; p != NULL; p = p->ai_next) {
        void    *addr;

        if (p->ai_family == AF_INET) {
            struct sockaddr_in *ipv4 = (struct sockaddr_in *)p->ai_addr;
            addr = &(ipv4->sin_addr);
            ipver = (char *)"IPv4";
        } else {
            struct sockaddr_in6 *ipv6 = (struct sockaddr_in6 *)p->ai_addr;
            addr = &(ipv6->sin6_addr);
            ipver = (char *)"IPv6";
        }
        inet_ntop(p->ai_family, addr, ipstr, sizeof ipstr);
        Syslog('+', "Trying %s %s port %s", ipver, ipstr, servport);

        if ((nntpsock = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1) {
            WriteError("$socket()");
            return -1;
        } else {
            if (connect(nntpsock, p->ai_addr, p->ai_addrlen) == -1) {
                WriteError("$connect %s port %s", ipstr, servport);
                close(nntpsock);
            } else {
                break;
            }
        }
    }
    if (p == NULL) {
        return -1;      /* Not connected */
    }

    q = nntp_receive();
    if (strlen(q) == 0) {
	WriteError("NNTP: no response");
	nntp_close();
	return -1;
    }
    Syslog('+', "NNTP: %s", q);

    if ((strncmp(q, "480", 3) == 0) || CFG.nntpforceauth) {
	/*
	 *  Must login with username and password
	 */
	if (nntp_auth() == FALSE) {
	    WriteError("Authorisation failure");
	    nntp_close();
	    return -1;
	}
    } else if (strncmp(q, "200", 3)) {
	WriteError("NNTP: bad response: %s", q);
//		nntp_close();  FIXME: Don't close, the other end might have done that already
		//		      If we do also, this program hangs. Must be fixed!
	return -1;
    }

    if (CFG.modereader) {
	Syslog('+', "NNTP: setting mode reader");
	nntp_send((char *)"MODE READER\r\n");
	q = nntp_receive();
	Syslog('+', "NNTP: %s", q);
	if (strncmp(q, "480", 3) == 0) {
	    /*
	     *  Must login with username and password
	     */
	    Syslog('+', "NNTP: %s", q);
	    if (nntp_auth() == FALSE) {
		WriteError("NNTP: authorisation failure");
		nntp_close();
		return -1;
	    }
	} else if (strncmp(q, "200", 3)) {
	    WriteError("NNTP: bad response: %s", q);
	    nntp_close();
	    return -1;
	}
    }
    return nntpsock;
}