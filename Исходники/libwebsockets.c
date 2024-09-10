LWS_VISIBLE int
libwebsockets_get_addresses(struct libwebsocket_context *context,
			    void *ads, char *name, int name_len,
			    char *rip, int rip_len)
{
	struct addrinfo ai, *res;
	void *p = NULL;

	rip[0] = '\0';
	name[0] = '\0';

#ifdef LWS_USE_IPV6
	if (LWS_IPV6_ENABLED(context)) {
		if (!lws_plat_inet_ntop(AF_INET6, &((struct sockaddr_in6 *)ads)->sin6_addr, rip, rip_len)) {
			lwsl_err("inet_ntop", strerror(LWS_ERRNO));
			return -1;
		}

		// Strip off the IPv4 to IPv6 header if one exists
		if (strncmp(rip, "::ffff:", 7) == 0)
			memmove(rip, rip + 7, strlen(rip) - 6);

		getnameinfo((struct sockaddr *)ads,
				sizeof(struct sockaddr_in6), name,
							name_len, NULL, 0, 0);
		
		return 0;
	} else
#endif
	{
		memset(&ai, 0, sizeof ai);
		ai.ai_family = PF_UNSPEC;
		ai.ai_socktype = SOCK_STREAM;
		ai.ai_flags = AI_CANONNAME;

		if (getnameinfo((struct sockaddr *)ads,
				sizeof(struct sockaddr_in),
				name, name_len, NULL, 0, 0))
			return -1;

		if (!rip)
			return 0;

		if (getaddrinfo(name, NULL, &ai, &res))
			return -1;

		while (!p && res) {
			switch (res->ai_family) {
			case AF_INET:
				p = &((struct sockaddr_in *)res->ai_addr)->sin_addr;
				break;
			}

			res = res->ai_next;
		}
	}

	if (!p)
		return -1;

	lws_plat_inet_ntop(AF_INET, p, rip, rip_len);

	return 0;
}