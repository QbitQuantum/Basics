/*
 * Get IPv4 source filter list in use on socket.
 *
 * Stubbed to getsourcefilter(). Performs conversion of structures which
 * may be inefficient; applications are encouraged to use the
 * protocol-independent API.
 * An slist of NULL may be used for guessing the required buffer size.
 */
int getipv4sourcefilter(int s, struct in_addr interface, struct in_addr group,
	uint32_t *fmode, uint32_t *numsrc, struct in_addr *slist)
{
	sockunion_t	*psu, *tmpslist;
	sockunion_t	 tmpgroup;
	struct in_addr	*pina;
	int		 err;
	size_t		 i;
	uint32_t	 ifindex, onumsrc;

	assert(s != -1);
	assert(fmode != NULL);
	assert(numsrc != NULL);

	onumsrc = *numsrc;
	*numsrc = 0;
	tmpslist = NULL;

	if (!IN_MULTICAST(ntohl(group.s_addr)) ||
		(onumsrc != 0 && slist == NULL))
	{
		errno = EINVAL;
		return (-1);
	}

	ifindex = __inaddr_to_index(interface.s_addr);

	if (ifindex == 0)
	{
		errno = EADDRNOTAVAIL;
		return (-1);
	}

	memset(&tmpgroup, 0, sizeof(sockunion_t));
	tmpgroup.sin.sin_family = AF_INET;
	tmpgroup.sin.sin_len = sizeof(struct sockaddr_in);
	tmpgroup.sin.sin_addr = group;

	if (onumsrc != 0 || slist != NULL)
	{
		tmpslist = calloc(onumsrc, sizeof(sockunion_t));

		if (tmpslist == NULL)
		{
			errno = ENOMEM;
			return (-1);
		}
	}

	err = getsourcefilter(s, ifindex, (struct sockaddr *)&tmpgroup,
		sizeof(struct sockaddr_in), fmode, numsrc,
		(struct sockaddr_storage *)tmpslist);

	if (tmpslist != NULL && *numsrc != 0)
	{
		pina = slist;
		psu = tmpslist;

		for (i = 0; i < MIN(onumsrc, *numsrc); i++, psu++)
		{
			if (psu->ss.ss_family != AF_INET)
				continue;
			*pina++ = psu->sin.sin_addr;
		}

		free(tmpslist);
	}

	return (err);
}