const char *fullname(void)
{
    static VSTRING *result;
    char   *cp;
    int     ch;
    uid_t   uid;
    struct passwd *pwd;

    if (result == 0)
	result = vstring_alloc(10);

    /*
     * Try the environment.
     */
    if ((cp = safe_getenv("NAME")) != 0)
	return (vstring_str(vstring_strcpy(result, cp)));

    /*
     * Try the password file database.
     */
    uid = getuid();
    if ((pwd = getpwuid(uid)) == 0)
	return (0);

    /*
     * Replace all `&' characters by the login name of this user, first
     * letter capitalized. Although the full name comes from the protected
     * password file, the actual data is specified by the user so we should
     * not trust its sanity.
     */
    VSTRING_RESET(result);
    for (cp = pwd->pw_gecos; (ch = *(unsigned char *) cp) != 0; cp++) {
	if (ch == ',' || ch == ';' || ch == '%')
	    break;
	if (ch == '&') {
	    if (pwd->pw_name[0]) {
		VSTRING_ADDCH(result, TOUPPER(pwd->pw_name[0]));
		vstring_strcat(result, pwd->pw_name + 1);
	    }
	} else {
	    VSTRING_ADDCH(result, ch);
	}
    }
    VSTRING_TERMINATE(result);
    return (vstring_str(result));
}