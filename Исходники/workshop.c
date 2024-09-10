/*ARGSUSED*/
    void
workshop_toolbar_button(
	char	*label,
	char	*verb,
	char	*senseVerb,
	char	*filepos,
	char	*help,
	char	*sense,
	char	*file,
	char	*left)
{
    char	cbuf[BUFSIZ + MAXPATHLEN];
    char	namebuf[BUFSIZ];
    static int	tbid = 1;
    char_u	*p;

#ifdef WSDEBUG_TRACE
    if (WSDLEVEL(WS_TRACE_VERBOSE))
	wsdebug("workshop_toolbar_button(\"%s\", %s, %s,\n"
		"\t%s, \"%s\", %s,\n\t\"%s\",\n\t<%s>)\n",
		label   && *label   ? label   : "<None>",
		verb    && *verb    ? verb    : "<None>",
		senseVerb && *senseVerb    ? senseVerb    : "<None>",
		filepos && *filepos ? filepos : "<None>",
		help    && *help    ? help    : "<None>",
		sense   && *sense   ? sense   : "<None>",
		file    && *file    ? file    : "<None>",
		left    && *left    ? left    : "<None>");
    else if (WSDLEVEL(WS_TRACE))
	wstrace("workshop_toolbar_button(\"%s\", %s)\n",
		label   && *label   ? label   : "<None>",
		verb    && *verb    ? verb    : "<None>");
#endif
#ifdef WSDEBUG_SENSE
    if (ws_debug)
	wsdebug("button: %-21.20s%-21.20s(%s)\n", label, verb,
		*sense == '1' ? "Sensitive" : "Insensitive");
#endif

    if (left && *left && atoi(left) > 0)
    {
	/* Add a separator (but pass the width passed after the ':') */
	sprintf(cbuf, "amenu 1.%d ToolBar.-sep%d:%s- <nul>",
		tbpri - 5, tbid++, left);

	coloncmd(cbuf, True);
    }

    p = vim_strsave_escaped((char_u *)label, (char_u *)"\\. ");
    sprintf(namebuf, "ToolBar.%s", p);
    vim_free(p);
    STRCPY(cbuf, "amenu <silent> ");
    if (file != NULL && *file != NUL)
    {
	p = vim_strsave_escaped((char_u *)file, (char_u *)" ");
	sprintf(cbuf + STRLEN(cbuf), "icon=%s ", p);
	vim_free(p);
    }
    sprintf(cbuf + STRLEN(cbuf), "1.%d %s :wsverb %s<CR>",
							tbpri, namebuf, verb);

    /* Define the menu item */
    coloncmd(cbuf, True);

    if (*sense == '0')
    {
	/* If menu isn't sensitive at startup... */
	sprintf(cbuf, "amenu disable %s", namebuf);
	coloncmd(cbuf, True);
    }

    if (help && *help)
    {
	/* Do the tooltip */
	sprintf(cbuf, "tmenu %s %s", namebuf, help);
	coloncmd(cbuf, True);
    }

    addMenu(namebuf, NULL, verb);
    tbpri += 10;
}