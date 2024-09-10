/*ARGSUSED*/
void
domigrate(Char **v, struct command *c)
{
    struct sf *st;
    char   *s;
    Char   *cp;
    struct process *pp;
    int    err1 = 0;
    int    pid = 0;
    siteno_t new_site = 0;

    pchild_disabled++;
    cleanup_push(&pchild_disabled, disabled_cleanup);
    if (setintr) {
	pintr_disabled++;
	cleanup_push(&pintr_disabled, disabled_cleanup);
    }

    ++v;
    if (*v[0] == '-') {
	/*
	 * Do the -site.
	 */
	s = short2str(&v[0][1]);
	/*
	 * see comment in setspath()
	 */
	dont_free = 1;
	if ((st = sfname(s)) == NULL) {
	    dont_free = 0;
	    setname(s);
	    stderror(ERR_NAME | ERR_STRING, CGETS(23, 7, "Site not found"));
	}
	dont_free = 0;
	new_site = st->sf_id;
	++v;
    }

    if (!*v || *v[0] == '\0') {
	if (migratepid(0, new_site) == -1)
	    err1++;
    }
    else {
	Char **globbed;

	v = glob_all_or_error(v);
	globbed = v;
	cleanup_push(globbed, blk_cleanup);

	while (v && (cp = *v)) {
	    if (*cp == '%') {
		pp = pfind(cp);
		if (kill3(- pp->p_jobid, SIGMIGRATE, new_site) < 0) {
		    xprintf("%S: %s\n", cp, strerror(errno));
		    err1++;
		}
	    }
	    else if (!(Isdigit(*cp) || *cp == '-'))
		stderror(ERR_NAME | ERR_JOBARGS);
	    else {
		pid = atoi(short2str(cp));
		if (migratepid(pid, new_site) == -1)
		    err1++;
	    }
	    v++;
	}
	cleanup_until(globbed);
    }

done:
    cleanup_until(&pchild_disabled);
    if (err1)
	stderror(ERR_SILENT);
}