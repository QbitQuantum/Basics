/* tw_complete():
 *	Return the appropriate completion for the command
 *
 *	valid completion strings are:
 *	p/<range>/<completion>/[<suffix>/]	positional
 *	c/<pattern>/<completion>/[<suffix>/]	current word ignore pattern
 *	C/<pattern>/<completion>/[<suffix>/]	current word with pattern
 *	n/<pattern>/<completion>/[<suffix>/]	next word
 *	N/<pattern>/<completion>/[<suffix>/]	next-next word
 */
int
tw_complete(const Char *line, Char **word, Char **pat, int looking, eChar *suf)
{
    Char *buf, **vec, **wl;
    static Char nomatch[2] = { (Char) ~0, 0x00 };
    const Char *ptr;
    size_t wordno;
    int n;

    buf = Strsave(line);
    cleanup_push(buf, xfree);
    /* Single-character words, empty current word, terminating NULL */
    wl = xmalloc(((Strlen(line) + 1) / 2 + 2) * sizeof (*wl));
    cleanup_push(wl, xfree);

    /* find the command */
    if ((wl[0] = tw_tok(buf)) == NULL || wl[0] == INVPTR) {
	cleanup_until(buf);
	return TW_ZERO;
    }

    /*
     * look for hardwired command completions using a globbing
     * search and for arguments using a normal search.
     */
    if ((vec = tw_find(wl[0], &completions, (looking == TW_COMMAND)))
	== NULL) {
	cleanup_until(buf);
	return looking;
    }

    /* tokenize the line one more time :-( */
    for (wordno = 1; (wl[wordno] = tw_tok(NULL)) != NULL &&
		      wl[wordno] != INVPTR; wordno++)
	continue;

    if (wl[wordno] == INVPTR) {		/* Found a meta character */
	cleanup_until(buf);
	return TW_ZERO;			/* de-activate completions */
    }
#ifdef TDEBUG
    {
	size_t i;
	for (i = 0; i < wordno; i++)
	    xprintf("'%s' ", short2str(wl[i]));
	xprintf("\n");
    }
#endif /* TDEBUG */

    /* if the current word is empty move the last word to the next */
    if (**word == '\0') {
	wl[wordno] = *word;
	wordno++;
    }
    wl[wordno] = NULL;
	

#ifdef TDEBUG
    xprintf("\r\n");
    xprintf("  w#: %lu\n", (unsigned long)wordno);
    xprintf("line: %s\n", short2str(line));
    xprintf(" cmd: %s\n", short2str(wl[0]));
    xprintf("word: %s\n", short2str(*word));
    xprintf("last: %s\n", wordno >= 2 ? short2str(wl[wordno-2]) : "n/a");
    xprintf("this: %s\n", wordno >= 1 ? short2str(wl[wordno-1]) : "n/a");
#endif /* TDEBUG */
    
    for (;vec != NULL && (ptr = vec[0]) != NULL; vec++) {
	Char  *ran,	        /* The pattern or range X/<range>/XXXX/ */
	      *com,	        /* The completion X/XXXXX/<completion>/ */
	     *pos = NULL;	/* scratch pointer 			*/
	int   cmd, res;
        Char  sep;		/* the command and separator characters */
	int   exact;

	if (ptr[0] == '\0')
	    continue;

#ifdef TDEBUG
	xprintf("match %s\n", short2str(ptr));
#endif /* TDEBUG */

	switch (cmd = ptr[0]) {
	case 'N':
	    pos = (wordno < 3) ? nomatch : wl[wordno - 3];
	    break;
	case 'n':
	    pos = (wordno < 2) ? nomatch : wl[wordno - 2];
	    break;
	case 'c':
	case 'C':
	    pos = (wordno < 1) ? nomatch : wl[wordno - 1];
	    break;
	case 'p':
	    break;
	default:
	    stderror(ERR_COMPINV, CGETS(27, 1, "command"), cmd);
	    return TW_ZERO;
	}

	sep = ptr[1];
	if (!Ispunct(sep)) {
	    /* Truncates data if WIDE_STRINGS */
	    stderror(ERR_COMPINV, CGETS(27, 2, "separator"), (int)sep);
	    return TW_ZERO;
	}

	ptr = tw_dollar(&ptr[2], wl, wordno, &ran, sep,
			CGETS(27, 3, "pattern"));
	cleanup_push(ran, xfree);
	if (ran[0] == '\0')	/* check for empty pattern (disallowed) */
	{
	    stderror(ERR_COMPINC, cmd == 'p' ?  CGETS(27, 4, "range") :
		     CGETS(27, 3, "pattern"), "");
	    return TW_ZERO;
	}

	ptr = tw_dollar(ptr, wl, wordno, &com, sep,
			CGETS(27, 5, "completion"));
	cleanup_push(com, xfree);

	if (*ptr != '\0') {
	    if (*ptr == sep)
		*suf = CHAR_ERR;
	    else
		*suf = *ptr;
	}
	else
	    *suf = '\0';

#ifdef TDEBUG
	xprintf("command:    %c\nseparator:  %c\n", cmd, (int)sep);
	xprintf("pattern:    %s\n", short2str(ran));
	xprintf("completion: %s\n", short2str(com));
	xprintf("suffix:     ");
        switch (*suf) {
	case 0:
	    xprintf("*auto suffix*\n");
	    break;
	case CHAR_ERR:
	    xprintf("*no suffix*\n");
	    break;
	default:
	    xprintf("%c\n", (int)*suf);
	    break;
	}
#endif /* TDEBUG */

	exact = 0;
	switch (cmd) {
	case 'p':			/* positional completion */
#ifdef TDEBUG
	    xprintf("p: tw_pos(%s, %lu) = ", short2str(ran),
		    (unsigned long)wordno - 1);
	    xprintf("%d\n", tw_pos(ran, wordno - 1));
#endif /* TDEBUG */
	    if (!tw_pos(ran, wordno - 1)) {
		cleanup_until(ran);
		continue;
	    }
	    break;

	case 'N':			/* match with the next-next word */
	case 'n':			/* match with the next word */
	    exact = 1;
	    /*FALLTHROUGH*/
	case 'c':			/* match with the current word */
	case 'C':
#ifdef TDEBUG
	    xprintf("%c: ", cmd);
#endif /* TDEBUG */
	    if ((n = tw_match(pos, ran, exact)) < 0) {
		cleanup_until(ran);
		continue;
	    }
	    if (cmd == 'c')
		*word += n;
	    break;

	default:
	    abort();		       /* Cannot happen */
	}
	tsetenv(STRCOMMAND_LINE, line);
	res = tw_result(com, pat);
	Unsetenv(STRCOMMAND_LINE);
	cleanup_until(buf);
	return res;
    }
    cleanup_until(buf);
    *suf = '\0';
    return TW_ZERO;
} /* end tw_complete */