static void
opt(struct tbl_node *tbl, int ln, const char *p, int *pos)
{
	int		 i, sv;
	char		 buf[KEY_MAXNAME];

	/*
	 * Parse individual options from the stream as surrounded by
	 * this goto.  Each pass through the routine parses out a single
	 * option and registers it.  Option arguments are processed in
	 * the arg() function.
	 */

again:	/*
	 * EBNF describing this section:
	 *
	 * options	::= option_list [:space:]* [;][\n]
	 * option_list	::= option option_tail
	 * option_tail	::= [:space:]+ option_list |
	 * 		::= epsilon
	 * option	::= [:alpha:]+ args
	 * args		::= [:space:]* [(] [:alpha:]+ [)]
	 */

	while (isspace((unsigned char)p[*pos]))
		(*pos)++;

	/* Safe exit point. */

	if (';' == p[*pos])
		return;

	/* Copy up to first non-alpha character. */

	for (sv = *pos, i = 0; i < KEY_MAXNAME; i++, (*pos)++) {
		buf[i] = (char)tolower((unsigned char)p[*pos]);
		if ( ! isalpha((unsigned char)buf[i]))
			break;
	}

	/* Exit if buffer is empty (or overrun). */

	if (KEY_MAXNAME == i || 0 == i) {
		mandoc_msg(MANDOCERR_TBL, tbl->parse, ln, *pos, NULL);
		return;
	}

	buf[i] = '\0';

	while (isspace((unsigned char)p[*pos]))
		(*pos)++;

	/* 
	 * Look through all of the available keys to find one that
	 * matches the input.  FIXME: hashtable this.
	 */

	for (i = 0; i < KEY_MAXKEYS; i++) {
		if (strcmp(buf, keys[i].name))
			continue;

		/*
		 * Note: this is more difficult to recover from, as we
		 * can be anywhere in the option sequence and it's
		 * harder to jump to the next.  Meanwhile, just bail out
		 * of the sequence altogether.
		 */

		if (keys[i].key) 
			tbl->opts.opts |= keys[i].key;
		else if ( ! arg(tbl, ln, p, pos, keys[i].ident))
			return;

		break;
	}

	/* 
	 * Allow us to recover from bad options by continuing to another
	 * parse sequence.
	 */

	if (KEY_MAXKEYS == i)
		mandoc_msg(MANDOCERR_TBLOPT, tbl->parse, ln, sv, NULL);

	goto again;
	/* NOTREACHED */
}