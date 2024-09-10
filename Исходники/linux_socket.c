/*
 * Reads a linux sockaddr and does any necessary translation.
 * Linux sockaddrs don't have a length field, only a family.
 * Copy the osockaddr structure pointed to by osa to kernel, adjust
 * family and convert to sockaddr.
 */
static int
linux_getsockaddr(struct sockaddr **sap, const struct osockaddr *osa, int salen)
{
	struct sockaddr *sa;
	struct osockaddr *kosa;
#ifdef INET6
	struct sockaddr_in6 *sin6;
	int oldv6size;
#endif
	char *name;
	int bdom, error, hdrlen, namelen;

	if (salen < 2 || salen > UCHAR_MAX || !osa)
		return (EINVAL);

#ifdef INET6
	oldv6size = 0;
	/*
	 * Check for old (pre-RFC2553) sockaddr_in6. We may accept it
	 * if it's a v4-mapped address, so reserve the proper space
	 * for it.
	 */
	if (salen == sizeof(struct sockaddr_in6) - sizeof(uint32_t)) {
		salen += sizeof(uint32_t);
		oldv6size = 1;
	}
#endif

	kosa = malloc(salen, M_SONAME, M_WAITOK);

	if ((error = copyin(osa, kosa, salen)))
		goto out;

	bdom = linux_to_bsd_domain(kosa->sa_family);
	if (bdom == -1) {
		error = EAFNOSUPPORT;
		goto out;
	}

#ifdef INET6
	/*
	 * Older Linux IPv6 code uses obsolete RFC2133 struct sockaddr_in6,
	 * which lacks the scope id compared with RFC2553 one. If we detect
	 * the situation, reject the address and write a message to system log.
	 *
	 * Still accept addresses for which the scope id is not used.
	 */
	if (oldv6size) {
		if (bdom == AF_INET6) {
			sin6 = (struct sockaddr_in6 *)kosa;
			if (IN6_IS_ADDR_V4MAPPED(&sin6->sin6_addr) ||
			    (!IN6_IS_ADDR_LINKLOCAL(&sin6->sin6_addr) &&
			     !IN6_IS_ADDR_SITELOCAL(&sin6->sin6_addr) &&
			     !IN6_IS_ADDR_V4COMPAT(&sin6->sin6_addr) &&
			     !IN6_IS_ADDR_UNSPECIFIED(&sin6->sin6_addr) &&
			     !IN6_IS_ADDR_MULTICAST(&sin6->sin6_addr))) {
				sin6->sin6_scope_id = 0;
			} else {
				log(LOG_DEBUG,
				    "obsolete pre-RFC2553 sockaddr_in6 rejected\n");
				error = EINVAL;
				goto out;
			}
		} else
			salen -= sizeof(uint32_t);
	}
#endif
	if (bdom == AF_INET) {
		if (salen < sizeof(struct sockaddr_in)) {
			error = EINVAL;
			goto out;
		}
		salen = sizeof(struct sockaddr_in);
	}

	if (bdom == AF_LOCAL && salen > sizeof(struct sockaddr_un)) {
		hdrlen = offsetof(struct sockaddr_un, sun_path);
		name = ((struct sockaddr_un *)kosa)->sun_path;
		if (*name == '\0') {
			/*
		 	 * Linux abstract namespace starts with a NULL byte.
			 * XXX We do not support abstract namespace yet.
			 */
			namelen = strnlen(name + 1, salen - hdrlen - 1) + 1;
		} else
			namelen = strnlen(name, salen - hdrlen);
		salen = hdrlen + namelen;
		if (salen > sizeof(struct sockaddr_un)) {
			error = ENAMETOOLONG;
			goto out;
		}
	}