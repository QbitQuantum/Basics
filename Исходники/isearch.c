/* ARGSUSED */
static int
isearch(int f GCC_UNUSED, int n)
{
    static TBUFF *pat_save = 0;	/* Saved copy of the old pattern str */

    int status;			/* Search status */
    register int cpos;		/* character number in search string */
    register int c;		/* current input character */
    MARK curpos, curp;		/* Current point on entry */
    int init_direction;		/* The initial search direction */

    /* Initialize starting conditions */

    cmd_reexecute = -1;		/* We're not re-executing (yet?) */
    itb_init(&cmd_buff, EOS);	/* Init the command buffer */
    /* Save the old pattern string */
    (void) tb_copy(&pat_save, searchpat);
    curpos = DOT;		/* Save the current pointer */
    init_direction = n;		/* Save the initial search direction */

    ignorecase = window_b_val(curwp, MDIGNCASE);

    scanboundry(FALSE, DOT, FORWARD);	/* keep scanner() finite */

    /* This is a good place to start a re-execution: */

  start_over:

    /* ask the user for the text of a pattern */
    promptpattern("ISearch: ");

    status = TRUE;		/* Assume everything's cool */

    /*
     * Get the first character in the pattern.  If we get an initial
     * Control-S or Control-R, re-use the old search string and find the
     * first occurrence
     */

    c = kcod2key(get_char());	/* Get the first character */
    if ((c == IS_FORWARD) ||
	(c == IS_REVERSE)) {	/* Reuse old search string? */
	for (cpos = 0; cpos < (int) tb_length(searchpat); ++cpos)
	    echochar(tb_values(searchpat)[cpos]);	/* and re-echo the string */
	curp = DOT;
	if (c == IS_REVERSE) {	/* forward search? */
	    n = -1;		/* No, search in reverse */
	    last_srch_direc = REVERSE;
	    backchar(TRUE, 1);	/* Be defensive about EOB */
	} else {
	    n = 1;		/* Yes, search forward */
	    last_srch_direc = FORWARD;
	    forwchar(TRUE, 1);
	}
	unget_char();
	status = scanmore(searchpat, n);	/* Do the search */
	if (status != TRUE)
	    DOT = curp;
	c = kcod2key(get_char());	/* Get another character */
    } else {
	tb_init(&searchpat, EOS);
    }
    /* Top of the per character loop */

    for_ever {			/* ISearch per character loop */
	/* Check for special characters, since they might change the
	 * search to be done
	 */

	if (ABORTED(c) || c == '\r')	/* search aborted? */
	    return (TRUE);	/* end the search */

	if (isbackspace(c))
	    c = '\b';

	if (c == quotec)	/* quote character? */
	    c = kcod2key(get_char());	/* Get the next char */

	switch (c) {		/* dispatch on the input char */
	case IS_REVERSE:	/* If backward search */
	case IS_FORWARD:	/* If forward search */
	    curp = DOT;
	    if (c == IS_REVERSE) {	/* forward search? */
		last_srch_direc = REVERSE;
		n = -1;		/* No, search in reverse */
		backchar(TRUE, 1);	/* Be defensive about
					 * EOB */
	    } else {
		n = 1;		/* Yes, search forward */
		last_srch_direc = FORWARD;
		forwchar(TRUE, 1);
	    }
	    status = scanmore(searchpat, n);	/* Do the search */
	    if (status != TRUE)
		DOT = curp;
	    c = kcod2key(get_char());	/* Get the next char */
	    continue;		/* Go continue with the search */

	case '\t':		/* Generically allowed */
	case '\n':		/* controlled characters */
	    break;		/* Make sure we use it */

	case '\b':		/* or if a Rubout: */
	    if (itb_length(cmd_buff) <= 1)	/* Anything to delete? */
		return (TRUE);	/* No, just exit */
	    unget_char();
	    DOT = curpos;	/* Reset the pointer */
	    n = init_direction;	/* Reset the search direction */
	    (void) tb_copy(&searchpat, pat_save);
	    /* Restore the old search str */
	    cmd_reexecute = 0;	/* Start the whole mess over */
	    goto start_over;	/* Let it take care of itself */

	    /* Presumably a quasi-normal character comes here */

	default:		/* All other chars */
	    if (!isPrint(c)) {	/* Is it printable? */
		/* Nope. */
		unkeystroke(c);	/* Re-eat the char */
		return (TRUE);	/* And return the last status */
	    }
	}			/* Switch */

	/* I guess we got something to search for, so search for it */

	tb_append(&searchpat, c);	/* put the char in the buffer */
	echochar(c);		/* Echo the character */
	if (!status) {		/* If we lost last time */
	    kbd_alarm();	/* Feep again */
	} else			/* Otherwise, we must have won */
	    status = scanmore(searchpat, n);	/* or find the next
						   * match */
	c = kcod2key(get_char());	/* Get the next char */
    }				/* for_ever */
}