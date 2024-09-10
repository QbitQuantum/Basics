int
cray_setup (uid_t uid, char *username, const char *command)
{
	extern struct udb *getudb();
	extern char *setlimits();

	int err;			/* error return */
	time_t system_time;		/* current system clock */
	time_t expiration_time;		/* password expiration time */
	int maxattempts;		/* maximum no. of failed login attempts */
	int SecureSys;			/* unicos security flag */
	int minslevel = 0;		/* system minimum security level */
	int i, j;
	int valid_acct = -1;		/* flag for reading valid acct */
	char acct_name[MAXACID] = { "" }; /* used to read acct name */
	struct jtab jtab;		/* Job table struct */
	struct udb ue;			/* udb entry for logging-in user */
	struct udb *up;			/* pointer to UDB entry */
	struct secstat secinfo;		/* file  security attributes */
	struct servprov init_info;	/* used for sesscntl() call */
	int jid;			/* job ID */
	int pid;			/* process ID */
	char *sr;			/* status return from setlimits() */
	char *ttyn = NULL;		/* ttyname or command name*/
	char hostname[MAXHOSTNAMELEN];
	/* passwd stuff for ia_user */
	passwd_t pwdacm, pwddialup, pwdudb, pwdwal, pwddce;
	ia_user_ret_t uret;		/* stuff returned from ia_user */
	ia_user_t usent;		/* ia_user main structure */
	int ia_rcode;			/* ia_user return code */
	ia_failure_t fsent;		/* ia_failure structure */
	ia_failure_ret_t fret;		/* ia_failure return stuff */
	ia_success_t ssent;		/* ia_success structure */
	ia_success_ret_t sret;		/* ia_success return stuff */
	int ia_mlsrcode;		/* ia_mlsuser return code */
	int secstatrc;			/* [f]secstat return code */

	if (SecureSys = (int)sysconf(_SC_CRAY_SECURE_SYS)) {
		getsysv(&sysv, sizeof(struct sysv));
		minslevel = sysv.sy_minlvl;
		if (getusrv(&usrv) < 0)
			fatal("getusrv() failed, errno = %d", errno);
	}
	hostname[0] = '\0';
	strlcpy(hostname,
	   (char *)get_canonical_hostname(options.use_dns),
	   MAXHOSTNAMELEN);
	/*
	 *  Fetch user's UDB entry.
	 */
	getsysudb();
	if ((up = getudbnam(username)) == UDB_NULL)
		fatal("cannot fetch user's UDB entry");

	/*
	 *  Prevent any possible fudging so perform a data
	 *  safety check and compare the supplied uid against
	 *  the udb's uid.
	 */
	if (up->ue_uid != uid)
		fatal("IA uid missmatch");
	endudb();

	if ((jid = getjtab(&jtab)) < 0) {
		debug("getjtab");
		return(-1);
	}
	pid = getpid();
	ttyn = ttyname(0);
	if (SecureSys) {
		if (ttyn != NULL)
			secstatrc = secstat(ttyn, &secinfo);
		else
			secstatrc = fsecstat(1, &secinfo);

		if (secstatrc == 0)
			debug("[f]secstat() successful");
		else
			fatal("[f]secstat() error, rc = %d", secstatrc);
	}
	if ((ttyn == NULL) && ((char *)command != NULL))
		ttyn = (char *)command;
	/*
	 *  Initialize all structures to call ia_user
	 */
	usent.revision = 0;
	usent.uname = username;
	usent.host = hostname;
	usent.ttyn = ttyn;
	usent.caller = IA_SSHD; 
	usent.pswdlist = &pwdacm;
	usent.ueptr = &ue;
	usent.flags = IA_INTERACTIVE | IA_FFLAG;
	pwdacm.atype = IA_SECURID;
	pwdacm.pwdp = NULL;
	pwdacm.next = &pwdudb;

	pwdudb.atype = IA_UDB;
	pwdudb.pwdp = NULL;
	pwdudb.next = &pwddce;

	pwddce.atype = IA_DCE;
	pwddce.pwdp = NULL;
	pwddce.next = &pwddialup;

	pwddialup.atype = IA_DIALUP;
	pwddialup.pwdp = NULL;
	/* pwddialup.next = &pwdwal; */
	pwddialup.next = NULL;

	pwdwal.atype = IA_WAL;
	pwdwal.pwdp = NULL;
	pwdwal.next = NULL;

	uret.revision = 0;
	uret.pswd = NULL;
	uret.normal = 0;

	ia_rcode = ia_user(&usent, &uret);
	switch (ia_rcode) {
	/*
	 *  These are acceptable return codes from ia_user()
	 */
	case IA_UDBWEEK:        /* Password Expires in 1 week */
		expiration_time = ue.ue_pwage.time + ue.ue_pwage.maxage;
		printf ("WARNING - your current password will expire %s\n",
		ctime((const time_t *)&expiration_time));
		break;
	case IA_UDBEXPIRED:
		if (ttyname(0) != NULL) {
			/* Force a password change */
			printf("Your password has expired; Choose a new one.\n");
			execl("/bin/passwd", "passwd", username, 0);
			exit(9);
			}
		break;
	case IA_NORMAL:         /* Normal Return Code */
		break;
	case IA_BACKDOOR:
		/* XXX: can we memset it to zero here so save some of this */
		strlcpy(ue.ue_name, "root", sizeof(ue.ue_name));
		strlcpy(ue.ue_dir, "/", sizeof(ue.ue_dir));
		strlcpy(ue.ue_shell, "/bin/sh", sizeof(ue.ue_shell));

		ue.ue_passwd[0] = '\0';
		ue.ue_age[0] = '\0';
		ue.ue_comment[0] = '\0';
		ue.ue_loghost[0] = '\0';
		ue.ue_logline[0] = '\0';

		ue.ue_uid = -1;
		ue.ue_nice[UDBRC_INTER] = 0;

		for (i = 0; i < MAXVIDS; i++)
			ue.ue_gids[i] = 0;

		ue.ue_logfails = 0;
		ue.ue_minlvl = ue.ue_maxlvl = ue.ue_deflvl = minslevel;
		ue.ue_defcomps = 0;
		ue.ue_comparts = 0;
		ue.ue_permits = 0;
		ue.ue_trap = 0;
		ue.ue_disabled = 0;
		ue.ue_logtime = 0;
		break;
	case IA_CONSOLE:        /* Superuser not from Console */
	case IA_TRUSTED:	/* Trusted user */
		if (options.permit_root_login > PERMIT_NO)
			break;	/* Accept root login */
	default:
	/*
	 *  These are failed return codes from ia_user()
	 */
		switch (ia_rcode) 
		{
		case IA_BADAUTH:
			printf("Bad authorization, access denied.\n");
			break;
		case IA_DISABLED:
			printf("Your login has been disabled. Contact the system ");
			printf("administrator for assistance.\n");
			break;
		case IA_GETSYSV:
			printf("getsysv() failed - errno = %d\n", errno);
			break;
		case IA_MAXLOGS:
			printf("Maximum number of failed login attempts exceeded.\n");
			printf("Access denied.\n");
			break;
		case IA_UDBPWDNULL:
			if (SecureSys)
				printf("NULL Password not allowed on MLS systems.\n");
			break;
		default:
			break;
		}

		/*
		 *  Authentication failed.
		 */
		printf("sshd: Login incorrect, (0%o)\n",
		    ia_rcode-IA_ERRORCODE);

		/*
		 *  Initialize structure for ia_failure
		 *  which will exit.
		 */
		fsent.revision = 0;
		fsent.uname = username;
		fsent.host = hostname;
		fsent.ttyn = ttyn;
		fsent.caller = IA_SSHD;
		fsent.flags = IA_INTERACTIVE;
		fsent.ueptr = &ue;
		fsent.jid = jid;
		fsent.errcode = ia_rcode;
		fsent.pwdp = uret.pswd;
		fsent.exitcode = 1;

		fret.revision = 0;
		fret.normal = 0;

		/*
		*  Call ia_failure because of an IA failure.
		*  There is no return because ia_failure exits.
		*/
		ia_failure(&fsent, &fret);

		exit(1); 
	}

	ia_mlsrcode = IA_NORMAL;
	if (SecureSys) {
		debug("calling ia_mlsuser()");
		ia_mlsrcode = ia_mlsuser(&ue, &secinfo, &usrv, NULL, 0);
	}
	if (ia_mlsrcode != IA_NORMAL) {
		printf("sshd: Login incorrect, (0%o)\n",
		    ia_mlsrcode-IA_ERRORCODE);
		/*
		 *  Initialize structure for ia_failure
		 *  which will exit.
		 */
		fsent.revision = 0;
		fsent.uname = username;
		fsent.host = hostname;
		fsent.ttyn = ttyn;
		fsent.caller = IA_SSHD;
		fsent.flags = IA_INTERACTIVE;
		fsent.ueptr = &ue;
		fsent.jid  = jid;
		fsent.errcode = ia_mlsrcode;
		fsent.pwdp = uret.pswd;
		fsent.exitcode = 1;
		fret.revision = 0;
		fret.normal = 0;

		/*
		 *  Call ia_failure because of an IA failure.
		 *  There is no return because ia_failure exits.
		 */
		ia_failure(&fsent,&fret);
		exit(1); 
	}

	/* Provide login status information */
	if (options.print_lastlog && ue.ue_logtime != 0) {
		printf("Last successful login was : %.*s ", 19,
		    (char *)ctime(&ue.ue_logtime));

		if (*ue.ue_loghost != '\0') {
			printf("from %.*s\n", sizeof(ue.ue_loghost),
			    ue.ue_loghost);
		} else {
			printf("on %.*s\n", sizeof(ue.ue_logline),
			    ue.ue_logline);
		}

		if (SecureSys && (ue.ue_logfails != 0)) {
			printf("  followed by %d failed attempts\n",
			    ue.ue_logfails);
		}
	}

	/*
	 * Call ia_success to process successful I/A.
	 */
	ssent.revision = 0;
	ssent.uname = username;
	ssent.host = hostname;
	ssent.ttyn = ttyn;
	ssent.caller = IA_SSHD;
	ssent.flags = IA_INTERACTIVE;
	ssent.ueptr = &ue;
	ssent.jid = jid;
	ssent.errcode = ia_rcode;
	ssent.us = NULL;
	ssent.time = 1;	/* Set ue_logtime */

	sret.revision = 0;
	sret.normal = 0;

	ia_success(&ssent, &sret);

	/*
	 * Query for account, iff > 1 valid acid & askacid permbit
	 */
	if (((ue.ue_permbits & PERMBITS_ACCTID) ||
	    (ue.ue_acids[0] >= 0) && (ue.ue_acids[1] >= 0)) &&
	    ue.ue_permbits & PERMBITS_ASKACID) {
		if (ttyname(0) != NULL) {
			debug("cray_setup: ttyname true case, %.100s", ttyname);
			while (valid_acct == -1) {
				printf("Account (? for available accounts)"
				    " [%s]: ", acid2nam(ue.ue_acids[0]));
				fgets(acct_name, MAXACID, stdin);
				switch (acct_name[0]) {
				case EOF:
					exit(0);
					break;
				case '\0':
					valid_acct = ue.ue_acids[0];
					strlcpy(acct_name, acid2nam(valid_acct), MAXACID);
					break;
				case '?':
					/* Print the list 3 wide */
					for (i = 0, j = 0; i < MAXVIDS; i++) {
						if (ue.ue_acids[i] == -1) {
							printf("\n");
							break;
						}
						if (++j == 4) {
							j = 1;
							printf("\n");
						}
						printf(" %s",
						    acid2nam(ue.ue_acids[i]));
					}
					if (ue.ue_permbits & PERMBITS_ACCTID) {
						printf("\"acctid\" permbit also allows"
						    " you to select any valid "
						    "account name.\n");
					}
					printf("\n");
					break;
				default:
					valid_acct = nam2acid(acct_name);
					if (valid_acct == -1) 
						printf(
						    "Account id not found for"
						    " account name \"%s\"\n\n",
						    acct_name);
					break;
				}
				/*
				 * If an account was given, search the user's
				 * acids array to verify they can use this account.
				 */
				if ((valid_acct != -1) &&
				    !(ue.ue_permbits & PERMBITS_ACCTID)) {
					for (i = 0; i < MAXVIDS; i++) {
						if (ue.ue_acids[i] == -1)
							break;
						if (valid_acct == ue.ue_acids[i])
							break;
					}
					if (i == MAXVIDS ||
					    ue.ue_acids[i] == -1) {
						fprintf(stderr, "Cannot set"
						    " account name to "
						    "\"%s\", permission "
						    "denied\n\n", acct_name);
						valid_acct = -1;
					}
				}
			}
		} else {
			/*
			 * The client isn't connected to a terminal and can't
			 * respond to an acid prompt.  Use default acid.
			 */
			debug("cray_setup: ttyname false case, %.100s",
			    ttyname);
			valid_acct = ue.ue_acids[0];
		}
	} else {
		/*
		 * The user doesn't have the askacid permbit set or
		 * only has one valid account to use.
		 */
		valid_acct = ue.ue_acids[0];
	}
	if (acctid(0, valid_acct) < 0) {
		printf ("Bad account id: %d\n", valid_acct);
		exit(1);
	}

	/* 
	 * Now set shares, quotas, limits, including CPU time for the 
	 * (interactive) job and process, and set up permissions 
	 * (for chown etc), etc.
	 */
	if (setshares(ue.ue_uid, valid_acct, printf, 0, 0)) {
		printf("Unable to give %d shares to <%s>(%d/%d)\n",
		    ue.ue_shares, ue.ue_name, ue.ue_uid, valid_acct);
		exit(1);
	}

	sr = setlimits(username, C_PROC, pid, UDBRC_INTER);
	if (sr != NULL) {
		debug("%.200s", sr);
		exit(1);
	}
	sr = setlimits(username, C_JOB, jid, UDBRC_INTER);
	if (sr != NULL) {
		debug("%.200s", sr);
		exit(1);
	}
	/*
	 * Place the service provider information into
	 * the session table (Unicos) or job table (Unicos/mk).
	 * There exist double defines for the job/session table in
	 * unicos/mk (jtab.h) so no need for a compile time switch.
	 */
	memset(&init_info, '\0', sizeof(init_info));
	init_info.s_sessinit.si_id = URM_SPT_LOGIN;
	init_info.s_sessinit.si_pid = getpid();
	init_info.s_sessinit.si_sid = jid;
	sesscntl(0, S_SETSERVPO, (int)&init_info);

	/*
	 * Set user and controlling tty security attributes.
	 */
	if (SecureSys) {
		if (setusrv(&usrv) == -1) {
			debug("setusrv() failed, errno = %d",errno);
			exit(1);
		}
	}

	return (0);
}