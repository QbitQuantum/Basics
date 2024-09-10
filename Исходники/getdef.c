static void def_load (void)
{
	int i;
	FILE *fp;
	char buf[1024], *name, *value, *s;

	/*
	 * Open the configuration definitions file.
	 */
	fp = fopen (def_fname, "r");
	if (NULL == fp) {
		int err = errno;
		SYSLOG ((LOG_CRIT, "cannot open login definitions %s [%s]",
		         def_fname, strerror (err)));
		exit (EXIT_FAILURE);
	}

	/*
	 * Set the initialized flag.
	 * (do it early to prevent recursion in putdef_str())
	 */
	def_loaded = true;

	/*
	 * Go through all of the lines in the file.
	 */
	while (fgets (buf, (int) sizeof (buf), fp) != NULL) {

		/*
		 * Trim trailing whitespace.
		 */
		for (i = (int) strlen (buf) - 1; i >= 0; --i) {
			if (!isspace (buf[i])) {
				break;
			}
		}
		i++;
		buf[i] = '\0';

		/*
		 * Break the line into two fields.
		 */
		name = buf + strspn (buf, " \t");	/* first nonwhite */
		if (*name == '\0' || *name == '#')
			continue;	/* comment or empty */

		s = name + strcspn (name, " \t");	/* end of field */
		if (*s == '\0')
			continue;	/* only 1 field?? */

		*s++ = '\0';
		value = s + strspn (s, " \"\t");	/* next nonwhite */
		*(value + strcspn (value, "\"")) = '\0';

		/*
		 * Store the value in def_table.
		 *
		 * Ignore failures to load the login.defs file.
		 * The error was already reported to the user and to
		 * syslog. The tools will just use their default values.
		 */
		(void)putdef_str (name, value);
	}

	if (ferror (fp) != 0) {
		int err = errno;
		SYSLOG ((LOG_CRIT, "cannot read login definitions %s [%s]",
		         def_fname, strerror (err)));
		exit (EXIT_FAILURE);
	}

	(void) fclose (fp);
}