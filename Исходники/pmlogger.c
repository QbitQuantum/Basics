/*
 * generate dialog/message when launching application wishes to break
 * its association with pmlogger
 *
 * cmd is one of the following:
 *	D	detach pmlogger and let it run forever
 *	Q	terminate pmlogger
 *	?	display status
 *	X	fatal error or application exit ... user must decide
 *		to detach or quit
 */
void
do_dialog(char cmd)
{
    FILE	*msgf = NULL;
    time_t	now;
    static char	lbuf[100+MAXPATHLEN];
    double	archsize;
    char	*q;
    char	*p = NULL;
    int		nchar;
    char	*msg;
#if HAVE_MKSTEMP
    char	tmp[MAXPATHLEN];
#endif

    time(&now);
    now -= rsc_start;
    if (now == 0)
	/* hack is close enough! */
	now = 1;

    archsize = vol_bytes + ftell(logctl.l_mfp);

    nchar = add_msg(&p, 0, "");
    p[0] = '\0';

    snprintf(lbuf, sizeof(lbuf), "PCP recording for the archive folio \"%s\" and the host", folio_name);
    nchar = add_msg(&p, nchar, lbuf);
    if (now < 240)
	snprintf(lbuf, sizeof(lbuf), " \"%s\" has been in progress for %ld seconds",
	pmcd_host, (long)now);
    else
	snprintf(lbuf, sizeof(lbuf), " \"%s\" has been in progress for %ld minutes",
	pmcd_host, (long)((now + 30)/60));
    nchar = add_msg(&p, nchar, lbuf);
    nchar = add_msg(&p, nchar, " and in that time the pmlogger process has created an");
    nchar = add_msg(&p, nchar, " archive of ");
    q = do_size(archsize);
    nchar = add_msg(&p, nchar, q);
    nchar = add_msg(&p, nchar, ".");
    if (rsc_replay) {
	nchar = add_msg(&p, nchar, "\n\nThis archive may be replayed with the following command:\n");
	snprintf(lbuf, sizeof(lbuf), "  $ pmafm %s replay", folio_name);
	nchar = add_msg(&p, nchar, lbuf);
    }

    if (cmd == 'D') {
	nchar = add_msg(&p, nchar, "\n\nThe application that launched pmlogger has asked pmlogger");
	nchar = add_msg(&p, nchar, " to continue independently and the PCP archive will grow at");
	nchar = add_msg(&p, nchar, " the rate of ");
	q = do_size((archsize * 3600) / now);
	nchar = add_msg(&p, nchar, q);
	nchar = add_msg(&p, nchar, " per hour or ");
	q = do_size((archsize * 3600 * 24) / now);
	nchar = add_msg(&p, nchar, q);
	nchar = add_msg(&p, nchar, " per day.");
    }

    if (cmd == 'X') {
	nchar = add_msg(&p, nchar, "\n\nThe application that launched pmlogger has exited and you");
	nchar = add_msg(&p, nchar, " must decide if the PCP recording session should be terminated");
	nchar = add_msg(&p, nchar, " or continued.  If recording is continued the PCP archive will");
	nchar = add_msg(&p, nchar, " grow at the rate of ");
	q = do_size((archsize * 3600) / now);
	nchar = add_msg(&p, nchar, q);
	nchar = add_msg(&p, nchar, " per hour or ");
	q = do_size((archsize * 3600 * 24) / now);
	nchar = add_msg(&p, nchar, q);
	nchar = add_msg(&p, nchar, " per day.");
    }

    if (cmd == 'Q') {
	nchar = add_msg(&p, nchar, "\n\nThe application that launched pmlogger has terminated");
	nchar = add_msg(&p, nchar, " this PCP recording session.\n");
    }

    if (cmd != 'Q') {
	nchar = add_msg(&p, nchar, "\n\nAt any time this pmlogger process may be terminated with the");
	nchar = add_msg(&p, nchar, " following command:\n");
	snprintf(lbuf, sizeof(lbuf), "  $ pmsignal -s TERM %" FMT_PID "\n", getpid());
	nchar = add_msg(&p, nchar, lbuf);
    }

    if (cmd == 'X')
	nchar = add_msg(&p, nchar, "\n\nTerminate this PCP recording session now?");

    if (nchar > 0) {
	char * xconfirm = __pmNativePath(pmGetConfig("PCP_XCONFIRM_PROG"));
	int fd = -1;

#if HAVE_MKSTEMP
	snprintf(tmp, sizeof(tmp), "%s%cmsgXXXXXX", pmGetConfig("PCP_TMPFILE_DIR"), __pmPathSeparator());
	msg = tmp;
	fd = mkstemp(tmp);
#else
	if ((msg = tmpnam(NULL)) != NULL)
	    fd = open(msg, O_WRONLY|O_CREAT|O_EXCL, 0600);
#endif
	if (fd >= 0)
	    msgf = fdopen(fd, "w");
	if (msgf == NULL) {
	    fprintf(stderr, "\nError: failed create temporary message file for recording session dialog\n");
	    fprintf(stderr, "Reason? %s\n", osstrerror());
	    if (fd != -1)
		close(fd);
	    goto failed;
	}
	fputs(p, msgf);
	fclose(msgf);
	msgf = NULL;

	if (cmd == 'X')
	    snprintf(lbuf, sizeof(lbuf), "%s -c -header \"%s - %s\" -file %s -icon question "
			  "-B Yes -b No 2>/dev/null",
		    xconfirm, dialog_title, rsc_prog, msg);
	else
	    snprintf(lbuf, sizeof(lbuf), "%s -c -header \"%s - %s\" -file %s -icon info "
			  "-b Close 2>/dev/null",
		    xconfirm, dialog_title, rsc_prog, msg);

	if ((msgf = popen(lbuf, "r")) == NULL) {
	    fprintf(stderr, "\nError: failed to start command for recording session dialog\n");
	    fprintf(stderr, "Command: \"%s\"\n", lbuf);
	    goto failed;
	}

	if (fgets(lbuf, sizeof(lbuf), msgf) == NULL) {
	    fprintf(stderr, "\n%s: pmconfirm(1) failed for recording session dialog\n",
		    cmd == '?' ? "Warning" : "Error");
failed:
	    fprintf(stderr, "Dialog:\n");
	    fputs(p, stderr);
	    strcpy(lbuf, "Yes");
	}
	else {
	    /* strip at first newline */
	    for (q = lbuf; *q && *q != '\n'; q++)
		;
	    *q = '\0';
	}

	if (msgf != NULL)
	    pclose(msgf);
	unlink(msg);
    }
    else {
	fprintf(stderr, "Error: failed to create recording session dialog message!\n");
	fprintf(stderr, "Reason? %s\n", osstrerror());
	strcpy(lbuf, "Yes");
    }

    free(p);

    if (cmd == 'Q' || (cmd == 'X' && strcmp(lbuf, "Yes") == 0)) {
	run_done(0, "Recording session terminated");
	/*NOTREACHED*/
    }

    if (cmd != '?') {
	/* detach, silently go off to the races ... */
	close(rsc_fd);
	__pmFD_CLR(rsc_fd, &fds);
	rsc_fd = -1;
    }
}