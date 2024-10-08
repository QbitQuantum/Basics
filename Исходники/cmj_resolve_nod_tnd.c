cmi_status_t cmj_resolve_nod_tnd(cmi_descriptor *nod, cmi_descriptor *tnd, struct sockaddr_in *inp)
{
	cmi_status_t status = SS_NORMAL;
	char hn[MAX_HOST_NAME_LEN];
	struct hostent *hp;
	int loop_limit = MAX_GETHOST_TRIES;

	/* tnd may contain host:port */
	status = cmj_getsockaddr(tnd, inp);
	if (CMI_ERROR(status))
		return status;

	if (inp->sin_addr.s_addr == INADDR_ANY)
	{
		/* use nod as a host name if tnd was just a port */
		assert(CMI_DESC_LENGTH(nod) < (SIZEOF(hn)-1));
		memcpy(hn, CMI_DESC_POINTER(nod), CMI_DESC_LENGTH(nod));
		hn[CMI_DESC_LENGTH(nod)] = '\0';

		/* test to see if nod is a dotted quad text string */
		inp->sin_addr.s_addr = INET_ADDR(hn);
		if (inp->sin_addr.s_addr == (in_addr_t)-1)
		{
			/* assume hn is a host and query netdb */
			for (; 0 < loop_limit && (NULL == (hp = GETHOSTBYNAME(hn))) && TRY_AGAIN == h_errno; loop_limit--)
				;
			endhostent();
			if (!hp)
				return CMI_NETFAIL;
			inp->sin_addr = *(struct in_addr *)hp->h_addr;
		}
	}
	return status;
}