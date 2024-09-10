static void
GetEnvironment(void)
{
    static char	envDISPLAY[]="DISPLAY";
    static char	envSESSION_MANAGER[]="SESSION_MANAGER";
    static char	envAUDIOSERVER[]="AUDIOSERVER";
    char	*p, *temp;

    remote_allowed = 1;

    display_env = NULL;
    if((p = cmd_line_display) || (p = (char *) getenv(envDISPLAY))) {
	display_env = (char *) XtMalloc(strlen(envDISPLAY)+1+strlen(p)+1);
	if(!display_env) nomem();
	sprintf(display_env, "%s=%s", envDISPLAY, p);

	/*
	 * When we restart a remote client, we have to make sure the
	 * display environment we give it has the SM's hostname.
	 */

	if ((temp = strchr (p, '/')) == 0)
	    temp = p;
	else
	    temp++;

	if (*temp != ':')
	{
	    /* we have a host name */

	    non_local_display_env = (char *) XtMalloc (
		strlen (display_env) + 1);
	    if (!non_local_display_env) nomem();

	    strcpy (non_local_display_env, display_env);
	}
	else
	{
	    char hostnamebuf[256];

	    gethostname (hostnamebuf, sizeof hostnamebuf);
	    non_local_display_env = (char *) XtMalloc (
		strlen (envDISPLAY) + 1 +
		strlen (hostnamebuf) + strlen (temp) + 1);
	    if (!non_local_display_env) nomem();
	    sprintf(non_local_display_env, "%s=%s%s",
		envDISPLAY, hostnamebuf, temp);
	}
    }

    session_env = NULL;
    if((p = (char *) getenv(envSESSION_MANAGER))) {
	session_env = (char *) XtMalloc(
	    strlen(envSESSION_MANAGER)+1+strlen(p)+1);
	if(!session_env) nomem();
	sprintf(session_env, "%s=%s", envSESSION_MANAGER, p);

	/*
	 * When we restart a remote client, we have to make sure the
	 * session environment does not have the SM's local connection port.
	 */

	non_local_session_env = (char *) XtMalloc (strlen (session_env) + 1);
	if (!non_local_session_env) nomem();
	strcpy (non_local_session_env, session_env);

	if ((temp = Strstr (non_local_session_env, "local/")) != NULL)
	{
	    char *delim = strchr (temp, ',');
	    if (delim == NULL)
	    {
		if (temp == non_local_session_env +
		    strlen (envSESSION_MANAGER) + 1)
		{
		    *temp = '\0';
		    remote_allowed = 0;
		}
		else
		    *(temp - 1) = '\0';
	    }
	    else
	    {
		int bytes = strlen (delim + 1);
		memmove (temp, delim + 1, bytes);
		*(temp + bytes) = '\0';
	    }
	}
    }

    audio_env = NULL;
    if((p = (char *) getenv(envAUDIOSERVER))) {
	audio_env = (char *) XtMalloc(strlen(envAUDIOSERVER)+1+strlen(p)+1);
	if(!audio_env) nomem();
	sprintf(audio_env, "%s=%s", envAUDIOSERVER, p);
    }
}