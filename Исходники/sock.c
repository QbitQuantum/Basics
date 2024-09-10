int get_host_addr(void *addr, unsigned int addrlen, const char *host, unsigned short port)
{
	struct addrinfo hint = {0};
	struct addrinfo *addrlink = NULL;
	struct addrinfo *tmp = NULL;
	unsigned short *lpport = (unsigned short *)((char*)addr + 1 + sizeof(unsigned short));
	hint.ai_flags = AI_CANONNAME;

	if(getaddrinfo(host, NULL, &hint, &addrlink) != 0) {
		return -1;
	}

	for(tmp = addrlink; tmp != NULL; tmp = tmp->ai_next) {
		if(tmp->ai_family == AF_INET6) {
			if(IN6_IS_ADDR_MULTICAST(&((struct sockaddr_in6 *)tmp->ai_addr)->sin6_addr)
				|| IN6_IS_ADDR_LINKLOCAL(&((struct sockaddr_in6 *)tmp->ai_addr)->sin6_addr)
				|| IN6_IS_ADDR_SITELOCAL(&((struct sockaddr_in6 *)tmp->ai_addr)->sin6_addr)
				|| IN6_IS_ADDR_V4MAPPED(&((struct sockaddr_in6 *)tmp->ai_addr)->sin6_addr)
				|| IN6_IS_ADDR_V4COMPAT(&((struct sockaddr_in6 *)tmp->ai_addr)->sin6_addr) ) {
				continue;
			}
		} 

		((char*)addr)[0] = (char)(tmp->ai_addrlen > addrlen ? addrlen : tmp->ai_addrlen);
		memcpy((char*)addr+1, tmp->ai_addr, ((char*)addr)[0]);
		*lpport = htons(port);
		break;
	}

	freeaddrinfo(addrlink);
	return 0;
}