/*
 *  the devxxx.c that calls us handles writing data, it knows best
 */
long netifwrite(struct ether *nif, struct chan *c, void *a, long n)
{
	ERRSTACK(1);
	struct netfile *f;
	int type;
	char *p, buf[64];
	uint8_t binaddr[Nmaxaddr];

	if (NETTYPE(c->qid.path) != Nctlqid)
		error(EPERM, NULL);

	if (n >= sizeof(buf))
		n = sizeof(buf) - 1;
	memmove(buf, a, n);
	buf[n] = 0;

	qlock(&nif->qlock);
	if (waserror()) {
		qunlock(&nif->qlock);
		nexterror();
	}

	f = nif->f[NETID(c->qid.path)];
	if ((p = matchtoken(buf, "connect")) != 0) {
		type = strtol(p, 0, 0);	/* allows any base, though usually hex */
		if (typeinuse(nif, type))
			error(EBUSY, NULL);
		f->type = type;
		if (f->type < 0)
			nif->all++;
	} else if (matchtoken(buf, "promiscuous")) {
		if (f->prom == 0) {
			if (nif->prom == 0 && nif->promiscuous != NULL)
				nif->promiscuous(nif->arg, 1);
			f->prom = 1;
			nif->prom++;
		}
	} else if ((p = matchtoken(buf, "scanbs")) != 0) {
		/* scan for base stations */
		if (f->scan == 0) {
			type = strtol(p, 0, 0);	/* allows any base, though usually hex */
			if (type < 5)
				type = 5;
			if (nif->scanbs != NULL)
				nif->scanbs(nif->arg, type);
			f->scan = type;
			nif->scan++;
		}
	} else if (matchtoken(buf, "bridge")) {
		f->bridge = 1;
	} else if (matchtoken(buf, "headersonly")) {
		f->headersonly = 1;
	} else if ((p = matchtoken(buf, "addmulti")) != 0) {
		if (parseaddr(binaddr, p, nif->alen) < 0)
			error(EFAIL, "bad address");
		p = netmulti(nif, f, binaddr, 1);
		if (p)
			error(EFAIL, p);
	} else if ((p = matchtoken(buf, "remmulti")) != 0) {
		if (parseaddr(binaddr, p, nif->alen) < 0)
			error(EFAIL, "bad address");
		p = netmulti(nif, f, binaddr, 0);
		if (p)
			error(EFAIL, p);
	} else
		n = -1;
	qunlock(&nif->qlock);
	poperror();
	return n;
}