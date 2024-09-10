/*
 * Execute the shell command tree pointed to by t.
 */
static void
execute(struct tnode *t, int *pin, int *pout)
{
	struct tnode *t1;
	enum tnflags f;
	pid_t cpid;
	int i, pfd[2];
	const char **gav;
	const char *cmd, *p;

	if (t == NULL)
		return;
	switch (t->ntype) {
	case TLIST:
		f = t->nflags & (FFIN | FPIN | FINTR);
		if ((t1 = t->nleft) != NULL)
			t1->nflags |= f;
		execute(t1, NULL, NULL);
		if ((t1 = t->nright) != NULL)
			t1->nflags |= f;
		execute(t1, NULL, NULL);
		return;

	case TPIPE:
		if (pipe(pfd) == -1) {
			err(SH_ERR, FMT1S, ERR_PIPE);
			if (pin != NULL) {
				(void)close(pin[0]);
				(void)close(pin[1]);
			}
			return;
		}
		f = t->nflags;
		if ((t1 = t->nleft) != NULL)
			t1->nflags |= FPOUT | (f & (FFIN|FPIN|FINTR|FPRS));
		execute(t1, pin, pfd);
		if ((t1 = t->nright) != NULL)
			t1->nflags |= FPIN | (f & (FAND|FPOUT|FINTR|FPRS));
		execute(t1, pfd, pout);
		(void)close(pfd[0]);
		(void)close(pfd[1]);
		return;

	case TCOMMAND:
		if (t->nav == NULL || t->nav[0] == NULL) {
			/* should never (but can) be true */
			err(SH_ERR, FMT1S, "execute: Invalid command");
			return;
		}
		cmd = t->nav[0];
		if (EQUAL(cmd, ":")) {
			status = SH_TRUE;
			return;
		}
		if (EQUAL(cmd, "chdir")) {
			ascan(t->nav[1], &trim);
			if (t->nav[1] == NULL)
				err(SH_ERR, FMT2S, cmd, ERR_ARGCOUNT);
			else if (chdir(t->nav[1]) == -1)
				err(SH_ERR, FMT2S, cmd, ERR_BADDIR);
			else
				status = SH_TRUE;
			return;
		}
		if (EQUAL(cmd, "exit")) {
			if (prompt == NULL) {
				(void)lseek(FD0, (off_t)0, SEEK_END);
				EXIT(status);
			}
			return;
		}
		if (EQUAL(cmd, "login") || EQUAL(cmd, "newgrp")) {
			if (prompt != NULL) {
				p = (*cmd == 'l') ? PATH_LOGIN : PATH_NEWGRP;
				vscan(t->nav, &trim);
				(void)sasignal(SIGINT, SIG_DFL);
				(void)sasignal(SIGQUIT, SIG_DFL);
				(void)pexec(p, (char *const *)t->nav);
				(void)sasignal(SIGINT, SIG_IGN);
				(void)sasignal(SIGQUIT, SIG_IGN);
			}
			err(SH_ERR, FMT2S, cmd, ERR_EXEC);
			return;
		}
		if (EQUAL(cmd, "shift")) {
			if (dolc > 1) {
				dolv = &dolv[1];
				dolc--;
				status = SH_TRUE;
				return;
			}
			err(SH_ERR, FMT2S, cmd, ERR_NOARGS);
			return;
		}
		if (EQUAL(cmd, "wait")) {
			pwait(-1);
			return;
		}
		/*FALLTHROUGH*/

	case TSUBSHELL:
		f = t->nflags;
		if ((cpid = ((f & FNOFORK) != 0) ? 0 : fork()) == -1) {
			err(SH_ERR, FMT1S, ERR_FORK);
			return;
		}
		/**** Parent! ****/
		if (cpid != 0) {
			if (pin != NULL && (f & FPIN) != 0) {
				(void)close(pin[0]);
				(void)close(pin[1]);
			}
			if ((f & FPRS) != 0)
				fd_print(FD2, "%u\n", (unsigned)cpid);
			if ((f & FAND) != 0)
				return;
			if ((f & FPOUT) == 0)
				pwait(cpid);
			return;
		}
		/**** Child! ****/
		/*
		 * Redirect (read) input from pipe.
		 */
		if (pin != NULL && (f & FPIN) != 0) {
			if (dup2(pin[0], FD0) == -1)
				err(FC_ERR, FMT1S, strerror(errno));
			(void)close(pin[0]);
			(void)close(pin[1]);
		}
		/*
		 * Redirect (write) output to pipe.
		 */
		if (pout != NULL && (f & FPOUT) != 0) {
			if (dup2(pout[1], FD1) == -1)
				err(FC_ERR, FMT1S, strerror(errno));
			(void)close(pout[0]);
			(void)close(pout[1]);
		}
		/*
		 * Redirect (read) input from file.
		 */
		if (t->nfin != NULL && (f & FPIN) == 0) {
			f |= FFIN;
			ascan(t->nfin, &trim);
			if ((i = open(t->nfin, O_RDONLY)) == -1)
				err(FC_ERR, FMT2S, t->nfin, ERR_OPEN);
			if (dup2(i, FD0) == -1)
				err(FC_ERR, FMT1S, strerror(errno));
			(void)close(i);
		}
		/*
		 * Redirect (write) output to file.
		 */
		if (t->nfout != NULL && (f & FPOUT) == 0) {
			if ((f & FCAT) != 0)
				i = O_WRONLY | O_APPEND | O_CREAT;
			else
				i = O_WRONLY | O_TRUNC | O_CREAT;
			ascan(t->nfout, &trim);
			if ((i = open(t->nfout, i, 0666)) == -1)
				err(FC_ERR, FMT2S, t->nfout, ERR_CREATE);
			if (dup2(i, FD1) == -1)
				err(FC_ERR, FMT1S, strerror(errno));
			(void)close(i);
		}
		/*
		 * Set the action for the SIGINT and SIGQUIT signals, and
		 * redirect input for `&' commands from `/dev/null' if needed.
		 */
		if ((f & FINTR) != 0) {
			(void)sasignal(SIGINT, SIG_IGN);
			(void)sasignal(SIGQUIT, SIG_IGN);
			if (t->nfin == NULL && (f & (FFIN|FPIN|FPRS)) == FPRS) {
				(void)close(FD0);
				if (open("/dev/null", O_RDONLY) != FD0)
					err(FC_ERR,FMT2S,"/dev/null",ERR_OPEN);
			}
		} else {
			if ((sig_child & S_SIGINT) != 0)
				(void)sasignal(SIGINT, SIG_DFL);
			if ((sig_child & S_SIGQUIT) != 0)
				(void)sasignal(SIGQUIT, SIG_DFL);
		}
		/* Set the SIGTERM signal to its default action if needed. */
		if ((sig_child & S_SIGTERM) != 0)
			(void)sasignal(SIGTERM, SIG_DFL);
		if (t->ntype == TSUBSHELL) {
			if ((t1 = t->nsub) != NULL)
				t1->nflags |= (f & (FFIN | FPIN | FINTR));
			execute(t1, NULL, NULL);
			_exit(status);
		}
		glob_flag = false;
		vscan(t->nav, &tglob);
		if (glob_flag) {
			for (i = 0; t->nav[i] != NULL; i++)
				;	/* nothing */
#ifdef	DEBUG
#ifdef	DEBUG_GLOB
			fd_print(FD2, "execute:  i      == %2d;\n", i);
			fd_print(FD2, "       : (i + 2) == %2d;\n", (i + 2));
			fd_print(FD2, "       : (i + 1) == %2d;\n", (i + 1));
#endif
#endif
			gav = xmalloc((i + 2) * sizeof(char *));
			gav[0] = "glob6";
			cmd = gav[0];
			(void)memcpy(&gav[1], t->nav, (i + 1) * sizeof(char *));
#ifdef	DEBUG
#ifdef	DEBUG_GLOB
			for (i = 0; gav[i] != NULL; i++)
				fd_print(FD2, "       : gav[%2d] == %s;\n",
				    i, gav[i]);
			fd_print(FD2, "       : gav[%2d] == NULL;\n", i);
#endif
#endif
			(void)err_pexec(cmd, (char *const *)gav);
		} else {
			vscan(t->nav, &trim);
			cmd = t->nav[0];
			(void)err_pexec(cmd, (char *const *)t->nav);
		}
		/*NOTREACHED*/
	}
}