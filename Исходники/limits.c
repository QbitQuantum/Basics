int
main(int argc, char *argv[])
{
    char *p, *cls = NULL;
    char *cleanenv[1];
    struct passwd * pwd = NULL;
    int rcswhich, shelltype;
    int i, num_limits = 0;
    int ch, doeval = 0, doall = 0;
    login_cap_t * lc = NULL;
    enum { ANY=0, SOFT=1, HARD=2, BOTH=3, DISPLAYONLY=4 } type = ANY;
    enum { RCSUNKNOWN=0, RCSSET=1, RCSSEL=2 } todo = RCSUNKNOWN;
    int which_limits[RLIM_NLIMITS];
    rlim_t set_limits[RLIM_NLIMITS];
    struct rlimit limits[RLIM_NLIMITS];

    /* init resource tables */
    for (i = 0; i < RLIM_NLIMITS; i++) {
	which_limits[i] = 0; /* Don't set/display any */
	set_limits[i] = RLIM_INFINITY;
	/* Get current resource values */
	if (getrlimit(i, &limits[i]) < 0) {
		limits[i].rlim_cur = -1;
		limits[i].rlim_max = -1;
	}
    }

    optarg = NULL;
    while ((ch = getopt(argc, argv, ":EeC:U:BSHabc:d:f:k:l:m:n:s:t:u:v:")) != -1) {
	switch(ch) {
	case 'a':
	    doall = 1;
	    break;
	case 'E':
	    environ = cleanenv;
	    cleanenv[0] = NULL;
	    break;
	case 'e':
	    doeval = 1;
	    break;
	case 'C':
	    cls = optarg;
	    break;
	case 'U':
	    if ((pwd = getpwnam(optarg)) == NULL) {
		if (!isdigit(*optarg) ||
		    (pwd = getpwuid(atoi(optarg))) == NULL) {
		    warnx("invalid user `%s'", optarg);
		    usage();
		}
	    }
	    break;
	case 'H':
	    type = HARD;
	    break;
	case 'S':
	    type = SOFT;
	    break;
	case 'B':
	    type = SOFT|HARD;
	    break;
	default:
	case ':': /* Without arg */
	    if ((p = strchr(rcs_string, optopt)) != NULL) {
		rcswhich = p - rcs_string;

		/*
		 * Backwards compatibility with earlier kernel which might
		 * support fewer resources.
		 */
		if (rcswhich >= RLIM_NLIMITS) {
		    usage();
		    break;
		}
		if (optarg && *optarg == '-') { /* 'arg' is actually a switch */
		    --optind;		/* back one arg, and make arg NULL */
		    optarg = NULL;
		}
		todo = optarg == NULL ? RCSSEL : RCSSET;
		if (type == ANY)
		    type = BOTH;
		which_limits[rcswhich] = optarg ? type : DISPLAYONLY;
		set_limits[rcswhich] = resource_num(rcswhich, optopt, optarg);
		num_limits++;
		break;
	    }
	    /* FALLTHRU */
	case '?':
	    usage();
	}
	optarg = NULL;
    }

    /* If user was specified, get class from that */
    if (pwd != NULL)
	lc = login_getpwclass(pwd);
    else if (cls != NULL && *cls != '\0') {
	lc = login_getclassbyname(cls, NULL);
	if (lc == NULL || strcmp(cls, lc->lc_class) != 0)
	    fprintf(stderr, "login class '%s' non-existent, using %s\n",
		    cls, lc?lc->lc_class:"current settings");
    }

    /* If we have a login class, update resource table from that */
    if (lc != NULL) {
	for (rcswhich = 0; rcswhich < RLIM_NLIMITS; rcswhich++) {
	    char str[40];
	    rlim_t val;

	    /* current value overridden by resourcename or resourcename-cur */
	    sprintf(str, "%s-cur", resources[rcswhich].cap);
	    val = resources[rcswhich].func(lc, resources[rcswhich].cap, limits[rcswhich].rlim_cur, limits[rcswhich].rlim_cur);
	    limits[rcswhich].rlim_cur = resources[rcswhich].func(lc, str, val, val);
	    /* maximum value overridden by resourcename or resourcename-max */
	    sprintf(str, "%s-max", resources[rcswhich].cap);
	    val = resources[rcswhich].func(lc, resources[rcswhich].cap, limits[rcswhich].rlim_max, limits[rcswhich].rlim_max);
	    limits[rcswhich].rlim_max = resources[rcswhich].func(lc, str, val, val);
	}
    }

    /* now, let's determine what we wish to do with all this */

    argv += optind;

    /* If we're setting limits or doing an eval (ie. we're not just
     * displaying), then check that hard limits are not lower than
     * soft limits, and force rasing the hard limit if we need to if
     * we are raising the soft limit, or lower the soft limit if we
     * are lowering the hard limit.
     */
    if ((*argv || doeval) && getuid() == 0) {

	for (rcswhich = 0; rcswhich < RLIM_NLIMITS; rcswhich++) {
	    if (limits[rcswhich].rlim_max != RLIM_INFINITY) {
		if (limits[rcswhich].rlim_cur == RLIM_INFINITY) {
		    limits[rcswhich].rlim_max = RLIM_INFINITY;
		    which_limits[rcswhich] |= HARD;
		} else if (limits[rcswhich].rlim_cur > limits[rcswhich].rlim_max) {
		    if (which_limits[rcswhich] == SOFT) {
			limits[rcswhich].rlim_max = limits[rcswhich].rlim_cur;
			which_limits[rcswhich] |= HARD;
		    }  else if (which_limits[rcswhich] == HARD) {
			limits[rcswhich].rlim_cur = limits[rcswhich].rlim_max;
			which_limits[rcswhich] |= SOFT;
		    } else {
			/* else.. if we're specifically setting both to
			 * silly values, then let it error out.
			 */
		    }
		}
	    }
	}
    }

    /* See if we've overridden anything specific on the command line */
    if (num_limits && todo == RCSSET) {
	for (rcswhich = 0; rcswhich < RLIM_NLIMITS; rcswhich++) {
	    if (which_limits[rcswhich] & HARD)
		limits[rcswhich].rlim_max = set_limits[rcswhich];
	    if (which_limits[rcswhich] & SOFT)
		limits[rcswhich].rlim_cur = set_limits[rcswhich];
	}
    }

    /* If *argv is not NULL, then we are being asked to
     * (perhaps) set environment variables and run a program
     */
    if (*argv) {
	if (doeval) {
	    warnx("-e cannot be used with `cmd' option");
	    usage();
	}

	login_close(lc);

	/* set leading environment variables, like eval(1) */
	while (*argv && (p = strchr(*argv, '='))) {
	    *p = '\0';
	    if (setenv(*argv++, p + 1, 1) == -1)
		err(1, "setenv: cannot set %s=%s", *argv, p + 1);
	    *p = '=';
	}

	/* Set limits */
	for (rcswhich = 0; rcswhich < RLIM_NLIMITS; rcswhich++) {
	    if (doall || num_limits == 0 || which_limits[rcswhich] != 0)
		if (setrlimit(rcswhich, &limits[rcswhich]) == -1)
		    err(1, "setrlimit %s", resources[rcswhich].cap);
	}

	if (*argv == NULL)
	    usage();

	execvp(*argv, argv);
	err(1, "%s", *argv);
    }

    shelltype = doeval ? getshelltype() : SH_NONE;

    if (type == ANY) /* Default to soft limits */
	type = SOFT;

    /* Display limits */
    printf(shellparm[shelltype].cmd,
	   lc ? " for class " : " (current)",
	   lc ? lc->lc_class : "");

    for (rcswhich = 0; rcswhich < RLIM_NLIMITS; rcswhich++) {
	if (doall || num_limits == 0 || which_limits[rcswhich] != 0) {
	    if (which_limits[rcswhich] == ANY)
		which_limits[rcswhich] = type;
	    if (shellparm[shelltype].lprm[rcswhich].pfx) {
		if (shellparm[shelltype].both && limits[rcswhich].rlim_cur == limits[rcswhich].rlim_max) {
		    print_limit(limits[rcswhich].rlim_max,
				shellparm[shelltype].lprm[rcswhich].divisor,
				shellparm[shelltype].inf,
				shellparm[shelltype].lprm[rcswhich].pfx,
				shellparm[shelltype].lprm[rcswhich].sfx,
				shellparm[shelltype].both);
		} else {
		    if (which_limits[rcswhich] & HARD) {
			print_limit(limits[rcswhich].rlim_max,
				    shellparm[shelltype].lprm[rcswhich].divisor,
				    shellparm[shelltype].inf,
				    shellparm[shelltype].lprm[rcswhich].pfx,
				    shellparm[shelltype].lprm[rcswhich].sfx,
				    shellparm[shelltype].hard);
		    }
		    if (which_limits[rcswhich] & SOFT) {
			print_limit(limits[rcswhich].rlim_cur,
				    shellparm[shelltype].lprm[rcswhich].divisor,
				    shellparm[shelltype].inf,
				    shellparm[shelltype].lprm[rcswhich].pfx,
				    shellparm[shelltype].lprm[rcswhich].sfx,
				    shellparm[shelltype].soft);
		    }
		}
	    }
	}
    }

    login_close(lc);
    exit(EXIT_SUCCESS);
}