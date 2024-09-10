int
im_udp_read(struct i_module *im, int infd, struct im_msg *ret)
{
	struct sockaddr_in	 frominet;
	struct im_udp_ctx	*c;
	char			*p;
	int			 slen;

	if (ret == NULL) {
		m_dprintf(MSYSLOG_SERIOUS, "im_udp: arg is null\n");
		return (-1);
	}

	ret->im_pid = -1;
	ret->im_pri = -1;
	ret->im_flags = 0;

	slen = sizeof(frominet);
	if ((ret->im_len = recvfrom(im->im_fd, ret->im_msg,
	    sizeof(ret->im_msg) - 1, 0, (struct sockaddr *)&frominet,
	    (socklen_t *)&slen)) < 1) {
		if (ret->im_len < 0 && errno != EINTR)
			logerror("recvfrom inet");
		return (1);
	}

	ret->im_msg[ret->im_len] = '\0';

	c = (struct im_udp_ctx *) im->im_ctx;

	/* change non printable chars to X, just in case */
	for(p = ret->im_msg; *p != '\0'; p++)
		if (!isprint((unsigned int) *p) && *p != '\n')
			*p = 'X';

	if (c->flags & M_USEMSGHOST) {
		char	host[90];
		int	n1, n2;

		n1 = 0;
		n2 = 0;
		/* extract hostname from message */
		if ((sscanf(ret->im_msg, "<%*d>%*3s %*i %*i:%*i:%*i %n%89s "
		    "%n%*s", &n1, host, &n2) != 1 &&
		    sscanf(ret->im_msg, "%*3s %*i %*i:%*i:%*i %n%89s %n%*s",
		    &n1, host, &n2) != 1 &&
		    sscanf(ret->im_msg, "%n%89s %n%*s", &n1, host,
		    &n2) != 1) ||
		    ret->im_msg[n2] == '\0') {
			m_dprintf(MSYSLOG_INFORMATIVE, "im_udp_read: skipped"
			    " invalid message [%s]\n", ret->im_msg);
			return (0);
		}

		if (ret->im_msg[n2] == '\0')
			return (0);

		/* remove host from message */
		while (ret->im_msg[n2] != '\0')
			ret->im_msg[n1++] = ret->im_msg[n2++];
		ret->im_msg[n1] = '\0';

		strncpy(ret->im_host, host, sizeof(ret->im_host) - 1);
		ret->im_host[sizeof(ret->im_host) - 1] = '\0';

	} else {
		struct hostent *hent;

		hent = gethostbyaddr((char *) &frominet.sin_addr,
		    sizeof(frominet.sin_addr), frominet.sin_family);
		if (hent) {
			strncpy(ret->im_host, hent->h_name,
			    sizeof(ret->im_host) - 1);
		} else {
			strncpy(ret->im_host, inet_ntoa(frominet.sin_addr),
			    sizeof(ret->im_host) - 1);
		}
	}

	ret->im_host[sizeof(ret->im_host) - 1] = '\0';

	if (c->flags & M_NOTFQDN) {
		char     *dot;

		if ((dot = strchr(ret->im_host, '.')) != NULL)
			*dot = '\0';
	}

	return (1);
}