/*
 * Print info about the process.
 */
static int
prcom(int found, psinfo_t *psinfo, char *psargs)
{
	char	*cp;
	char	*tp;
	char	*psa;
	long	tm;
	int	i, wcnt, length;
	wchar_t	wchar;
	struct tty *ttyp;

	/*
	 * If process is zombie, call print routine and return.
	 */
	if (psinfo->pr_nlwp == 0) {
		if (tflg && !found)
			return (0);
		else {
			przom(psinfo);
			return (1);
		}
	}

	/*
	 * Get current terminal.  If none ("?") and 'a' is set, don't print
	 * info.  If 't' is set, check if term is in list of desired terminals
	 * and print it if it is.
	 */
	i = 0;
	tp = gettty(psinfo);

	if (*tp == '?' && !found && !xflg)
		return (0);

	if (!(*tp == '?' && aflg) && tflg && !found) {
		int match = 0;
		char *other = NULL;
		for (ttyp = tty; ttyp->tname != NULL; ttyp++) {
			/*
			 * Look for a name match
			 */
			if (strcmp(tp, ttyp->tname) == 0) {
				match = 1;
				break;
			}
			/*
			 * Look for same device under different names.
			 */
			if ((other == NULL) &&
			    (psinfo->pr_ttydev == ttyp->tdev))
				other = ttyp->tname;
		}
		if (!match) {
			if (other == NULL)
				return (0);
			tp = other;
		}
	}

	if (lflg)
		(void) printf("%2x", psinfo->pr_flag & 0377);
	if (uflg) {
		if (!nflg) {
			struct passwd *pwd;

			if ((pwd = getpwuid(psinfo->pr_euid)) != NULL)
								/* USER */
				(void) printf("%-8.8s", pwd->pw_name);
			else
								/* UID */
				(void) printf(" %7.7d", (int)psinfo->pr_euid);
		} else {
			(void) printf(" %5d", (int)psinfo->pr_euid); /* UID */
		}
	} else if (lflg)
		(void) printf(" %5d", (int)psinfo->pr_euid);	/* UID */

	(void) printf("%*d", pidwidth + 1, (int)psinfo->pr_pid); /* PID */
	if (lflg)
		(void) printf("%*d", pidwidth + 1,
		    (int)psinfo->pr_ppid); /* PPID */
	if (lflg)
		(void) printf("%3d", psinfo->pr_lwp.pr_cpu & 0377); /* CP */
	if (uflg) {
		prtpct(psinfo->pr_pctcpu);			/* %CPU */
		prtpct(psinfo->pr_pctmem);			/* %MEM */
	}
	if (lflg) {
		(void) printf("%4d", psinfo->pr_lwp.pr_pri);	/* PRI */
		(void) printf("%3d", psinfo->pr_lwp.pr_nice);	/* NICE */
	}
	if (lflg || uflg) {
		if (psinfo->pr_flag & SSYS)			/* SZ */
			(void) printf("    0");
		else if (psinfo->pr_size)
			(void) printf(" %4lu", (ulong_t)psinfo->pr_size);
		else
			(void) printf("    ?");
		if (psinfo->pr_flag & SSYS)			/* RSS */
			(void) printf("    0");
		else if (psinfo->pr_rssize)
			(void) printf(" %4lu", (ulong_t)psinfo->pr_rssize);
		else
			(void) printf("    ?");
	}
	if (lflg) {						/* WCHAN */
		if (psinfo->pr_lwp.pr_sname != 'S') {
			(void) printf("         ");
		} else if (psinfo->pr_lwp.pr_wchan) {
			(void) printf(" %+8.8lx",
			    (ulong_t)psinfo->pr_lwp.pr_wchan);
		} else {
			(void) printf("        ?");
		}
	}
	if ((tplen = strlen(tp)) > 9)
		maxlen = twidth - tplen + 9;
	else
		maxlen = twidth;

	if (!lflg)
		(void) printf(" %-8.14s", tp);			/* TTY */
	(void) printf(" %c", psinfo->pr_lwp.pr_sname);		/* STATE */
	if (lflg)
		(void) printf(" %-8.14s", tp);			/* TTY */
	if (uflg)
		prtime(psinfo->pr_start);			/* START */

	/* time just for process */
	tm = psinfo->pr_time.tv_sec;
	if (Sflg) {	/* calculate time for process and all reaped children */
		tm += psinfo->pr_ctime.tv_sec;
		if (psinfo->pr_time.tv_nsec + psinfo->pr_ctime.tv_nsec
		    >= 1000000000)
			tm += 1;
	}

	(void) printf(" %2ld:%.2ld", tm / 60, tm % 60);		/* TIME */

	if (vflg) {
		if (psinfo->pr_flag & SSYS)			/* SZ */
			(void) printf("    0");
		else if (psinfo->pr_size)
			(void) printf("%5lu", (ulong_t)psinfo->pr_size);
		else
			(void) printf("    ?");
		if (psinfo->pr_flag & SSYS)			/* SZ */
			(void) printf("    0");
		else if (psinfo->pr_rssize)
			(void) printf("%5lu", (ulong_t)psinfo->pr_rssize);
		else
			(void) printf("    ?");
		prtpct(psinfo->pr_pctcpu);			/* %CPU */
		prtpct(psinfo->pr_pctmem);			/* %MEM */
	}
	if (cflg) {						/* CMD */
		wcnt = namencnt(psinfo->pr_fname, 16, maxlen);
		(void) printf(" %.*s", wcnt, psinfo->pr_fname);
		return (1);
	}
	/*
	 * PRARGSZ == length of cmd arg string.
	 */
	if (psargs == NULL) {
		psa = &psinfo->pr_psargs[0];
		i = PRARGSZ;
		tp = &psinfo->pr_psargs[PRARGSZ];
	} else {
		psa = psargs;
		i = strlen(psargs);
		tp = psa + i;
	}

	for (cp = psa; cp < tp; /* empty */) {
		if (*cp == 0)
			break;
		length = mbtowc(&wchar, cp, MB_LEN_MAX);
		if (length < 0 || !iswprint(wchar)) {
			(void) printf(" [ %.16s ]", psinfo->pr_fname);
			return (1);
		}
		cp += length;
	}
	wcnt = namencnt(psa, i, maxlen);
#if 0
	/* dumps core on really long strings */
	(void) printf(" %.*s", wcnt, psa);
#else
	(void) putchar(' ');
	(void) fwrite(psa, 1, wcnt, stdout);
#endif
	return (1);
}