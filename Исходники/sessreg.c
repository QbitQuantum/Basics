static void
set_utmpx (struct utmpx *u, const char *line, const char *user,
	   const char *host, time_t date, int addp)
{
	static const char letters[] =
	       "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

	memset (u, 0, sizeof (*u));
	if (line)
	{
		if(strcmp(line, ":0") == 0)
			(void) strcpy(u->ut_line, "console");
		else
			(void) strncpy (u->ut_line, line, sizeof (u->ut_line));

		strncpy(u->ut_host, line, sizeof(u->ut_host));
#ifdef HAVE_STRUCT_UTMPX_UT_SYSLEN
		u->ut_syslen = strlen(line);
#endif
	}
	else
		memset (u->ut_line, 0, sizeof (u->ut_line));
	if (addp && user)
		(void) strncpy (u->ut_user, user, sizeof (u->ut_user));
	else
		memset (u->ut_user, 0, sizeof (u->ut_user));

	if (line) {
		size_t	i;
		/*
		 * this is a bit crufty, but
		 * follows the apparent conventions in
		 * the ttys file.  ut_id is only 4 bytes
		 * long, and the last 4 bytes of the line
		 * name are written into it, left justified.
		 */
		i = strlen (line);
		if (i >= sizeof (u->ut_id))
			i -= sizeof (u->ut_id);
		else
			i = 0;
		(void) strncpy (u->ut_id, line + i, sizeof (u->ut_id));

		/* make sure there is no entry using identical ut_id */
		if (!UtmpxIdOpen(u->ut_id) && addp) {
			int limit = sizeof(letters) - 1;
			int t = 0;

			u->ut_id[1] = line[i];
			u->ut_id[2] = line[i+1];
			u->ut_id[3] = line[i+2];
			do {
				u->ut_id[0] = letters[t];
				t++;
			} while (!UtmpxIdOpen(u->ut_id) && (t < limit));
		}
		if (!addp && strstr(line, ":") != NULL) {
			struct utmpx *tmpu;

			while ( (tmpu = getutxent()) != NULL ) {
				if ( (strcmp(tmpu->ut_host, line) == 0 ) &&
					tmpu->ut_type != DEAD_PROCESS ) {
					strncpy(u->ut_id, tmpu->ut_id,
						sizeof(u->ut_id));
					break;
				}
			}
			endutxent();
		}
	} else
		memset (u->ut_id, 0, sizeof (u->ut_id));

	if (addp) {
		u->ut_pid = getppid ();
		u->ut_type = USER_PROCESS;
	} else {
		u->ut_pid = 0;
		u->ut_type = DEAD_PROCESS;
	}
	u->ut_tv.tv_sec = date;
	u->ut_tv.tv_usec = 0;
}