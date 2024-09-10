bool netif_str_to_addr(struct sockaddr_storage *out, int *addr_len,
		const char *addr)
{
	bool ipv6;

	memset(out, 0, sizeof(*out));
	*addr_len = 0;

	if (!addr)
		return false;

	ipv6 = (strchr(addr, ':') != NULL);
	out->ss_family = ipv6 ? AF_INET6 : AF_INET;
	*addr_len = sizeof(*out);

#ifdef _WIN32
	int ret = WSAStringToAddressA((LPSTR)addr, out->ss_family, NULL,
			(LPSOCKADDR)out, addr_len);
	if (ret == SOCKET_ERROR)
		warn("Could not parse address, error code: %d", GetLastError());
	return ret != SOCKET_ERROR;
#else
	struct sockaddr_in *sin = (struct sockaddr_in *)out;
	if (inet_pton(out->ss_family, addr, &sin->sin_addr)) {
		*addr_len = ipv6 ?
			sizeof(struct sockaddr_in6) :
			sizeof(struct sockaddr_in);
		return true;
	}

	return false;
#endif
}