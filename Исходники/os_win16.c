/*
 * Either execute a command by calling the shell or start a new shell
 */
    int
mch_call_shell(
    char_u *cmd,
    int options)	    /* SHELL_, see vim.h */
{
    int		x;
    int		tmode = cur_tmode;

    out_flush();


#ifdef MCH_WRITE_DUMP
    if (fdDump)
    {
	fprintf(fdDump, "mch_call_shell(\"%s\", %d)\n", cmd, options);
	fflush(fdDump);
    }
#endif

    /*
     * Catch all deadly signals while running the external command, because a
     * CTRL-C, Ctrl-Break or illegal instruction  might otherwise kill us.
     */
    signal(SIGINT, SIG_IGN);
    signal(SIGILL, SIG_IGN);
    signal(SIGFPE, SIG_IGN);
    signal(SIGSEGV, SIG_IGN);
    signal(SIGTERM, SIG_IGN);
    signal(SIGABRT, SIG_IGN);

    if (options & SHELL_COOKED)
	settmode(TMODE_COOK);	/* set to normal mode */

    if (cmd == NULL)
    {
	x = mch_system(p_sh, options);
    }
    else
    {
	/* we use "command" or "cmd" to start the shell; slow but easy */
	char_u *newcmd;

	newcmd = lalloc(
		STRLEN(p_sh) + STRLEN(p_shcf) + STRLEN(cmd) + 10, TRUE);
	if (newcmd != NULL)
	{
	    if (STRNICMP(cmd, "start ", 6) == 0)
	    {
		sprintf((char *)newcmd, "%s\0", cmd+6);
		if (WinExec((LPCSTR)newcmd, SW_SHOWNORMAL) > 31)
		    x = 0;
		else
		    x = -1;
	    }
	    else
	    {
		sprintf((char *)newcmd, "%s%s %s %s",
			"",
			p_sh,
			p_shcf,
			cmd);
		x = mch_system((char *)newcmd, options);
	    }
	    vim_free(newcmd);
	}
    }

    if (tmode == TMODE_RAW)
	settmode(TMODE_RAW);	/* set to raw mode */

    if (x && !(options & SHELL_SILENT) && !emsg_silent)
    {
	smsg(_("shell returned %d"), x);
	msg_putchar('\n');
    }
#ifdef FEAT_TITLE
    resettitle();
#endif

    signal(SIGINT, SIG_DFL);
    signal(SIGILL, SIG_DFL);
    signal(SIGFPE, SIG_DFL);
    signal(SIGSEGV, SIG_DFL);
    signal(SIGTERM, SIG_DFL);
    signal(SIGABRT, SIG_DFL);


    return x;
}