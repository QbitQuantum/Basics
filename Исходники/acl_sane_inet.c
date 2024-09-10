size_t acl_inet_ntop(const struct sockaddr *sa, char *buf, size_t size)
{
	if (sa->sa_family == AF_INET) {
		int    port;
		char   ip[IPLEN];
		struct sockaddr_in *in = (struct sockaddr_in*) sa;

		if (!inet_ntop(sa->sa_family, &in->sin_addr, ip, IPLEN)) {
			return 0;
		}

		port = ntohs(in->sin_port);
		if (port > 0) {
			snprintf(buf, size, "%s:%d", ip, port);
		} else {
			snprintf(buf, size, "%s", ip);
		}
		return sizeof(struct sockaddr_in);
#ifdef AF_INET6
	} else if (sa->sa_family == AF_INET6) {
		int    port;
		char   ip[IPLEN], ifname[IF_NAMESIZE], *ptr;
		struct sockaddr_in6 *in6 = (struct sockaddr_in6*) sa;

		if (!inet_ntop(sa->sa_family, &in6->sin6_addr, ip, IPLEN)) {
			return 0;
		}

		ptr = if_indextoname(in6->sin6_scope_id, ifname);
		if (ptr == NULL) {
			ifname[0] = 0;
		}
		port = ntohs(in6->sin6_port);
		if (port <= 0) {
			if (strcmp(ip, "::1") == 0) {
				snprintf(buf, size, "%s", ip);
			} else if (ifname[0] != 0) {
				snprintf(buf, size, "%s%%%s", ip, ifname);
			} else {
				snprintf(buf, size, "%s", ip);
			}
		} else if (strcmp(ip, "::1") == 0) {  /* for local IPV6 */
			snprintf(buf, size, "%s%c%d", ip, ACL_ADDR_SEP, port);
		} else if (ifname[0] != 0) {
			snprintf(buf, size, "%s%%%s%c%d",
				ip, ifname, ACL_ADDR_SEP, port);
		} else {
			snprintf(buf, size, "%s%c%d", ip, ACL_ADDR_SEP, port);
		}

		return sizeof(struct sockaddr_in6);
#endif
#ifdef ACL_UNIX
	} else if (sa->sa_family == AF_UNIX) {
		struct sockaddr_un *un = (struct sockaddr_un *) sa;

		ACL_SAFE_STRNCPY(buf, un->sun_path, size);
		return sizeof(struct sockaddr_un);
#endif
	} else {
		return 0;
	}
}