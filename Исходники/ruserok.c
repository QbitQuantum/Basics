/**
 * @brief
 * 	check whether to allow access for users.
 *
 * @param[in] rhost - remote hosts
 * @param[in] superuser - val to indicate whether superuser
 * @param[in] ruser - remote user
 * @param[in] luser - local user
 *
 * @return	int
 * @retval	0	if access is allowed
 * @retval	-1	if access is denied
 * @retval	-2	if user does not exist
 * @retval	-3	problem reading user's .rhosts file.
 * 
 * @par	Note:
 *	Checks if (ruser,rhost) can access account
 *	luser@LOCALHOST. The hosts.equiv or user's .rhosts is consulted.
 *
 */
int
ruserok(const char *rhost, int superuser, const char *ruser, const char *luser)
{
	char	hosts_equiv[MAXPATHLEN+1];
	char	rhosts[MAXPATHLEN+1];
	struct  stat sbuf;
	int	rc = 1;
	struct  passwd *pw;
	int	user_impersonate = 0;
	char	logb[LOG_BUF_SIZE] = {'\0' } ;

	/* see if local user exists! */
	if ((pw = getpwnam((char *)luser)) == NULL) {
		sprintf(logb,"user %s does not exist!", luser);
		log_err(-1, "ruserok", logb);
		return (-2);
	}

	/* Let's construct the hosts.equiv file */
	sprintf(hosts_equiv, "%s\\system32\\drivers\\etc\\hosts.equiv",
		get_saved_env("SYSTEMROOT"));
	if (stat(hosts_equiv, &sbuf) != 0) {
		sprintf(hosts_equiv, "%s\\hosts.equiv",
			get_saved_env("SYSTEMROOT"));
	}

	/* check hosts.equiv file if luser is not superuser */
	if( !superuser && \
		chk_file_sec(hosts_equiv, 0, 0, WRITES_MASK, 0) == 0 && \
		  match_hosts_equiv_entry(hosts_equiv, rhost, ruser, luser) )
		return (0);

	/* check luser's .rhosts file */
	/* Let's construct the $HOME/.rhosts file */
	/* have to read .rhosts as user */
	if (pw->pw_userlogin != INVALID_HANDLE_VALUE) {
		ImpersonateLoggedOnUser(pw->pw_userlogin);
		user_impersonate =1;
	}

	strcpy(rhosts, getRhostsFile(pw->pw_name, pw->pw_userlogin));

	rc = match_rhosts_entry(rhosts, rhost, ruser);
	if (user_impersonate)
		RevertToSelf();

	if (rc == 1)		/* ok */
		return (0);
	else if (rc < 0)	/* some error occurred */
		return (-3);
	else			/* absolutely no match */
		return (-1);
}