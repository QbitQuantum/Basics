/*
 * PersonExists()
 *
 * This function will check to see if the given name is valid for mail.
 *
 * This includes special processing for "Sysop" and "Citadel".
 */
int PersonExists(char *name)
{
	int result;
	logBuffer temp;

	if ((strCmpU("Citadel", name) == SAMESTRING && HalfSysop()) ||
		             strCmpU("sysop", name) == SAMESTRING)
		return cfg.MAXLOGTAB;       /* signals special string */

	initLogBuf(&temp);
	result = findPerson(name, &temp);
	if (result != ERROR) strCpy(name, temp.lbname);
	killLogBuf(&temp);
	return result;
}