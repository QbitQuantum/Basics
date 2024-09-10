int cli_url_canon(const char *inurl, size_t len, char *urlbuff, size_t dest_len, char **host, size_t *hostlen, const char **path, size_t *pathlen)
{
	char *url, *p, *last;
	char *host_begin, *path_begin;
	const char *urlend = urlbuff + len;
	size_t host_len, path_len;

	dest_len -= 3;
	strncpy(urlbuff, inurl, dest_len);
	urlbuff[dest_len] = urlbuff[dest_len+1] = urlbuff[dest_len+2] = '\0';
	url = urlbuff;

	/* canonicalize only real URLs, with a protocol */
	host_begin = strchr(url, ':');
	if(!host_begin)
		return CL_PHISH_CLEAN;
	++host_begin;

	/* ignore username in URL */
	while((host_begin < urlend) && *host_begin == '/') ++host_begin;
	host_len = strcspn(host_begin, ":/?");
	p = memchr(host_begin, '@', host_len);
	if (p)
	    host_begin = p+1;
	url = host_begin;
	/* repeatedly % unescape characters */
	str_hex_to_char(&url, &urlend);
	host_begin = url;
	len = urlend - url;
	/* skip to beginning of hostname */
	while((host_begin < urlend) && *host_begin == '/') ++host_begin;
	while(*host_begin == '.' && host_begin < urlend) ++host_begin;

	last = strchr(host_begin, '/');
	p = host_begin;
	while (p < urlend) {
	    if (p+2 < urlend && *p == '/' && p[1] == '.' ) {
		if (p[2] == '/') {
		    /* remove /./ */
		    if (p + 3 < urlend)
			memmove(p+1, p+3, urlend - p - 3);
		    urlend -= 2;
		}
		else if (p[2] == '.' && (p[3] == '/' || p[3] == '\0') && last) {
		    /* remove /component/../ */
		    if (p+4 < urlend)
			memmove(last+1, p+4, urlend - p - 4);
		    urlend -= 3 + (p - last);
		}
	    }
	    if (*p == '/')
		last = p;
	    p++;
	}
	p = &url[urlend - url];
	*p = '\0';

	p = host_begin;
	while (p < urlend && p+2 < url + dest_len && urlend < urlbuff+dest_len) {
	    unsigned char c = *p;
	    if (c <= 32 || c >= 127 || c == '%' || c == '#') {
		/* convert non-ascii characters back to % escaped */
		const char hexchars[] = "0123456789ABCDEF";
		memmove(p+3, p+1, urlend - p - 1);
		*p++ = '%';
		*p++ = hexchars[c>>4];
		*p = hexchars[c&0xf];
		urlend += 2;
	    }
	    p++;
	}
	*p = '\0';
	urlend = p;
	len = urlend - url;
	/* determine end of hostname */
	host_len = strcspn(host_begin, ":/?");
	path_begin = host_begin + host_len;
	if(host_len <= len) {
		/* url without path, use a single / */
		memmove(path_begin + 2, path_begin + 1, len - host_len);
		*path_begin++ = '/';
		*path_begin++ = '\0';
	} else path_begin = url+len;
	if(url + len >= path_begin) {
		path_len = url + len - path_begin + 1;
		p = strchr(path_begin, '#');
		if (p) {
		    /* ignore anchor */
		    *p = '\0';
		    path_len = p - path_begin;
		}
		*path = path_begin;
	} else {
		path_len = 0;
		*path = "";
	}
	/* lowercase entire URL */
	str_make_lowercase(host_begin, host_len);
	*host = host_begin;
	*hostlen = host_len;
	*pathlen = path_len;
	return CL_PHISH_NODECISION;
}