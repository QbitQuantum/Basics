/**
 * Do all socket creation and initialization
 */
void create_sockets(void)
{
    struct addrinfo ai_hints, *ai_rval;
    int family, rval, fdflag, i;
#if (defined IPV6_RECVTCLASS || defined IP_RECVTCLASS || defined IP_RECVTOS) &&\
        !(defined WINDOWS && _WIN32_WINNT < _WIN32_WINNT_LONGHORN)
    int tosflag;
#endif

    family = AF_INET;
    for (i = 0; i < pub_multi_count; i++) {
        if (pub_multi[i].ss.ss_family == AF_INET6) {
            family = AF_INET6;
            break;
        }
    }

    if ((listener = socket(family, SOCK_DGRAM, 0)) == INVALID_SOCKET) {
        sockerror(0, 0, 0, "Error creating socket for listener");
        exit(ERR_SOCKET);
    }
#if (defined WINDOWS && _WIN32_WINNT >= _WIN32_WINNT_LONGHORN) ||\
        (!defined WINDOWS && !defined NO_DUAL)
    if (family == AF_INET6) {
        int v6flag = 0;
        if (setsockopt(listener, IPPROTO_IPV6, IPV6_V6ONLY, (char *)&v6flag,
                        sizeof(v6flag)) == SOCKET_ERROR) {
            sockerror(0, 0, 0, "Error setting v6only");
            closesocket(listener);
            exit(ERR_SOCKET);
        }
    }
#endif
    memset(&ai_hints, 0, sizeof(ai_hints));
    ai_hints.ai_family = family;
    ai_hints.ai_socktype = SOCK_DGRAM;
    ai_hints.ai_protocol = 0;
    ai_hints.ai_flags = AI_PASSIVE | AI_NUMERICSERV;
    if ((rval = getaddrinfo(NULL, portname, &ai_hints, &ai_rval)) != 0) {
        log0(0, 0, 0, "Error getting bind address: %s", gai_strerror(rval));
        exit(ERR_SOCKET);
    }
    if (bind(listener, ai_rval->ai_addr, ai_rval->ai_addrlen) == SOCKET_ERROR) {
        sockerror(0, 0, 0, "Error binding socket for listener");
        closesocket(listener);
        exit(ERR_SOCKET);
    }
    freeaddrinfo(ai_rval);
#ifdef WINDOWS
    fdflag = 1;
    if (ioctlsocket(listener, FIONBIO, &fdflag) == SOCKET_ERROR) {
        sockerror(0, 0, 0, "Error setting non-blocking option");
        closesocket(listener);
        exit(ERR_SOCKET);
    }
#else
    if ((fdflag = fcntl(listener, F_GETFL)) == SOCKET_ERROR) {
        sockerror(0, 0, 0, "Error getting socket descriptor flags");
        closesocket(listener);
        exit(ERR_SOCKET);
    }
    fdflag |= O_NONBLOCK;
    if (fcntl(listener, F_SETFL, fdflag) == SOCKET_ERROR) {
        sockerror(0, 0, 0, "Error setting non-blocking option");
        closesocket(listener);
        exit(ERR_SOCKET);
    }
#endif
    if (family == AF_INET6) {
#if defined IPV6_TCLASS && !defined WINDOWS
        if (setsockopt(listener, IPPROTO_IPV6, IPV6_TCLASS, (char *)&dscp,
                       sizeof(dscp)) == SOCKET_ERROR) {
            sockerror(0, 0, 0, "Error setting dscp");
            closesocket(listener);
            exit(ERR_SOCKET);
        }
#endif
#ifdef IPV6_RECVTCLASS
#if !(defined WINDOWS && _WIN32_WINNT < _WIN32_WINNT_LONGHORN)
        tosflag = 1;
        if (setsockopt(listener, IPPROTO_IPV6, IPV6_RECVTCLASS,
                       (char *)&tosflag, sizeof(tosflag)) == SOCKET_ERROR) {
            sockerror(0, 0, 0, "Error setting recv tos");
            closesocket(listener);
            exit(ERR_SOCKET);
       }
#endif
#endif
#ifdef IPV6_MTU_DISCOVER
        {
            int mtuflag = IP_PMTUDISC_DONT;
            if (setsockopt(listener, IPPROTO_IPV6, IPV6_MTU_DISCOVER,
                           (char *)&mtuflag, sizeof(mtuflag)) == SOCKET_ERROR) {
                sockerror(0, 0, 0, "Error disabling MTU discovery");
                closesocket(listener);
                exit(ERR_SOCKET);
            }
        }
#endif
    }
#if (defined WINDOWS && _WIN32_WINNT < _WIN32_WINNT_LONGHORN) ||\
        (defined NO_DUAL)
    if (family == AF_INET) {
#endif
        if (setsockopt(listener, IPPROTO_IP, IP_TOS, (char *)&dscp,
                       sizeof(dscp)) == SOCKET_ERROR) {
            sockerror(0, 0, 0, "Error setting dscp");
            closesocket(listener);
            exit(ERR_SOCKET);
        }
#ifdef IP_RECVTCLASS
#if !(defined WINDOWS && _WIN32_WINNT < _WIN32_WINNT_LONGHORN)
        tosflag = 1;
        if (setsockopt(listener, IPPROTO_IP, IP_RECVTCLASS, (char *)&tosflag,
                       sizeof(tosflag)) == SOCKET_ERROR) {
            sockerror(0, 0, 0, "Error setting recv tos");
            closesocket(listener);
            exit(ERR_SOCKET);
        }
#endif
#elif defined IP_RECVTOS
        tosflag = 1;
        if (setsockopt(listener, IPPROTO_IP, IP_RECVTOS, (char *)&tosflag,
                       sizeof(tosflag)) == SOCKET_ERROR) {
            sockerror(0, 0, 0, "Error setting recv tos");
            closesocket(listener);
            exit(ERR_SOCKET);
        }
#endif
#ifdef IP_MTU_DISCOVER
        {
            int mtuflag = IP_PMTUDISC_DONT;
            if (setsockopt(listener, IPPROTO_IP, IP_MTU_DISCOVER,
                    (char *)&mtuflag, sizeof(mtuflag)) == SOCKET_ERROR) {
                sockerror(0, 0, 0, "Error disabling MTU discovery");
                closesocket(listener);
                exit(ERR_SOCKET);
            }
        }
#endif
#if (defined WINDOWS && _WIN32_WINNT < _WIN32_WINNT_LONGHORN) ||\
        (defined NO_DUAL)
    }
#endif
    if (rcvbuf) {
        if (setsockopt(listener, SOL_SOCKET, SO_RCVBUF,
                       (char *)&rcvbuf, sizeof(rcvbuf)) == SOCKET_ERROR) {
            sockerror(0, 0, 0, "Error setting receive buffer size");
            exit(ERR_SOCKET);
        }
    } else {
        rcvbuf = DEF_RCVBUF;
        if (setsockopt(listener, SOL_SOCKET, SO_RCVBUF,
                       (char *)&rcvbuf, sizeof(rcvbuf)) == SOCKET_ERROR) {
            rcvbuf = DEF_BSD_RCVBUF;
            if (setsockopt(listener, SOL_SOCKET, SO_RCVBUF,
                           (char *)&rcvbuf, sizeof(rcvbuf)) == SOCKET_ERROR) {
                sockerror(0, 0, 0, "Error setting receive buffer size");
                exit(ERR_SOCKET);
            }
        }
    }
    for (i = 0; i < pub_multi_count; i++) {
        if (server_count > 0) {
            log3(0, 0, 0, "joining ssm for server IPs");
            if (!multicast_join(listener, 0, &pub_multi[i], m_interface,
                                interface_count, server_keys, server_count)) {
                exit(ERR_SOCKET);
            }
            if (has_proxy) {
                log3(0, 0, 0, "joining ssm for proxy IPs");
                if (!multicast_join(listener, 0, &pub_multi[i], m_interface,
                                    interface_count, &proxy_info, 1)) {
                    exit(ERR_SOCKET);
                }
            }
        } else {
            if (!multicast_join(listener, 0, &pub_multi[i], m_interface,
                                interface_count, NULL, 0)) {
                exit(ERR_SOCKET);
            }
        }
    }
}