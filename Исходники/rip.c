void
main(int argc, char *argv[])
{
	int dobroadcast, i, n;
	long diff;
	char *p;
	char buf[2*1024];
	uint8_t raddr[Pasize];
	Bnet *bn, **l;
	Udphdr *up;
	Rip *r;
	Ripmsg *m;
	Route route;
	static long btime;

	setnetmtpt(netdir, sizeof(netdir), nil);
	dobroadcast = 0;
	ARGBEGIN{
	case 'b':
		dobroadcast++;
		break;
	case 'd':
		debug++;
		break;
	case 'n':
		readonly++;
		break;
	case 'x':
		p = ARGF();
		if(p == nil)
			usage();
		setnetmtpt(netdir, sizeof(netdir), p);
		break;
	default:
		usage();
	}ARGEND

	/* specific broadcast nets */
	l = &bnets;
	while(argc > 0){
		bn = (Bnet*)malloc(sizeof(Bnet));
		if(bn == 0)
			fatal(1, "out of mem");
		v4parseip(bn->addr, *argv);
		*l = bn;
		l = &bn->next;
		argc--;
		argv++;
		dobroadcast++;
	}

	/* command returns */
	if(!debug)
		switch(rfork(RFNOTEG|RFPROC|RFFDG|RFNOWAIT)) {
		case -1:
			fatal(1, "fork");
		case 0:
			break;
		default:
			exits(0);
		}


	fmtinstall('E', eipfmt);
	fmtinstall('V', eipfmt);

	snprint(routefile, sizeof(routefile), "%s/iproute", netdir);
	snprint(buf, sizeof(buf), "%s/iproute", netdir);

	now = time(0);
	readifcs();
	readroutes();

	notify(ding);

	ripfd = openport();
	for(;;) {
		diff = btime - time(0);
		if(diff <= 0){
			if(dobroadcast)
				broadcast();
			timeoutroutes();

			btime = time(0) + 2*60;
			diff = 2*60;
		}
		alarm(diff*1000);
		n = read(ripfd, buf, sizeof(buf));
		alarm(0);
		if(n <= 0)
			continue;

		n = (n - Udphdrsize - 4) / sizeof(Rip);
		if(n <= 0)
			continue;

		up = (Udphdr*)buf;
		m = (Ripmsg*)(buf+Udphdrsize);
		if(m->type != Response || m->vers != Version)
			continue;
		v6tov4(raddr, up->raddr);

		/* ignore our own messages */
		for(i = 0; i < ialloc.nifc; i++)
			if(equivip(ialloc.ifc[i].addr, raddr))
				continue;

		now = time(0);
		for(r = m->rip; r < &m->rip[n]; r++){
			memmove(route.gate, raddr, Pasize);
			memmove(route.mask, getmask(r->addr), Pasize);
			v4maskip(r->addr, route.mask, route.dest);
			route.metric = nhgetl(r->metric) + 1;
			if(route.metric < 1)
				continue;
			considerroute(&route);
		}
	}
	/* not reached */
}