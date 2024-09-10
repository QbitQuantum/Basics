/*
 * cvs_read_rcfile()
 *
 * Read the CVS `.cvsrc' file in the user's home directory.  If the file
 * exists, it should contain a list of arguments that should always be given
 * implicitly to the specified commands.
 */
static void
cvs_read_rcfile(void)
{
	char rcpath[MAXPATHLEN], *buf, *lbuf, *lp, *p;
	int cmd_parsed, cvs_parsed, i, linenum;
	size_t len, pos;
	struct cvs_cmd *tcmdp;
	FILE *fp;

	linenum = 0;

	i = snprintf(rcpath, MAXPATHLEN, "%s/%s", cvs_homedir, CVS_PATH_RC);
	if (i < 0 || i >= MAXPATHLEN) {
		cvs_log(LP_ERRNO, "%s", rcpath);
		return;
	}

	fp = fopen(rcpath, "r");
	if (fp == NULL) {
		if (errno != ENOENT)
			cvs_log(LP_NOTICE, "failed to open `%s': %s", rcpath,
			    strerror(errno));
		return;
	}

	cmd_parsed = cvs_parsed = 0;
	lbuf = NULL;
	while ((buf = fgetln(fp, &len)) != NULL) {
		if (buf[len - 1] == '\n') {
			buf[len - 1] = '\0';
		} else {
			lbuf = xmalloc(len + 1);
			memcpy(lbuf, buf, len);
			lbuf[len] = '\0';
			buf = lbuf;
		}

		linenum++;

		/* skip any whitespaces */
		p = buf;
		while (*p == ' ')
			p++;

		/*
		 * Allow comments.
		 * GNU cvs stops parsing a line if it encounters a \t
		 * in front of a command, stick at this behaviour for
		 * compatibility.
		 */
		if (*p == '#' || *p == '\t')
			continue;

		pos = strcspn(p, " \t");
		if (pos == strlen(p)) {
			lp = NULL;
		} else {
			lp = p + pos;
			*lp = '\0';
		}

		if (strcmp(p, "cvs") == 0 && !cvs_parsed) {
			/*
			 * Global default options.  In the case of cvs only,
			 * we keep the 'cvs' string as first argument because
			 * getopt() does not like starting at index 0 for
			 * argument processing.
			 */
			if (lp != NULL) {
				*lp = ' ';
				cvs_defargs = xstrdup(p);
			}
			cvs_parsed = 1;
		} else {
			tcmdp = cvs_findcmd(p);
			if (tcmdp == NULL && verbosity == 2)
				cvs_log(LP_NOTICE,
				    "unknown command `%s' in `%s:%d'",
				    p, rcpath, linenum);

			if (tcmdp != cmdp || cmd_parsed)
				continue;

			if (lp != NULL) {
				lp++;
				cmdp->cmd_defargs = xstrdup(lp);
			}
			cmd_parsed = 1;
		}
	}
	if (lbuf != NULL)
		xfree(lbuf);

	if (ferror(fp)) {
		cvs_log(LP_NOTICE, "failed to read line from `%s'", rcpath);
	}

	(void)fclose(fp);
}