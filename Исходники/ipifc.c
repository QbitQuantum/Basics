/*
 *  add an address to an interface.
 */
char*
ipifcadd(Ipifc *ifc, char **argv, int argc, int tentative, Iplifc *lifcp)
{
	int i, type, mtu, sendnbrdisc = 0;
	uint8_t ip[IPaddrlen], mask[IPaddrlen], rem[IPaddrlen];
	uint8_t bcast[IPaddrlen], net[IPaddrlen];
	Iplifc *lifc, **l;
	Fs *f;

	if(ifc->medium == nil)
		return "ipifc not yet bound to device";

	f = ifc->conv->p->f;

	type = Rifc;
	memset(ip, 0, IPaddrlen);
	memset(mask, 0, IPaddrlen);
	memset(rem, 0, IPaddrlen);
	switch(argc){
	case 6:
		if(strcmp(argv[5], "proxy") == 0)
			type |= Rproxy;
		/* fall through */
	case 5:
		mtu = strtoul(argv[4], 0, 0);
		if(mtu >= ifc->medium->mintu && mtu <= ifc->medium->maxtu)
			ifc->maxtu = mtu;
		/* fall through */
	case 4:
		if (parseip(ip, argv[1]) == -1 || parseip(rem, argv[3]) == -1)
			return Ebadip;
		parseipmask(mask, argv[2]);
		maskip(rem, mask, net);
		break;
	case 3:
		if (parseip(ip, argv[1]) == -1)
			return Ebadip;
		parseipmask(mask, argv[2]);
		maskip(ip, mask, rem);
		maskip(rem, mask, net);
		break;
	case 2:
		if (parseip(ip, argv[1]) == -1)
			return Ebadip;
		memmove(mask, defmask(ip), IPaddrlen);
		maskip(ip, mask, rem);
		maskip(rem, mask, net);
		break;
	default:
		return Ebadarg;
	}
	if(isv4(ip))
		tentative = 0;
	wlock(ifc);

	/* ignore if this is already a local address for this ifc */
	for(lifc = ifc->lifc; lifc; lifc = lifc->next) {
		if(ipcmp(lifc->local, ip) == 0) {
			if(lifc->tentative != tentative)
				lifc->tentative = tentative;
			if(lifcp) {
				lifc->onlink = lifcp->onlink;
				lifc->autoflag = lifcp->autoflag;
				lifc->validlt = lifcp->validlt;
				lifc->preflt = lifcp->preflt;
				lifc->origint = lifcp->origint;
			}
			goto out;
		}
	}

	/* add the address to the list of logical ifc's for this ifc */
	lifc = smalloc(sizeof(Iplifc));
	ipmove(lifc->local, ip);
	ipmove(lifc->mask, mask);
	ipmove(lifc->remote, rem);
	ipmove(lifc->net, net);
	lifc->tentative = tentative;
	if(lifcp) {
		lifc->onlink = lifcp->onlink;
		lifc->autoflag = lifcp->autoflag;
		lifc->validlt = lifcp->validlt;
		lifc->preflt = lifcp->preflt;
		lifc->origint = lifcp->origint;
	} else {		/* default values */
		lifc->onlink = lifc->autoflag = 1;
		lifc->validlt = lifc->preflt = ~0L;
		lifc->origint = NOW / 1000;
	}
	lifc->next = nil;

	for(l = &ifc->lifc; *l; l = &(*l)->next)
		;
	*l = lifc;

	/* check for point-to-point interface */
	if(ipcmp(ip, v6loopback)) /* skip v6 loopback, it's a special address */
	if(ipcmp(mask, IPallbits) == 0)
		type |= Rptpt;

	/* add local routes */
	if(isv4(ip))
		v4addroute(f, tifc, rem+IPv4off, mask+IPv4off, rem+IPv4off, type);
	else
		v6addroute(f, tifc, rem, mask, rem, type);

	addselfcache(f, ifc, lifc, ip, Runi);

	if((type & (Rproxy|Rptpt)) == (Rproxy|Rptpt)){
		ipifcregisterproxy(f, ifc, rem);
		goto out;
	}

	if(isv4(ip) || ipcmp(ip, IPnoaddr) == 0) {
		/* add subnet directed broadcast address to the self cache */
		for(i = 0; i < IPaddrlen; i++)
			bcast[i] = (ip[i] & mask[i]) | ~mask[i];
		addselfcache(f, ifc, lifc, bcast, Rbcast);

		/* add subnet directed network address to the self cache */
		for(i = 0; i < IPaddrlen; i++)
			bcast[i] = (ip[i] & mask[i]) & mask[i];
		addselfcache(f, ifc, lifc, bcast, Rbcast);

		/* add network directed broadcast address to the self cache */
		memmove(mask, defmask(ip), IPaddrlen);
		for(i = 0; i < IPaddrlen; i++)
			bcast[i] = (ip[i] & mask[i]) | ~mask[i];
		addselfcache(f, ifc, lifc, bcast, Rbcast);

		/* add network directed network address to the self cache */
		memmove(mask, defmask(ip), IPaddrlen);
		for(i = 0; i < IPaddrlen; i++)
			bcast[i] = (ip[i] & mask[i]) & mask[i];
		addselfcache(f, ifc, lifc, bcast, Rbcast);

		addselfcache(f, ifc, lifc, IPv4bcast, Rbcast);
	}
	else {
		if(ipcmp(ip, v6loopback) == 0) {
			/* add node-local mcast address */
			addselfcache(f, ifc, lifc, v6allnodesN, Rmulti);

			/* add route for all node multicast */
			v6addroute(f, tifc, v6allnodesN, v6allnodesNmask,
				v6allnodesN, Rmulti);
		}

		/* add all nodes multicast address */
		addselfcache(f, ifc, lifc, v6allnodesL, Rmulti);

		/* add route for all nodes multicast */
		v6addroute(f, tifc, v6allnodesL, v6allnodesLmask, v6allnodesL,
			Rmulti);

		/* add solicited-node multicast address */
		ipv62smcast(bcast, ip);
		addselfcache(f, ifc, lifc, bcast, Rmulti);

		sendnbrdisc = 1;
	}

	/* register the address on this network for address resolution */
	if(isv4(ip) && ifc->medium->areg != nil)
		(*ifc->medium->areg)(ifc, ip);

out:
	wunlock(ifc);
	if(tentative && sendnbrdisc)
		icmpns(f, 0, SRC_UNSPEC, ip, TARG_MULTI, ifc->mac);
	return nil;
}