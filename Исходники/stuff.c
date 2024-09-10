int do_exec(char* com, char* wd)
{
	char    path[MAXPATHLEN];
	char    pcom[MAXCOMSZ];
	char   *arglist[MAXARGS];
	char   *tz;
	register int i, len;
	register int argptr;
	int     status, pid, w;
	int     pmode;
	void    (*isig) (), (*qsig) ();

	strncpy(path, BINDIR, MAXPATHLEN);
	strncpy(pcom, com, MAXCOMSZ);
	len = Min(strlen(com) + 1, MAXCOMSZ);
	pmode = LOOKFIRST;
	for (i = 0, argptr = 0; i < len; i++)
	{
		if (pcom[i] == '\0')
			break;
		if (pmode == QUOTEMODE)
		{
			if (pcom[i] == '\001')
			{
				pmode = LOOKFIRST;
				pcom[i] = '\0';
				continue;
			}
			continue;
		}
		if (pcom[i] == '\001')
		{
			pmode = QUOTEMODE;
			arglist[argptr++] = &pcom[i + 1];
			if (argptr + 1 == MAXARGS)
				break;
			continue;
		}
		if (pmode == LOOKFIRST)
			if (pcom[i] != ' ')
			{
				arglist[argptr++] = &pcom[i];
				if (argptr + 1 == MAXARGS)
					break;
				pmode = LOOKLAST;
			}
			else
				continue;
		if (pcom[i] == ' ')
		{
			pmode = LOOKFIRST;
			pcom[i] = '\0';
		}
	}
	arglist[argptr] = NULL;
	if (argptr == 0)
		return -1;
	if (*arglist[0] == '/')
		strncpy(path, arglist[0], MAXPATHLEN);
	else
		strncat(path, arglist[0], MAXPATHLEN);
	reset_tty();
	alarm(0);
#ifdef IRIX

	if ((pid = fork()) == 0)
	{
#else
	if ((pid = vfork()) == 0)
	{
#endif

#ifdef BBSD
		waitpid(pid, &status, 0);
#endif

		if (wd)
			if (chdir(wd))
			{
				sprintf(genbuf, "Unable to chdir to '%s'\n", wd);
				report(genbuf);
				exit(-1);
			}

		bbssetenv("PATH", "/bin:.");
		bbssetenv("TERM", currentuser.termtype);
		bbssetenv("USER", currentuser.userid);
		bbssetenv("USERNAME", currentuser.username);

		if ((tz = getenv("TZ")) != NULL)
			bbssetenv("TZ", tz);
		if (numbbsenvs == 0)
			bbsenv[0] = NULL;
		//dup2(0,1);
		//dup2(0,2);
		execve(path, arglist, bbsenv);
		sprintf(genbuf, "EXECV FAILED... path = '%s'\n", path);
		report(genbuf);
		exit(-1);
	}
	isig = signal(SIGINT, SIG_IGN);
	qsig = signal(SIGQUIT, SIG_IGN);
#ifndef BBSD

	while ((w = wait(&status)) != pid && w != 1)
		/* NULL STATEMENT */
		;
#endif

	signal(SIGINT, isig);
	signal(SIGQUIT, qsig);
	restore_tty();
#ifdef DOTIMEOUT

	alarm(IDLE_TIMEOUT);
#endif

	return ((w == -1) ? w : status);
}

char* horoscope(int month, int day)
{
	char   *name[12] = {
	                       "Ä¦ôÉ", "Ë®Æ¿", "Ë«Óã", "ÄµÑò", "½ðÅ£", "Ë«×Ó",
	                       "¾ÞÐ·", "Ê¨×Ó", "´¦Å®", "Ìì³Ó", "ÌìÐ«", "ÉäÊÖ"
	                   };
	switch (month)
	{
	case 1:
		if (day < 21)
			return (name[0]);
		else
			return (name[1]);
	case 2:
		if (day < 19)
			return (name[1]);
		else
			return (name[2]);
	case 3:
		if (day < 21)
			return (name[2]);
		else
			return (name[3]);
	case 4:
		if (day < 21)
			return (name[3]);
		else
			return (name[4]);
	case 5:
		if (day < 21)
			return (name[4]);
		else
			return (name[5]);
	case 6:
		if (day < 22)
			return (name[5]);
		else
			return (name[6]);
	case 7:
		if (day < 23)
			return (name[6]);
		else
			return (name[7]);
	case 8:
		if (day < 23)
			return (name[7]);
		else
			return (name[8]);
	case 9:
		if (day < 23)
			return (name[8]);
		else
			return (name[9]);
	case 10:
		if (day < 24)
			return (name[9]);
		else
			return (name[10]);
	case 11:
		if (day < 23)
			return (name[10]);
		else
			return (name[11]);
	case 12:
		if (day < 22)
			return (name[11]);
		else
			return (name[0]);
	}
	return ("²»Ïê");
}