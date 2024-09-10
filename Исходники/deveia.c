static Chan*
eiaopen(Chan *c, int mode)
{
	int port = NETID(c->qid.path);

	c = devopen(c, mode, eiadir, ndir, devgen);

	switch(NETTYPE(c->qid.path)) {
	case Nctlqid:
	case Ndataqid:
	case Nstatqid:
		if(incref(&eia[port].r) != 1)
			break;
		if(waserror()) {
			decref(&eia[port].r);
			nexterror();
		}
		openport(port);
		poperror();
		break;
	}
	return c;
}