int
umountfs(char *name, char **typelist)
{
	enum clnt_stat clnt_stat;
	struct hostent *hp;
	struct mtablist *mtab;
	struct sockaddr_in saddr;
	struct timeval pertry, try;
	CLIENT *clp;
	size_t len;
	int so, speclen, do_rpc;
	char *mntonname, *mntfromname;
	char *mntfromnamerev;
	char *nfsdirname, *orignfsdirname;
	char *resolved, realname[MAXPATHLEN];
	char *type, *delimp, *hostp, *origname;

	len = 0;
	mtab = NULL;
	mntfromname = mntonname = delimp = hostp = orignfsdirname = NULL;

	/*
	 * 1. Check if the name exists in the mounttable.
	 */
	(void)checkmntlist(name, &mntfromname, &mntonname, &type);
	/*
	 * 2. Remove trailing slashes if there are any. After that
	 * we look up the name in the mounttable again.
	 */
	if (mntfromname == NULL && mntonname == NULL) {
		speclen = strlen(name);
		for (speclen = strlen(name); 
		    speclen > 1 && name[speclen - 1] == '/';
		    speclen--)
			name[speclen - 1] = '\0';
		(void)checkmntlist(name, &mntfromname, &mntonname, &type);
		resolved = name;
		/* Save off original name in origname */
		if ((origname = strdup(name)) == NULL)
			err(1, "strdup");
		/*
		 * 3. Check if the deprecated nfs-syntax with an '@'
		 * has been used and translate it to the ':' syntax.
		 * Look up the name in the mounttable again.
		 */
		if (mntfromname == NULL && mntonname == NULL) {
			if ((delimp = strrchr(name, '@')) != NULL) {
				hostp = delimp + 1;
				if (*hostp != '\0') {
					/*
					 * Make both '@' and ':'
					 * notations equal 
					 */
					char *host = strdup(hostp);
					len = strlen(hostp);
					if (host == NULL)
						err(1, "strdup");
					memmove(name + len + 1, name,
					    (size_t)(delimp - name));
					name[len] = ':';
					memmove(name, host, len);
					free(host);
				}
				for (speclen = strlen(name); 
				    speclen > 1 && name[speclen - 1] == '/';
				    speclen--)
					name[speclen - 1] = '\0';
				name[len + speclen + 1] = '\0';
				(void)checkmntlist(name, &mntfromname,
				    &mntonname, &type);
				resolved = name;
			}
			/*
			 * 4. Check if a relative mountpoint has been
			 * specified. This should happen as last check,
			 * the order is important. To prevent possible
			 * nfs-hangs, we just call realpath(3) on the
			 * basedir of mountpoint and add the dirname again.
			 * Check the name in mounttable one last time.
			 */
			if (mntfromname == NULL && mntonname == NULL) {
				(void)strcpy(name, origname);
				if ((getrealname(name, realname)) != NULL) {
					(void)checkmntlist(realname,
					    &mntfromname, &mntonname, &type);
					resolved = realname;
				}
				/*
				 * All tests failed, return to main()
				 */
				if (mntfromname == NULL && mntonname == NULL) {
					(void)strcpy(name, origname);
					warnx("%s: not currently mounted",
					    origname);
					free(origname);
					return (1);
				}
			}
		}
		free(origname);
	} else
		resolved = name;

	if (checkvfsname(type, typelist))
		return (1);

	hp = NULL;
	nfsdirname = NULL;
	if (!strcmp(type, "nfs")) {
		if ((nfsdirname = strdup(mntfromname)) == NULL)
			err(1, "strdup");
		orignfsdirname = nfsdirname;
		if ((delimp = strchr(nfsdirname, ':')) != NULL) {
			*delimp = '\0';
			hostp = nfsdirname;
			if ((hp = gethostbyname(hostp)) == NULL) {
				warnx("can't get net id for host");
			}
			nfsdirname = delimp + 1;
		}
	}
	/*
	 * Check if the reverse entrys of the mounttable are really the
	 * same as the normal ones.
	 */
	if ((mntfromnamerev = strdup(getmntname(getmntname(mntfromname,
	    NULL, MNTON, &type, NAME), NULL, MNTFROM, &type, NAME))) == NULL)
		err(1, "strdup");
	/*
	 * Mark the uppermost mount as unmounted.
	 */
	(void)getmntname(mntfromname, mntonname, NOTHING, &type, MARK);
	/*
	 * If several equal mounts are in the mounttable, check the order
	 * and warn the user if necessary.
	 */
	if (strcmp(mntfromnamerev, mntfromname ) != 0 &&
	    strcmp(resolved, mntonname) != 0) {
		warnx("cannot umount %s, %s\n        "
		    "is mounted there, umount it first",
		    mntonname, mntfromnamerev);

		/* call getmntname again to set mntcheck[i] to 0 */
		(void)getmntname(mntfromname, mntonname,
		    NOTHING, &type, UNMARK);
		return (1);
	}
	free(mntfromnamerev);
	/*
	 * Check if we have to start the rpc-call later.
	 * If there are still identical nfs-names mounted,
	 * we skip the rpc-call. Obviously this has to
	 * happen before unmount(2), but it should happen
	 * after the previous namecheck.
	 */
	if (strcmp(type, "nfs") == 0 && getmntname(mntfromname, NULL, NOTHING,
	    &type, COUNT) != NULL)
		do_rpc = 1;
	else
		do_rpc = 0;
	if (!namematch(hp))
		return (1);
	if (unmount(mntonname, fflag) != 0 ) {
		warn("unmount of %s failed", mntonname);
		return (1);
	}
	if (vflag)
		(void)printf("%s: unmount from %s\n", mntfromname, mntonname);
	/*
	 * Report to mountd-server which nfsname
	 * has been unmounted.
	 */
	if (hp != NULL && !(fflag & MNT_FORCE) && do_rpc) {
		memset(&saddr, 0, sizeof(saddr));
		saddr.sin_family = AF_INET;
		saddr.sin_port = 0;
		memmove(&saddr.sin_addr, hp->h_addr, 
		    MIN(hp->h_length, sizeof(saddr.sin_addr)));
		pertry.tv_sec = 3;
		pertry.tv_usec = 0;
		so = RPC_ANYSOCK;
		if ((clp = clntudp_create(&saddr,
		    RPCPROG_MNT, RPCMNT_VER1, pertry, &so)) == NULL) {
			clnt_pcreateerror("Cannot MNT PRC");
			return (1);
		}
		clp->cl_auth = authunix_create_default();
		try.tv_sec = 20;
		try.tv_usec = 0;
		clnt_stat = clnt_call(clp, RPCMNT_UMOUNT, xdr_dir,
		    nfsdirname, xdr_void, (caddr_t)0, try);
		if (clnt_stat != RPC_SUCCESS) {
			clnt_perror(clp, "Bad MNT RPC");
			return (1);
		}
		/*
		 * Remove the unmounted entry from /var/db/mounttab.
		 */
		if (read_mtab(mtab)) {
			mtab = mtabhead;
			clean_mtab(hostp, nfsdirname);
			if(!write_mtab())
				warnx("cannot remove entry %s:%s",
				    hostp, nfsdirname);
			free_mtab();
		}
		free(orignfsdirname);
		auth_destroy(clp->cl_auth);
		clnt_destroy(clp);
	}