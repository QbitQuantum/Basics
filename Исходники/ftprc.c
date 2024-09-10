int thrash_rc(void)
{
	struct stat			st;
	string				word, str;
	longstring			cwd;
	char				*cp, *dp, *rc;
	FILE				*fp;
	int					i;

	(void) get_cwd(cwd, sizeof(cwd));
	if (cwd[strlen(cwd) - 1] != '/')
		(void) Strncat(cwd, "/");

	/* Because some versions of regular ftp complain about ncftp's
	 * #set commands, FTPRC takes precedence over NETRC.
	 */
	cp = getenv("DOTDIR");
	for (i=0; i<2; i++) {
		rc = (i == 0) ? FTPRC : NETRC;

		(void) sprintf(rcname, "%s%s", cwd, rc);
		if (stat(rcname, &st) == 0)
			goto foundrc;
		
		(void) sprintf(rcname, "%s.%s", cwd, rc);
		if (stat(rcname, &st) == 0)
			goto foundrc;

		if (cp != NULL) {
			(void) sprintf(rcname, "%s/.%s", cp, rc);
			if (stat(rcname, &st) == 0)
				goto foundrc;
		}

		(void) sprintf(rcname, "%s/.%s", uinfo.homedir, rc);
		if (stat(rcname, &st) == 0)
			goto foundrc;
	}

	return (0);	/* it's OK not to have an rc. */
	
foundrc:	
	if ((st.st_mode & 077) != 0)				/* rc must be unreadable by others. */
		(void) chmod(rcname, 0600);

	if ((fp = fopen(rcname, "r")) == NULL) {
		PERROR("thrash_rc", rcname);
		return -1;
	}
	
	parsing_rc = 1;
	while ((cp = FGets(str, fp)) != 0) {
		while (isspace(*cp)) ++cp;		/* skip leading space. */
		if (*cp == '#') {
			if ((strncmp("set", ++cp, (size_t)3) == 0) || (strncmp("unset", cp, (size_t)5) == 0)) {
				(void) strcpy(line, cp);
				makeargv();
				(void) set(margc, margv);			
				/* setting or unsetting a variable. */
			} /* else a comment. */
		} else {
			if (strncmp(cp, "machine", (size_t) 7) == 0) {
				/* We have a new machine record. */
				cp += 7;
				while (isspace(*cp)) ++cp;	/* skip delimiting space. */
				dp = word;
				while (*cp && !isspace(*cp)) *dp++ = *cp++;	/* copy the name. */
				*dp = 0;
				AddNewSitePtr(word);
			}
		}
	}
	(void) fclose(fp);
	parsing_rc = 0;
	return 1;
}	/* thrash_rc */