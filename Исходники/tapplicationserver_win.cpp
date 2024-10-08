/*!
  Listen a port with SO_REUSEADDR option.
  This function must be called in a tfserver process.
 */
int TApplicationServer::nativeListen(const QHostAddress &address, quint16 port, OpenFlag)
{
    int protocol = (address.protocol() == QAbstractSocket::IPv6Protocol) ? AF_INET6 : AF_INET;
    SOCKET sock = ::WSASocket(protocol, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);
    if (sock == INVALID_SOCKET) {
        tSystemError("WSASocket Error: %d", WSAGetLastError());
        return -1;
    }
    
    // ReuseAddr
    bool on = true;
    if (::setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (char *)&on, sizeof(on)) != 0) {
        tSystemError("setsockopt error: %d", WSAGetLastError());
        goto error_socket;
    }
    
    if (address.protocol() == QAbstractSocket::IPv6Protocol) {
        struct tf_in6_addr {
            quint8 tf_s6_addr[16];
        };
        struct tf_sockaddr_in6 {
            short   sin6_family;            /* AF_INET6 */
            quint16 sin6_port;              /* Transport level port number */
            quint32 sin6_flowinfo;          /* IPv6 flow information */
            struct  tf_in6_addr sin6_addr;  /* IPv6 address */
            quint32 sin6_scope_id;          /* set of interfaces for a scope */
        } sa6;
        
        memset(&sa6, 0, sizeof(sa6));
        sa6.sin6_family = AF_INET6;
        WSAHtons(sock, port, &(sa6.sin6_port));
        Q_IPV6ADDR ipv6 = address.toIPv6Address();
        memcpy(&(sa6.sin6_addr.tf_s6_addr), &ipv6, sizeof(ipv6));
        if (::bind(sock, (struct sockaddr *)&sa6, sizeof(sa6)) != 0) {
            tSystemError("bind(v6) error: %d", WSAGetLastError());
            goto error_socket;
        }
        
    } else if (address.protocol() == QAbstractSocket::IPv4Protocol
#if QT_VERSION >= 0x050000
               || address.protocol() == QAbstractSocket::QAbstractSocket::AnyIPProtocol
#endif
        ) {
        struct sockaddr_in sa;
        memset(&sa, 0, sizeof(sa));
        sa.sin_family = AF_INET;
        WSAHtons(sock, port, &(sa.sin_port));
        WSAHtonl(sock, address.toIPv4Address(), &(sa.sin_addr.s_addr));
        if (::bind(sock, (struct sockaddr *)&sa, sizeof(sa)) != 0) {
            tSystemError("bind error: %d", WSAGetLastError());
            goto error_socket;
        }
    } else {  // UnknownNetworkLayerProtocol
        goto error_socket;
    }
    
    if (::listen(sock, 50) != 0) {
        tSystemError("listen error: %d", WSAGetLastError());
        goto error_socket;
    }
    return sock;

error_socket:
    nativeClose(sock);
    return -1;
}