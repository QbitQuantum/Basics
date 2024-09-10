/*
 * Returns the current user name.
 */
static char *
get_username(void)
{
	char *ret;

#ifndef WIN32
	struct passwd *pw;

	pw = getpwuid(geteuid());
	ret = (pw ? pw->pw_name : NULL);
#else
	static char username[128];	/* remains after function execute */
	DWORD		len = sizeof(username) - 1;

	if (GetUserNameA(username, &len))
		ret = username;
	else
	{
		_dosmaperr(GetLastError());
		ret = NULL;
	}
#endif

	if (ret == NULL)
		ereport(ERROR,
			(errcode_errno(),
			 errmsg("could not get current user name: ")));
	return ret;
}