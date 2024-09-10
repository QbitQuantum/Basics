static int
smux_socket (void)
{
    int ret;
#ifdef HAVE_IPV6
    struct addrinfo hints, *res0, *res;
    int gai;
#else
    struct sockaddr_in serv;
    struct servent *sp;
#endif
    int sock = 0;

#ifdef HAVE_IPV6
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = PF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    gai = getaddrinfo(NULL, "smux", &hints, &res0);
    if (gai == EAI_SERVICE)
    {
        char servbuf[NI_MAXSERV];
        sprintf(servbuf,"%d",SMUX_PORT_DEFAULT);
        servbuf[sizeof (servbuf) - 1] = '\0';
        gai = getaddrinfo(NULL, servbuf, &hints, &res0);
    }
    if (gai)
    {
        zlog_warn("Cannot locate loopback service smux");
        return -1;
    }
    for(res=res0; res; res=res->ai_next)
    {
        if (res->ai_family != AF_INET
#ifdef HAVE_IPV6
                && res->ai_family != AF_INET6
#endif /* HAVE_IPV6 */
           )
            continue;

        sock = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
        if (sock < 0)
            continue;
        sockopt_reuseaddr (sock);
        sockopt_reuseport (sock);
        ret = connect (sock, res->ai_addr, res->ai_addrlen);
        if (ret < 0)
        {
            close(sock);
            sock = -1;
            continue;
        }
        break;
    }
    freeaddrinfo(res0);
    if (sock < 0 && debug_smux)
        zlog_warn ("Can't connect to SNMP agent with SMUX");
#else
    sock = socket (AF_INET, SOCK_STREAM, 0);
    if (sock < 0)
    {
        zlog_warn ("Can't make socket for SNMP");
        return -1;
    }

    memset (&serv, 0, sizeof (struct sockaddr_in));
    serv.sin_family = AF_INET;
#ifdef HAVE_STRUCT_SOCKADDR_IN_SIN_LEN
    serv.sin_len = sizeof (struct sockaddr_in);
#endif /* HAVE_STRUCT_SOCKADDR_IN_SIN_LEN */

    sp = getservbyname ("smux", "tcp");
    if (sp != NULL)
        serv.sin_port = sp->s_port;
    else
        serv.sin_port = htons (SMUX_PORT_DEFAULT);

    serv.sin_addr.s_addr = htonl (INADDR_LOOPBACK);

    sockopt_reuseaddr (sock);
    sockopt_reuseport (sock);

    ret = connect (sock, (struct sockaddr *) &serv, sizeof (struct sockaddr_in));
    if (ret < 0)
    {
        close (sock);
        smux_sock = -1;
        if (debug_smux)
            zlog_warn ("Can't connect to SNMP agent with SMUX");
        return -1;
    }
#endif
    return sock;
}