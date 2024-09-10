int
__yp_ping(struct in_addr *restricted_addrs, int cnt, char *dom, short *port)
{
	struct timeval		tv = { 5, 0 };
	struct ping_req		**reqs;
	unsigned long		i;
	int			async;
	struct sockaddr_in	sin, *any = NULL;
	struct netbuf		addr;
	int			winner = -1;
	u_int32_t		xid_seed, xid_lookup;
	int			sock, dontblock = 1;
	CLIENT			*clnt;
	char			*foo = dom;
	int			validsrvs = 0;

	/* Set up handles. */
	reqs = calloc(1, sizeof(struct ping_req *) * cnt);
	xid_seed = time(NULL) ^ getpid();

	for (i = 0; i < cnt; i++) {
		bzero((char *)&sin, sizeof(sin));
		sin.sin_family = AF_INET;
		bcopy((char *)&restricted_addrs[i],
			(char *)&sin.sin_addr, sizeof(struct in_addr));
		sin.sin_port = htons(__pmap_getport(&sin, YPPROG,
					YPVERS, IPPROTO_UDP));
		if (sin.sin_port == 0)
			continue;
		reqs[i] = calloc(1, sizeof(struct ping_req));
		bcopy((char *)&sin, (char *)&reqs[i]->sin, sizeof(sin));
		any = &reqs[i]->sin;
		reqs[i]->xid = xid_seed;
		xid_seed++;
		validsrvs++;
	}

	/* Make sure at least one server was assigned */
	if (!validsrvs) {
		free(reqs);
		return(-1);
	}

	/* Create RPC handle */
	sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	clnt = clntudp_create(any, YPPROG, YPVERS, tv, &sock);
	if (clnt == NULL) {
		close(sock);
		for (i = 0; i < cnt; i++)
			if (reqs[i] != NULL)
				free(reqs[i]);
		free(reqs);
		return(-1);
	}
	clnt->cl_auth = authunix_create_default();
	tv.tv_sec = 0;

	clnt_control(clnt, CLSET_TIMEOUT, (char *)&tv);
	async = TRUE;
	clnt_control(clnt, CLSET_ASYNC, (char *)&async);
	ioctl(sock, FIONBIO, &dontblock);

	/* Transmit */
	for (i = 0; i < cnt; i++) {
		if (reqs[i] != NULL) {
			clnt_control(clnt, CLSET_XID, (char *)&reqs[i]->xid);
			addr.len = sizeof(reqs[i]->sin);
			addr.buf = (char *) &reqs[i]->sin;
			clnt_control(clnt, CLSET_SVC_ADDR, &addr);
			ypproc_domain_nonack_2_send(&foo, clnt);
		}
	}

	/* Receive reply */
	ypproc_domain_nonack_2_recv(&foo, clnt);

	/* Got a winner -- look him up. */
	clnt_control(clnt, CLGET_XID, (char *)&xid_lookup);
	for (i = 0; i < cnt; i++) {
		if (reqs[i] != NULL && reqs[i]->xid == xid_lookup) {
			winner = i;
			*port = reqs[i]->sin.sin_port;
		}
	}

	/* Shut everything down */
	auth_destroy(clnt->cl_auth);
	clnt_destroy(clnt);
	close(sock);

	for (i = 0; i < cnt; i++)
		if (reqs[i] != NULL)
			free(reqs[i]);
	free(reqs);

	return(winner);
}