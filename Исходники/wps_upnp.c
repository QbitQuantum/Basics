/* subscr_addr_add_url -- add address(es) for one url to subscription */
static void subscr_addr_add_url(struct subscription *s, const char *url,
				size_t url_len)
{
	int alloc_len;
	char *scratch_mem = NULL;
	char *mem;
	char *host;
	char *delim;
	char *path;
	int port = 80;  /* port to send to (default is port 80) */
	struct addrinfo hints;
	struct addrinfo *result = NULL;
	struct addrinfo *rp;
	int rerr;
	size_t host_len, path_len;

	/* url MUST begin with http: */
	if (url_len < 7 || os_strncasecmp(url, "http://", 7))
		goto fail;
	url += 7;
	url_len -= 7;

	/* Make a copy of the string to allow modification during parsing */
	scratch_mem = dup_binstr(url, url_len);
	if (scratch_mem == NULL)
		goto fail;
	wpa_printf(MSG_DEBUG, "WPS UPnP: Adding URL '%s'", scratch_mem);
	host = scratch_mem;
	path = os_strchr(host, '/');
	if (path)
		*path++ = '\0'; /* null terminate host */

	/* Process and remove optional port component */
	delim = os_strchr(host, ':');
	if (delim) {
		*delim = '\0'; /* null terminate host name for now */
		if (isdigit(delim[1]))
			port = atol(delim + 1);
	}

	/*
	 * getaddrinfo does the right thing with dotted decimal notations, or
	 * will resolve domain names. Resolving domain names will unfortunately
	 * hang the entire program until it is resolved or it times out
	 * internal to getaddrinfo; fortunately we think that the use of actual
	 * domain names (vs. dotted decimal notations) should be uncommon.
	 */
	os_memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_INET;      /* IPv4 */
	hints.ai_socktype = SOCK_STREAM;
#if NO_DOMAIN_NAME_RESOLUTION
	/* Suppress domain name resolutions that would halt
	 * the program for periods of time
	 */
	hints.ai_flags = AI_NUMERICHOST;
#else
	/* Allow domain name resolution. */
	hints.ai_flags = 0;
#endif
	hints.ai_protocol = 0;          /* Any protocol? */
	rerr = getaddrinfo(host, NULL /* fill in port ourselves */,
			   &hints, &result);
	if (rerr) {
		wpa_printf(MSG_INFO, "WPS UPnP: Resolve error %d (%s) on: %s",
			   rerr, gai_strerror(rerr), host);
		goto fail;
	}

	if (delim)
		*delim = ':'; /* Restore port */

	host_len = os_strlen(host);
	path_len = path ? os_strlen(path) : 0;
	alloc_len = host_len + 1 + 1 + path_len + 1;

	for (rp = result; rp; rp = rp->ai_next) {
		struct subscr_addr *a;

		/* Limit no. of address to avoid denial of service attack */
		if (dl_list_len(&s->addr_list) >= MAX_ADDR_PER_SUBSCRIPTION) {
			wpa_printf(MSG_INFO, "WPS UPnP: subscr_addr_add_url: "
				   "Ignoring excessive addresses");
			break;
		}

		a = os_zalloc(sizeof(*a) + alloc_len);
		if (a == NULL)
			break;
		mem = (char *) (a + 1);
		a->domain_and_port = mem;
		os_memcpy(mem, host, host_len);
		mem += host_len + 1;
		a->path = mem;
		if (path == NULL || path[0] != '/')
			*mem++ = '/';
		if (path)
			os_memcpy(mem, path, path_len);
		os_memcpy(&a->saddr, rp->ai_addr, sizeof(a->saddr));
		a->saddr.sin_port = htons(port);

		dl_list_add(&s->addr_list, &a->list);
	}

fail:
	if (result)
		freeaddrinfo(result);
	os_free(scratch_mem);
}