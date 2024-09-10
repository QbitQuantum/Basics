FILE *
collect(struct header *hp, int printheaders)
{
	FILE *fbuf;
	int lc, cc, escape, eofcount, fd, c, t;
	char linebuf[LINESIZE], tempname[PATHSIZE], *cp, getsub;
	sigset_t nset;
	int longline, lastlong, rc;	/* So we don't make 2 or more lines
					   out of a long input line. */

	collf = NULL;
	/*
	 * Start catching signals from here, but we're still die on interrupts
	 * until we're in the main loop.
	 */
	(void)sigemptyset(&nset);
	(void)sigaddset(&nset, SIGINT);
	(void)sigaddset(&nset, SIGHUP);
	(void)sigprocmask(SIG_BLOCK, &nset, NULL);
	if ((saveint = signal(SIGINT, SIG_IGN)) != SIG_IGN)
		(void)signal(SIGINT, collint);
	if ((savehup = signal(SIGHUP, SIG_IGN)) != SIG_IGN)
		(void)signal(SIGHUP, collhup);
	savetstp = signal(SIGTSTP, collstop);
	savettou = signal(SIGTTOU, collstop);
	savettin = signal(SIGTTIN, collstop);
	if (setjmp(collabort) || setjmp(colljmp)) {
		(void)rm(tempname);
		goto err;
	}
	(void)sigprocmask(SIG_UNBLOCK, &nset, NULL);

	noreset++;
	(void)snprintf(tempname, sizeof(tempname),
	    "%s/mail.RsXXXXXXXXXX", tmpdir);
	if ((fd = mkstemp(tempname)) == -1 ||
	    (collf = Fdopen(fd, "w+")) == NULL) {
		warn("%s", tempname);
		goto err;
	}
	(void)rm(tempname);

	/*
	 * If we are going to prompt for a subject,
	 * refrain from printing a newline after
	 * the headers (since some people mind).
	 */
	t = GTO|GSUBJECT|GCC|GNL;
	getsub = 0;
	if (hp->h_subject == NULL && value("interactive") != NULL &&
	    (value("ask") != NULL || value("asksub") != NULL))
		t &= ~GNL, getsub++;
	if (printheaders) {
		puthead(hp, stdout, t);
		(void)fflush(stdout);
	}
	if ((cp = value("escape")) != NULL)
		escape = *cp;
	else
		escape = ESCAPE;
	eofcount = 0;
	hadintr = 0;
	lastlong = 0;
	longline = 0;

	if (!setjmp(colljmp)) {
		if (getsub)
			grabh(hp, GSUBJECT);
	} else {
		/*
		 * Come here for printing the after-signal message.
		 * Duplicate messages won't be printed because
		 * the write is aborted if we get a SIGTTOU.
		 */
cont:
		if (hadintr) {
			(void)fflush(stdout);
			fprintf(stderr,
			"\n(Interrupt -- one more to kill letter)\n");
		} else {
			printf("(continue)\n");
			(void)fflush(stdout);
		}
	}
	for (;;) {
		colljmp_p = 1;
		c = readline(stdin, linebuf, LINESIZE);
		colljmp_p = 0;
		if (c < 0) {
			if (value("interactive") != NULL &&
			    value("ignoreeof") != NULL && ++eofcount < 25) {
				printf("Use \".\" to terminate letter\n");
				continue;
			}
			break;
		}
		lastlong = longline;
		longline = c == LINESIZE - 1;
		eofcount = 0;
		hadintr = 0;
		if (linebuf[0] == '.' && linebuf[1] == '\0' &&
		    value("interactive") != NULL && !lastlong &&
		    (value("dot") != NULL || value("ignoreeof") != NULL))
			break;
		if (linebuf[0] != escape || value("interactive") == NULL ||
		    lastlong) {
			if (putline(collf, linebuf, !longline) < 0)
				goto err;
			continue;
		}
		c = linebuf[1];
		switch (c) {
		default:
			/*
			 * On double escape, just send the single one.
			 * Otherwise, it's an error.
			 */
			if (c == escape) {
				if (putline(collf, &linebuf[1], !longline) < 0)
					goto err;
				else
					break;
			}
			printf("Unknown tilde escape.\n");
			break;
		case 'C':
			/*
			 * Dump core.
			 */
			core();
			break;
		case '!':
			/*
			 * Shell escape, send the balance of the
			 * line to sh -c.
			 */
			shell(&linebuf[2]);
			break;
		case ':':
		case '_':
			/*
			 * Escape to command mode, but be nice!
			 */
			execute(&linebuf[2], 1);
			goto cont;
		case '.':
			/*
			 * Simulate end of file on input.
			 */
			goto out;
		case 'q':
			/*
			 * Force a quit of sending mail.
			 * Act like an interrupt happened.
			 */
			hadintr++;
			collint(SIGINT);
			exit(1);
		case 'x':
			/*
			 * Exit, do not save in dead.letter.
			 */
			goto err;
		case 'h':
			/*
			 * Grab a bunch of headers.
			 */
			grabh(hp, GTO|GSUBJECT|GCC|GBCC);
			goto cont;
		case 't':
			/*
			 * Add to the To list.
			 */
			hp->h_to = cat(hp->h_to, extract(&linebuf[2], GTO));
			break;
		case 's':
			/*
			 * Set the Subject line.
			 */
			cp = &linebuf[2];
			while (isspace((unsigned char)*cp))
				cp++;
			hp->h_subject = savestr(cp);
			break;
		case 'R':
			/*
			 * Set the Reply-To line.
			 */
			cp = &linebuf[2];
			while (isspace((unsigned char)*cp))
				cp++;
			hp->h_replyto = savestr(cp);
			break;
		case 'c':
			/*
			 * Add to the CC list.
			 */
			hp->h_cc = cat(hp->h_cc, extract(&linebuf[2], GCC));
			break;
		case 'b':
			/*
			 * Add to the BCC list.
			 */
			hp->h_bcc = cat(hp->h_bcc, extract(&linebuf[2], GBCC));
			break;
		case 'i':
		case 'A':
		case 'a':
			/*
			 * Insert named variable in message.
			 */
			switch(c) {
				case 'i':
					cp = &linebuf[2];
					while(isspace((unsigned char)*cp))
						cp++;
					break;
				case 'a':
					cp = "sign";
					break;
				case 'A':
					cp = "Sign";
					break;
				default:
					goto err;
			}

			if(*cp != '\0' && (cp = value(cp)) != NULL) {
				printf("%s\n", cp);
				if(putline(collf, cp, 1) < 0)
					goto err;
			}

			break;
		case 'd':
			/*
			 * Read in the dead letter file.
			 */
			if (strlcpy(linebuf + 2, getdeadletter(),
				sizeof(linebuf) - 2)
			    >= sizeof(linebuf) - 2) {
				printf("Line buffer overflow\n");
				break;
			}
			/* FALLTHROUGH */
		case 'r':
		case '<':
			/*
			 * Invoke a file:
			 * Search for the file name,
			 * then open it and copy the contents to collf.
			 */
			cp = &linebuf[2];
			while (isspace((unsigned char)*cp))
				cp++;
			if (*cp == '\0') {
				printf("Interpolate what file?\n");
				break;
			}
			cp = expand(cp);
			if (cp == NULL)
				break;
			if (*cp == '!') {
				/*
				 * Insert stdout of command.
				 */
				char *sh;
				int nullfd, tempfd, rc;
				char tempname2[PATHSIZE];

				if ((nullfd = open(_PATH_DEVNULL, O_RDONLY, 0))
				    == -1) {
					warn(_PATH_DEVNULL);
					break;
				}

				(void)snprintf(tempname2, sizeof(tempname2),
				    "%s/mail.ReXXXXXXXXXX", tmpdir);
				if ((tempfd = mkstemp(tempname2)) == -1 ||
				    (fbuf = Fdopen(tempfd, "w+")) == NULL) {
					warn("%s", tempname2);
					break;
				}
				(void)unlink(tempname2);

				if ((sh = value("SHELL")) == NULL)
					sh = _PATH_CSHELL;

				rc = run_command(sh, 0, nullfd, fileno(fbuf),
				    "-c", cp+1, NULL);

				close(nullfd);

				if (rc < 0) {
					(void)Fclose(fbuf);
					break;
				}

				if (fsize(fbuf) == 0) {
					fprintf(stderr,
					    "No bytes from command \"%s\"\n",
					    cp+1);
					(void)Fclose(fbuf);
					break;
				}

				rewind(fbuf);
			} else if (isdir(cp)) {
				printf("%s: Directory\n", cp);
				break;
			} else if ((fbuf = Fopen(cp, "r")) == NULL) {
				warn("%s", cp);
				break;
			}
			printf("\"%s\" ", cp);
			(void)fflush(stdout);
			lc = 0;
			cc = 0;
			while ((rc = readline(fbuf, linebuf, LINESIZE)) >= 0) {
				if (rc != LINESIZE - 1)
					lc++;
				if ((t = putline(collf, linebuf,
					 rc != LINESIZE - 1)) < 0) {
					(void)Fclose(fbuf);
					goto err;
				}
				cc += t;
			}
			(void)Fclose(fbuf);
			printf("%d/%d\n", lc, cc);
			break;
		case 'w':
			/*
			 * Write the message on a file.
			 */
			cp = &linebuf[2];
			while (*cp == ' ' || *cp == '\t')
				cp++;
			if (*cp == '\0') {
				fprintf(stderr, "Write what file!?\n");
				break;
			}
			if ((cp = expand(cp)) == NULL)
				break;
			rewind(collf);
			exwrite(cp, collf, 1);
			break;
		case 'm':
		case 'M':
		case 'f':
		case 'F':
			/*
			 * Interpolate the named messages, if we
			 * are in receiving mail mode.  Does the
			 * standard list processing garbage.
			 * If ~f is given, we don't shift over.
			 */
			if (forward(linebuf + 2, collf, tempname, c) < 0)
				goto err;
			goto cont;
		case '?':
			if ((fbuf = Fopen(_PATH_TILDE, "r")) == NULL) {
				warn("%s", _PATH_TILDE);
				break;
			}
			while ((t = getc(fbuf)) != EOF)
				(void)putchar(t);
			(void)Fclose(fbuf);
			break;
		case 'p':
			/*
			 * Print out the current state of the
			 * message without altering anything.
			 */
			rewind(collf);
			printf("-------\nMessage contains:\n");
			puthead(hp, stdout, GTO|GSUBJECT|GCC|GBCC|GNL);
			while ((t = getc(collf)) != EOF)
				(void)putchar(t);
			goto cont;
		case '|':
			/*
			 * Pipe message through command.
			 * Collect output as new message.
			 */
			rewind(collf);
			mespipe(collf, &linebuf[2]);
			goto cont;
		case 'v':
		case 'e':
			/*
			 * Edit the current message.
			 * 'e' means to use EDITOR
			 * 'v' means to use VISUAL
			 */
			rewind(collf);
			mesedit(collf, c);
			goto cont;
		}
	}
	goto out;
err:
	if (collf != NULL) {
		(void)Fclose(collf);
		collf = NULL;
	}
out:
	if (collf != NULL)
		rewind(collf);
	noreset--;
	(void)sigprocmask(SIG_BLOCK, &nset, NULL);
	(void)signal(SIGINT, saveint);
	(void)signal(SIGHUP, savehup);
	(void)signal(SIGTSTP, savetstp);
	(void)signal(SIGTTOU, savettou);
	(void)signal(SIGTTIN, savettin);
	(void)sigprocmask(SIG_UNBLOCK, &nset, NULL);
	return (collf);
}