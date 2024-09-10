static int socketevent_tcp_connect(lua_State *L) {
    // sock struct
    LSocketEventTCP *sock = luaL_checkudata(L, 1, LUA_SOCKETEVENT_TCP_HANDLE);

    // check connect state
    if (sock->state != 0) {
        socketevent_tcp_trigger_error(sock, sock->L, __LINE__, 6, "socket has connect");
        return 0;
    }
    sock->state++;

    // get params
    const char *host = luaL_checkstring(L, 2);
    lua_Integer port = luaL_checkinteger(L, 3);

#if defined(_WIN32)
    WSADATA wsa;
    // WinSock Startup
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        socketevent_tcp_trigger_error(sock, sock->L, __LINE__, 2, "c WSAStartup function error!");
        return 0;
    }
#endif

    sock->host = host;
    if (-1 == inet_addr(host)) {
        struct hostent *hostinfo;
        if ((hostinfo = (struct hostent*)gethostbyname(host)) == NULL) {
#if defined(_WIN32)
            socketevent_tcp_trigger_error(sock, sock->L, __LINE__, h_errno, hstrerror(h_errno));
#else
            socketevent_tcp_trigger_error(sock, sock->L, __LINE__, 18, "domain not found!");
#endif
            return 0;
        }
        if (hostinfo->h_addrtype == AF_INET && hostinfo->h_addr_list != NULL) {
#if defined(_WIN32)
            char ipstr[16];
            char * ipbyte = *(hostinfo->h_addr_list);
            sprintf(ipstr, "%d.%d.%d.%d", *ipbyte, *(ipbyte++), *(ipbyte+2), *(ipbyte+3));
            sock->ip = ipstr;
#else
            char ipstr[16];
            inet_ntop(hostinfo->h_addrtype, *(hostinfo->h_addr_list), ipstr, sizeof(ipstr));
            sock->ip = ipstr;
#endif
        } else {
            socketevent_tcp_trigger_error(sock, sock->L, __LINE__, 3, "not support ipv6!");
            return 0;
        }
    } else {
        sock->ip = host;
    }
    sock->port = port;

    // create socket
    if ((sock->socket = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        socketevent_tcp_trigger_error(sock, sock->L, __LINE__, errno, strerror(errno));
        return 0;
    }

#if defined(__linux__) || defined(__ANDROID__)
    // tcp option set
    if (sock->keepalive == 1) {
        if (setsockopt(sock->socket, SOL_SOCKET, SO_KEEPALIVE, (void *)&(sock->keepalive), sizeof(sock->keepalive)) < 0) {
            socketevent_tcp_trigger_error(sock, sock->L, __LINE__, errno, strerror(errno));
            return 0;
        }
        if (setsockopt(sock->socket, SOL_TCP, TCP_KEEPIDLE, (void *)&(sock->keepidle), sizeof(sock->keepidle)) < 0) {
            socketevent_tcp_trigger_error(sock, sock->L, __LINE__, errno, strerror(errno));
            return 0;
        }
        if (setsockopt(sock->socket, SOL_TCP, TCP_KEEPINTVL, (void *)&(sock->keepintvl), sizeof(sock->keepintvl)) < 0) {
            socketevent_tcp_trigger_error(sock, sock->L, __LINE__, errno, strerror(errno));
            return 0;
        }
        if (setsockopt(sock->socket, SOL_TCP, TCP_KEEPCNT, (void *)&(sock->keepcnt), sizeof(sock->keepcnt)) < 0) {
            socketevent_tcp_trigger_error(sock, sock->L, __LINE__, errno, strerror(errno));
            return 0;
        }
    }
#endif

    // start thread
#if defined(_WIN32)
    _beginthread(socketevent_tcp_data_win, 0, sock);
#else
    int retval = pthread_create(&sock->thread, NULL, socketevent_tcp_data, sock);
    if (retval != 0) {
        socketevent_tcp_trigger_error(sock, sock->L, __LINE__, retval, strerror(retval));
        return 0;
    }
#endif

    return 1;
}