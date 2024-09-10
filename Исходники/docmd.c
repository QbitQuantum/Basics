/*
 * Process commands for comparing files to time stamp files.
 */
static void
dodcolon(struct cmd *cmd, char **filev)
{
	struct subcmd *sc;
	struct namelist *f;
	char *cp, **cpp;
	struct stat stb;
	struct namelist *files = cmd->c_files;
	struct subcmd *sbcmds = cmd->c_cmds;
	char *env, *stamp = cmd->c_name;

	debugmsg(DM_CALL, "dodcolon()");

	if (files == NULL) {
		error("No files to be updated for target \"%s\"", 
		      cmd->c_label);
		return;
	}
	if (stat(stamp, &stb) < 0) {
		error("%s: stat failed: %s", stamp, SYSERR);
		return;
	}

	debugmsg(DM_MISC, "%s: mtime %d\n", stamp, stb.st_mtime);

	env = NULL;
	for (sc = sbcmds; sc != NULL; sc = sc->sc_next) {
		if (sc->sc_type == CMDSPECIAL) {
			env = (char *) xmalloc(sizeof(E_FILES) + 3);
			(void) snprintf(env, sizeof(E_FILES) + 3,
					"%s='", E_FILES);
			break;
		}
	}

	subcmds = sbcmds;
	filelist = files;

	lastmod = stb.st_mtime;
	if (!nflag && !IS_ON(options, DO_VERIFY))
		/*
		 * Set atime and mtime to current time
		 */
		(void) setfiletime(stamp, (time_t) 0, (time_t) 0);

	for (f = files; f != NULL; f = f->n_next) {
		if (filev) {
			for (cpp = filev; *cpp; cpp++)
				if (strcmp(f->n_name, *cpp) == 0)
					goto found;
			continue;
		}
	found:
		ptarget = NULL;
		cmptime(f->n_name, sbcmds, &env);
	}

	for (sc = sbcmds; sc != NULL; sc = sc->sc_next) {
		if (sc->sc_type == NOTIFY)
			notify(NULL, sc->sc_args, (time_t)lastmod);
		else if (sc->sc_type == CMDSPECIAL && env) {
			size_t len = strlen(env);
			if (env[len - 1] == ':')
				env[--len] = CNULL;
			len += 2 + strlen(sc->sc_name) + 1;
			env = xrealloc(env, len);
			(void) strlcat(env, "';", len);
			(void) strlcat(env, sc->sc_name, len);
			message(MT_CHANGE, "cmdspecial \"%s\"", env);
			if (!nflag && IS_OFF(options, DO_VERIFY))
				runcommand(env);
			(void) free(env);
			env = NULL;	/* so cmdspecial is only called once */
		}
	}
	if (!nflag && !IS_ON(options, DO_VERIFY) && (cp = getnotifyfile()))
		(void) unlink(cp);
}