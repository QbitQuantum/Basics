static char *
reqpath(char *file, char **idnumber)
{
	char	*path;
	char	*cp;
	char	*cp2;

	/*
	 *	/var/spool/lp/tmp/machine/123-0
	 *	/var/spool/lp/temp/123-0
	 *	/usr/spool/lp/temp/123-0
	 *	/usr/spool/lp/tmp/machine/123-0
	 *	123-0
	 *	machine/123-0
	 *
	 *	/var/spool/lp/tmp/machine/123-0 + 123
	 */
	if (*file == '/') {
		/*CONSTCOND*/
		if (STRNEQU(file, Lp_Spooldir, strlen(Lp_Spooldir)))
			cp = file + strlen(Lp_Spooldir) + 1;
		else {
			if (STRNEQU(file, "/usr/spool/lp", 13))
				cp = file + strlen("/usr/spool/lp") + 1;
			else {
				*idnumber = NULL;
				return (NULL);
			}
		}

		if (STRNEQU(cp, "temp", 4)) {
			cp += 5;
			path = makepath(Local_System, cp, NULL);
		}
		else
			path = Strdup(cp);
	}
	else
	{
		if (strchr(file, '/'))
			path = makepath(file, NULL);
		else
			path = makepath(Local_System, file, NULL);
	}

	cp = strrchr(path, '/');
	cp++;
	if ((cp2 = strrchr(cp, '-')) == NULL)
		*idnumber = Strdup(cp);
	else
	{
		*cp2 = '\0';
		*idnumber = Strdup(cp);
		*cp2 = '-';
	}

	return (path);
}