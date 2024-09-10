/* Function for accepting password input from users
*/
char*
getpasswd(const char *prompt)
{
    static char     pwbuf[MAX_PASS_LEN + 1] = {0};
    char           *ptr;    
    int             c;

#ifndef WIN32
    FILE           *fp;
	sigset_t        sig, old_sig;
    struct termios  ts, old_ts;

    if((fp = fopen(ctermid(NULL), "r+")) == NULL)
        return(NULL);

    setbuf(fp, NULL);

    /* Setup blocks for SIGINT and SIGTSTP and save the original signal
     * mask.
    */
    sigemptyset(&sig);
    sigaddset(&sig, SIGINT);
    sigaddset(&sig, SIGTSTP);
    sigprocmask(SIG_BLOCK, &sig, &old_sig);

    /* Save current tty state for later restoration after we disable echo
     * of characters to the tty.
    */
    tcgetattr(fileno(fp), &ts);
    old_ts = ts;
    ts.c_lflag &= ~(ECHO | ECHOE | ECHOK | ECHONL);
    tcsetattr(fileno(fp), TCSAFLUSH, &ts);

    fputs(prompt, fp);
#endif

    /* Read in the password.
    */
    ptr = pwbuf;
#ifdef WIN32
	_cputs(prompt);
    while((c = _getch()) != '\r')
	{
		/* Handle a backspace without backing up too far.
		*/
		if(c == '\b')
		{
			if(ptr != pwbuf)
				*ptr--;

			continue;
		}

		/* Handle a Ctrl-U to clear the password entry and start over
		 * (like it works under Unix).
	    */
		if(c == 0x15)
		{
			ptr = pwbuf;
			continue;
		}
#else
	while((c = getc(fp)) != EOF && c != '\n')
	{
#endif
        if(ptr < &pwbuf[MAX_PASS_LEN])
            *ptr++ = c;
	}

	/* Null terminate the password.
    */
    *ptr = 0;

#ifndef WIN32
    /* we can go ahead and echo out a newline.
    */
    putc('\n', fp);

	/* Restore our tty state and signal handlers.
    */
    tcsetattr(fileno(fp), TCSAFLUSH, &old_ts);
    sigprocmask(SIG_BLOCK, &old_sig, NULL);

    fclose(fp);
#else
	/* In Windows, it would be a CR-LF
	*/
	_putch('\r');
	_putch('\n');
#endif

    return(pwbuf);
}

/* Function for accepting password input from from a file
*/
char*
getpasswd_file(const char *pw_file, const char *server_str)
{
    FILE           *pwfile_ptr;
    unsigned int    numLines = 0, i = 0, found_dst;

    static char     pwbuf[MAX_PASS_LEN + 1]     = {0};
    char            conf_line_buf[MAX_LINE_LEN] = {0};
    char            tmp_char_buf[MAX_LINE_LEN]  = {0};
    char           *lptr;

    if ((pwfile_ptr = fopen(pw_file, "r")) == NULL)
    {
        fprintf(stderr, "Could not open config file: %s\n", pw_file);
        exit(1);
    }

    while ((fgets(conf_line_buf, MAX_LINE_LEN, pwfile_ptr)) != NULL)
    {
        numLines++;
        conf_line_buf[MAX_LINE_LEN-1] = '\0';
        lptr = conf_line_buf;

        memset(tmp_char_buf, 0x0, MAX_LINE_LEN);

        while (*lptr == ' ' || *lptr == '\t' || *lptr == '=')
            lptr++;

        /* Get past comments and empty lines.
        */
        if (*lptr == '#' || *lptr == '\n' || *lptr == '\r' || *lptr == '\0' || *lptr == ';')
            continue;

        /* Look for a line like "<SPA destination IP>: <password>" - this allows
        * multiple keys to be placed within the same file, and the client will
        * reference the matching one for the SPA server we are contacting
        */
        found_dst = 1;
        for (i=0; i < strlen(server_str); i++)
            if (*lptr++ != server_str[i])
                found_dst = 0;

        if (! found_dst)
            continue;

        if (*lptr == ':')
            lptr++;
        else
            continue;

        /* Skip whitespace until we get to the password
        */
        while (*lptr == ' ' || *lptr == '\t' || *lptr == '=')
            lptr++;

        i = 0;
        while (*lptr != '\0' && *lptr != '\n') {
            pwbuf[i] = *lptr;
            lptr++;
            i++;
        }
        pwbuf[i] = '\0';
    }

    fclose(pwfile_ptr);

    if (pwbuf[0] == '\0') {
        fprintf(stderr, "Could not get password for IP: %s from: %s\n",
            server_str, pw_file);
        exit(1);
    }

    return pwbuf;
}