int
utmpx_mark_init(pid_t pid, char *prefix)
{
	struct utmpx ut, *oldu;
	int tmplen;
	int ret;

	while (st->st_initial && !utmpx_truncated)
		(void) usleep(200 * USEC_PER_MSEC);

	/*
	 * Clean out any preexisting records for this PID, as they must be
	 * inaccurate.
	 */
	utmpx_mark_dead(pid, 0, B_TRUE);

	/*
	 * Construct a new record with the appropriate prefix.
	 */
	(void) memset(&ut, 0, sizeof (ut));
	(void) strncpy(ut.ut_user, ".startd", sizeof (ut.ut_user));
	ut.ut_pid = pid;

	ut.ut_id[0] = ut.ut_id[1] = ut.ut_id[2] = ut.ut_id[3] = (char)SC_WILDC;

	for (ret = 0; ret < strlen(prefix); ret++)
		ut.ut_id[ret] = prefix[ret];

	ut.ut_type = INIT_PROCESS;
	(void) time(&ut.ut_tv.tv_sec);

	for (;;) {
		MUTEX_LOCK(&utmpx_lock);
		setutxent();

		if ((oldu = getutxid(&ut)) != NULL) {
			/*
			 * Copy in the old "line" and "host" fields.
			 */
			bcopy(oldu->ut_line, ut.ut_line, sizeof (ut.ut_line));
			bcopy(oldu->ut_host, ut.ut_host, sizeof (ut.ut_host));
			ut.ut_syslen = (tmplen = strlen(ut.ut_host)) ?
			    min(tmplen + 1, sizeof (ut.ut_host)) : 0;
		}

		if (makeutx(&ut) != NULL)
			break;

		if (errno != EROFS)
			log_framework(LOG_WARNING,
			    "makeutx failed, retrying: %s\n", strerror(errno));

		MUTEX_UNLOCK(&utmpx_lock);

		(void) sleep(1);
	}

	updwtmpx(WTMPX_FILE, &ut);

	endutxent();
	MUTEX_UNLOCK(&utmpx_lock);

	return (ret);
}