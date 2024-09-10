struct sockaddr *
_SC_string_to_sockaddr(const char *str, sa_family_t af, void *buf, size_t bufLen)
{
	union {
		void			*buf;
		struct sockaddr		*sa;
		struct sockaddr_in	*sin;
		struct sockaddr_in6	*sin6;
	} addr;

	if (buf == NULL) {
		bufLen = sizeof(struct sockaddr_storage);
		addr.buf = CFAllocatorAllocate(NULL, bufLen, 0);
	} else {
		addr.buf = buf;
	}

	bzero(addr.buf, bufLen);
	if (((af == AF_UNSPEC) || (af == AF_INET)) &&
	    (bufLen >= sizeof(struct sockaddr_in)) &&
	    inet_aton(str, &addr.sin->sin_addr) == 1) {
		// if IPv4 address
		addr.sin->sin_len    = sizeof(struct sockaddr_in);
		addr.sin->sin_family = AF_INET;
	} else if (((af == AF_UNSPEC) || (af == AF_INET6)) &&
		   (bufLen >= sizeof(struct sockaddr_in6)) &&
		   inet_pton(AF_INET6, str, &addr.sin6->sin6_addr) == 1) {
		// if IPv6 address
		char	*p;

		addr.sin6->sin6_len    = sizeof(struct sockaddr_in6);
		addr.sin6->sin6_family = AF_INET6;

		p = strchr(buf, '%');
		if (p != NULL) {
			addr.sin6->sin6_scope_id = if_nametoindex(p + 1);
		}

		if (IN6_IS_ADDR_LINKLOCAL(&addr.sin6->sin6_addr) ||
		    IN6_IS_ADDR_MC_LINKLOCAL(&addr.sin6->sin6_addr)) {
			uint16_t	if_index;

			if_index = ntohs(addr.sin6->sin6_addr.__u6_addr.__u6_addr16[1]);
			addr.sin6->sin6_addr.__u6_addr.__u6_addr16[1] = 0;
			if (addr.sin6->sin6_scope_id == 0) {
				// use the scope id that was embedded in the [link local] IPv6 address
				addr.sin6->sin6_scope_id = if_index;
			}
		}
	} else {
		if (addr.buf != buf) {
			CFAllocatorDeallocate(NULL, addr.buf);
		}
		addr.buf = NULL;
	}

	return addr.sa;
}