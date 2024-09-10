/*
    Extracts the port and address from a sockaddr, and stores them in
    \a port and \a addr if they are non-null.
*/
static inline void qt_socket_getPortAndAddress(SOCKET socketDescriptor, struct sockaddr *sa, quint16 *port, QHostAddress *address)
{
#if !defined (QT_NO_IPV6)
    if (sa->sa_family == AF_INET6) {
        qt_sockaddr_in6 *sa6 = (qt_sockaddr_in6 *)sa;
        Q_IPV6ADDR tmp;
        for (int i = 0; i < 16; ++i)
            tmp.c[i] = sa6->sin6_addr.qt_s6_addr[i];
        QHostAddress a;
	a.setAddress(tmp);
	if (address)
	    *address = a;
        if (port)
	    WSANtohs(socketDescriptor, sa6->sin6_port, port);
    } else
#endif
    if (sa->sa_family == AF_INET) {
        struct sockaddr_in *sa4 = (struct sockaddr_in *)sa;
        unsigned long addr;
        WSANtohl(socketDescriptor, sa4->sin_addr.s_addr, &addr);
        QHostAddress a;
	a.setAddress(addr);
	if (address)
	    *address = a;
        if (port)
	    WSANtohs(socketDescriptor, sa4->sin_port, port);
    }
}