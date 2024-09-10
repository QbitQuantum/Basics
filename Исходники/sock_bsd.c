/*
 * Convert IPv4/IPv6 address to text.
 */
PJ_DEF(pj_status_t) pj_inet_ntop(int af, const void *src,
				 char *dst, int size)

{
    PJ_ASSERT_RETURN(src && dst && size, PJ_EINVAL);

    *dst = '\0';

    PJ_ASSERT_RETURN(af==PJ_AF_INET || af==PJ_AF_INET6, PJ_EAFNOTSUP);

#if defined(PJ_SOCK_HAS_INET_NTOP) && PJ_SOCK_HAS_INET_NTOP != 0
    /*
     * Implementation using inet_ntop()
     */
    if (inet_ntop(af, src, dst, size) == NULL) {
	pj_status_t status = pj_get_netos_error();
	if (status == PJ_SUCCESS)
	    status = PJ_EUNKNOWN;

	return status;
    }

    return PJ_SUCCESS;

#elif defined(PJ_WIN32) || defined(PJ_WIN32_WINCE)
    /*
     * Implementation on Windows, using WSAAddressToString().
     * Should also work on Unicode systems.
     */
    {
	PJ_DECL_UNICODE_TEMP_BUF(wtempaddr,PJ_INET6_ADDRSTRLEN)
	pj_sockaddr sock_addr;
	DWORD addr_len, addr_str_len;
	int rc;

	pj_bzero(&sock_addr, sizeof(sock_addr));
	sock_addr.addr.sa_family = (pj_uint16_t)af;
	if (af == PJ_AF_INET) {
	    if (size < PJ_INET_ADDRSTRLEN)
		return PJ_ETOOSMALL;
	    pj_memcpy(&sock_addr.ipv4.sin_addr, src, 4);
	    addr_len = sizeof(pj_sockaddr_in);
	    addr_str_len = PJ_INET_ADDRSTRLEN;
	} else if (af == PJ_AF_INET6) {
	    if (size < PJ_INET6_ADDRSTRLEN)
		return PJ_ETOOSMALL;
	    pj_memcpy(&sock_addr.ipv6.sin6_addr, src, 16);
	    addr_len = sizeof(pj_sockaddr_in6);
	    addr_str_len = PJ_INET6_ADDRSTRLEN;
	} else {
	    pj_assert(!"Unsupported address family");
	    return PJ_EAFNOTSUP;
	}

#if PJ_NATIVE_STRING_IS_UNICODE
	rc = WSAAddressToString((LPSOCKADDR)&sock_addr, addr_len,
				NULL, wtempaddr, &addr_str_len);
	if (rc == 0) {
	    pj_unicode_to_ansi(wtempaddr, wcslen(wtempaddr), dst, size);
	}
#else
	rc = WSAAddressToString((LPSOCKADDR)&sock_addr, addr_len,
				NULL, dst, &addr_str_len);
#endif

	if (rc != 0) {
	    pj_status_t status = pj_get_netos_error();
	    if (status == PJ_SUCCESS)
		status = PJ_EUNKNOWN;

	    return status;
	}

	return PJ_SUCCESS;
    }

#elif !defined(PJ_HAS_IPV6) || PJ_HAS_IPV6==0
    /* IPv6 support is disabled, just return error without raising assertion */
    return PJ_EIPV6NOTSUP;
#else
    pj_assert(!"Not supported");
    return PJ_EIPV6NOTSUP;
#endif
}