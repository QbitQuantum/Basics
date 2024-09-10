static int
ifconfig(int argc, char *const *argv, int iscreate, const struct afswtch *uafp)
{
	const struct afswtch *afp, *nafp;
	const struct cmd *p;
	struct callback *cb;
	int s;

	strncpy(ifr.ifr_name, name, sizeof ifr.ifr_name);
	afp = uafp != NULL ? uafp : af_getbyname("inet");
top:
	ifr.ifr_addr.sa_family =
		afp->af_af == AF_LINK || afp->af_af == AF_UNSPEC ?
		AF_LOCAL : afp->af_af;

	if ((s = socket(ifr.ifr_addr.sa_family, SOCK_DGRAM, 0)) < 0 &&
	    (uafp != NULL || errno != EPROTONOSUPPORT ||
	     (s = socket(AF_LOCAL, SOCK_DGRAM, 0)) < 0))
		err(1, "socket(family %u,SOCK_DGRAM", ifr.ifr_addr.sa_family);

	while (argc > 0) {
		p = cmd_lookup(*argv, iscreate);
		if (iscreate && p == NULL) {
			/*
			 * Push the clone create callback so the new
			 * device is created and can be used for any
			 * remaining arguments.
			 */
			cb = callbacks;
			if (cb == NULL)
				errx(1, "internal error, no callback");
			callbacks = cb->cb_next;
			cb->cb_func(s, cb->cb_arg);
			iscreate = 0;
			/*
			 * Handle any address family spec that
			 * immediately follows and potentially
			 * recreate the socket.
			 */
			nafp = af_getbyname(*argv);
			if (nafp != NULL) {
				argc--, argv++;
				if (nafp != afp) {
					close(s);
					afp = nafp;
					goto top;
				}
			}
			/*
			 * Look for a normal parameter.
			 */
			continue;
		}
		if (p == NULL) {
			/*
			 * Not a recognized command, choose between setting
			 * the interface address and the dst address.
			 */
			p = (setaddr ? &setifdstaddr_cmd : &setifaddr_cmd);
		}
		if (p->c_u.c_func || p->c_u.c_func2) {
			if (p->c_parameter == NEXTARG) {
				if (argv[1] == NULL)
					errx(1, "'%s' requires argument",
					    p->c_name);
				p->c_u.c_func(argv[1], 0, s, afp);
				argc--, argv++;
			} else if (p->c_parameter == OPTARG) {
				p->c_u.c_func(argv[1], 0, s, afp);
				if (argv[1] != NULL)
					argc--, argv++;
			} else if (p->c_parameter == NEXTARG2) {
				if (argc < 3)
					errx(1, "'%s' requires 2 arguments",
					    p->c_name);
				p->c_u.c_func2(argv[1], argv[2], s, afp);
				argc -= 2, argv += 2;
			} else
				p->c_u.c_func(*argv, p->c_parameter, s, afp);
		}
		argc--, argv++;
	}

	/*
	 * Do any post argument processing required by the address family.
	 */
	if (afp->af_postproc != NULL)
		afp->af_postproc(s, afp);
	/*
	 * Do deferred callbacks registered while processing
	 * command-line arguments.
	 */
	for (cb = callbacks; cb != NULL; cb = cb->cb_next)
		cb->cb_func(s, cb->cb_arg);
	/*
	 * Do deferred operations.
	 */
	if (clearaddr) {
		if (afp->af_ridreq == NULL || afp->af_difaddr == 0) {
			warnx("interface %s cannot change %s addresses!",
			      name, afp->af_name);
			clearaddr = 0;
		}
	}
	if (clearaddr) {
		int ret;
		strncpy(afp->af_ridreq, name, sizeof ifr.ifr_name);
		ret = ioctl(s, afp->af_difaddr, afp->af_ridreq);
		if (ret < 0) {
			if (errno == EADDRNOTAVAIL && (doalias >= 0)) {
				/* means no previous address for interface */
			} else
				Perror("ioctl (SIOCDIFADDR)");
		}
	}
	if (newaddr) {
		if (afp->af_addreq == NULL || afp->af_aifaddr == 0) {
			warnx("interface %s cannot change %s addresses!",
			      name, afp->af_name);
			newaddr = 0;
		}
	}
	if (newaddr && (setaddr || setmask)) {
		strncpy(afp->af_addreq, name, sizeof ifr.ifr_name);
		if (ioctl(s, afp->af_aifaddr, afp->af_addreq) < 0)
			Perror("ioctl (SIOCAIFADDR)");
	}

	close(s);
	return(0);
}