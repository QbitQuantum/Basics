/*
 * vs_output --
 *	Output the text to the screen.
 */
static void
vs_output(SCR *sp, mtype_t mtype, const char *line, int llen)
{
	unsigned char *kp;
	GS *gp;
	VI_PRIVATE *vip;
	size_t chlen, notused;
	int ch, len, tlen;
	const char *p, *t;
	char *cbp, *ecbp, cbuf[128];

	gp = sp->gp;
	vip = VIP(sp);
	for (p = line; llen > 0;) {
		/* Get the next physical line. */
		if ((p = memchr(line, '\n', llen)) == NULL)
			len = llen;
		else
			len = p - line;

		/*
		 * The max is sp->cols characters, and we may have already
		 * written part of the line.
		 */
		if (len + vip->lcontinue > sp->cols)
			len = sp->cols - vip->lcontinue;

		/*
		 * If the first line output, do nothing.  If the second line
		 * output, draw the divider line.  If drew a full screen, we
		 * remove the divider line.  If it's a continuation line, move
		 * to the continuation point, else, move the screen up.
		 */
		if (vip->lcontinue == 0) {
			if (!IS_ONELINE(sp)) {
				if (vip->totalcount == 1) {
					(void)gp->scr_move(sp,
					    LASTLINE(sp) - 1, 0);
					(void)gp->scr_clrtoeol(sp);
					(void)vs_divider(sp);
					F_SET(vip, VIP_DIVIDER);
					++vip->totalcount;
					++vip->linecount;
				}
				if (vip->totalcount == sp->t_maxrows &&
				    F_ISSET(vip, VIP_DIVIDER)) {
					--vip->totalcount;
					--vip->linecount;
					F_CLR(vip, VIP_DIVIDER);
				}
			}
			if (vip->totalcount != 0)
				vs_scroll(sp, NULL, SCROLL_W_QUIT);

			(void)gp->scr_move(sp, LASTLINE(sp), 0);
			++vip->totalcount;
			++vip->linecount;

			if (INTERRUPTED(sp))
				break;
		} else
			(void)gp->scr_move(sp, LASTLINE(sp), vip->lcontinue);

		/* Error messages are in inverse video. */
		if (mtype == M_ERR)
			(void)gp->scr_attr(sp, SA_INVERSE, 1);

		/* Display the line, doing character translation. */
#define	FLUSH {								\
	*cbp = '\0';							\
	(void)gp->scr_addstr(sp, cbuf, cbp - cbuf);			\
	cbp = cbuf;							\
}
		ecbp = (cbp = cbuf) + sizeof(cbuf) - 1;
		for (t = line, tlen = len; tlen--; ++t) {
			ch = *t;
			/*
			 * Replace tabs with spaces, there are places in
			 * ex that do column calculations without looking
			 * at <tabs> -- and all routines that care about
			 * <tabs> do their own expansions.  This catches
			 * <tabs> in things like tag search strings.
			 */
			if (ch == '\t')
				ch = ' ';
			chlen = KEY_LEN(sp, ch);
			if (cbp + chlen >= ecbp)
				FLUSH;
			for (kp = KEY_NAME(sp, ch); chlen--;)
				*cbp++ = *kp++;
		}
		if (cbp > cbuf)
			FLUSH;
		if (mtype == M_ERR)
			(void)gp->scr_attr(sp, SA_INVERSE, 0);

		/* Clear the rest of the line. */
		(void)gp->scr_clrtoeol(sp);

		/* If we loop, it's a new line. */
		vip->lcontinue = 0;

		/* Reset for the next line. */
		line += len;
		llen -= len;
		if (p != NULL) {
			++line;
			--llen;
		}
	}

	/* Set up next continuation line. */
	if (p == NULL)
		gp->scr_cursor(sp, &notused, &vip->lcontinue);
}