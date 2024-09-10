char *
sockaddr_to_string(const struct sockaddr *sa, size_t length, GError **error)
{
#if defined(HAVE_IPV6) && defined(IN6_IS_ADDR_V4MAPPED)
	const struct sockaddr_in6 *a6 = (const struct sockaddr_in6 *)sa;
	struct sockaddr_in a4;
#endif
	int ret;
	char host[NI_MAXHOST], serv[NI_MAXSERV];

#if defined(HAVE_IPV6) && defined(IN6_IS_ADDR_V4MAPPED)
	if (sa->sa_family == AF_INET6 &&
	    IN6_IS_ADDR_V4MAPPED(&a6->sin6_addr)) {
		/* convert "::ffff:127.0.0.1" to "127.0.0.1" */

		memset(&a4, 0, sizeof(a4));
		a4.sin_family = AF_INET;
		memcpy(&a4.sin_addr, ((const char *)&a6->sin6_addr) + 12,
		       sizeof(a4.sin_addr));
		a4.sin_port = a6->sin6_port;

		sa = (const struct sockaddr *)&a4;
		length = sizeof(a4);
	}
#endif

	ret = getnameinfo(sa, length, host, sizeof(host), serv, sizeof(serv),
			  NI_NUMERICHOST|NI_NUMERICSERV);
	if (ret != 0) {
		g_set_error(error, g_quark_from_static_string("netdb"), ret,
			    "%s", gai_strerror(ret));
		return NULL;
	}

#ifdef HAVE_UN
	if (sa->sa_family == AF_UNIX)
		/* "serv" contains corrupt information with unix
		   sockets */
		return g_strdup(host);
#endif

#ifdef HAVE_IPV6
	if (strchr(host, ':') != NULL)
		return g_strconcat("[", host, "]:", serv, NULL);
#endif

	return g_strconcat(host, ":", serv, NULL);
}